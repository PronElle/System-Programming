//
// Created by elle on 14/07/21.
//

#ifndef EXAMS_CBUFFER_H
#define EXAMS_CBUFFER_H


#include <mutex>
#include <condition_variable>
#include <queue>
#include <optional>
#include <thread>

template <typename T>
class CBuffer {
    std::mutex m;
    std::condition_variable cv;
    std::queue<T> values;
    bool stop, failed;
    std::exception_ptr _eptr;

public:
    CBuffer() : stop(false), failed(false) {}

    ~CBuffer() {
        {
            std::lock_guard lg{m};
            stop = true;
        }
        cv.notify_all();
    }

    void fail (const std::exception_ptr &eptr){
        {
            std::lock_guard lg{m};
            failed = true;
            _eptr = eptr;
        }
        cv.notify_all();
    }

    void terminate(){
        {
            std::lock_guard lg{m};
            if (stop || failed) throw std::runtime_error("enqueing has stopped");
            stop = true;
        }
        cv.notify_all(); // notify stop signal
    }

    void next(T t) {
        {
            std::lock_guard lg{m};
            if (stop || failed) throw std::runtime_error("enqueing has stopped");
            values.push(std::move(t));
        }
        cv.notify_one(); // notify the consumer (if waiting)
    }

    std::optional<T> consume(){
        std::unique_lock ul{m};
        cv.wait(ul, [this]() { return !values.empty() || stop || failed; });

        if (values.empty()) { // if got notified and the queue is empty, then stop or failed have been sent
            if (stop)
                return std::nullopt;
            else
                std::rethrow_exception(_eptr);
        }
        // extract the value to consume
        T val = values.front();
        values.pop();
        return std::optional<T>(val);
    }
};



#endif //EXAMS_CBUFFER_H
