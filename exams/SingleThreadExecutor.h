//
// Created by elle on 14/07/21.
//

#ifndef EXAMS_SINGLETHREADEXECUTOR_H
#define EXAMS_SINGLETHREADEXECUTOR_H

#include <thread>
#include <condition_variable>
#include <queue>
#include <future>

using task_t = std::packaged_task<void()> ;

class SingleThreadExecutor {
    std::mutex m;
    std::condition_variable cv;
    bool stop;
    std::thread singleThread; // the only worker of the pool
    std::queue<task_t> tasks;


public:
    SingleThreadExecutor() : stop(false) {
        auto worker_fun = [this] () {
            std::unique_lock<std::mutex> ul{m};
            while (!stop || !tasks.empty()) {
                cv.wait(ul, [this]() { return stop || !tasks.empty(); });

                if (!tasks.empty()) { // something to do!
                    // extract next task to execute
                    task_t currentTask = std::move(tasks.front());
                    tasks.pop();

                    ul.unlock(); // release the lock
                    currentTask(); // execute the task
                    ul.lock(); // get back the lock
                }
            }
        };

        std::thread t(worker_fun);
        singleThread = std::move(t);
    }

    ~SingleThreadExecutor() {
        this->join();
    }

    void submit(task_t t) {
        std::lock_guard<std::mutex> lg{m};
        if (stop)
            throw std::logic_error("errore");
        // add new task
        tasks.push(std::move(t));
        cv.notify_one();
    }

    void close() {
        {
            std::lock_guard<std::mutex> lg{m};
            stop = true;
        }
        cv.notify_one();
    }

    void join() {
        if (singleThread.joinable()){
            close();
            singleThread.join();
        }
    }
};



#endif //EXAMS_SINGLETHREADEXECUTOR_H
