//
// Created by elle on 14/07/21.
//

#ifndef EXAMS_RAII_GUARD_H
#define EXAMS_RAII_GUARD_H

#include <mutex>
#include <condition_variable>

class semaphore{
    unsigned int count;
    std::mutex m;
    std::condition_variable cv;
public:
    explicit semaphore(int count): count(count) {}

    void acquire() {
        std::unique_lock ul(m);
        cv.wait(ul,[this]() {return count > 0;});
        count--;
    }

    void release() {
        std::unique_lock<std::mutex> ul(m);
        count++;
        cv.notify_one();
    }
};

class raii_guard {
    semaphore& s;
public:
    explicit raii_guard(semaphore& s): s(s) {
        s.acquire();
    }
    ~raii_guard() {
        s.release();
    }
};



#endif //EXAMS_RAII_GUARD_H
