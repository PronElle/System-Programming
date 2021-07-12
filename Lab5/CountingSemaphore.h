//
// Created by elle on 05/06/21.
//

#ifndef LAB5_COUNTINGSEMAPHORE_H
#define LAB5_COUNTINGSEMAPHORE_H

#include <mutex>
#include <condition_variable>

class CountingSemaphore {
    int count;
    std::mutex m;
    std::condition_variable cv;

public:
    explicit CountingSemaphore(int count = 0): count(count){}
    void acquire();
    void release();
};

/**
 * A thread acquires the resourse iff less
 * than count threads are using it
 */
void CountingSemaphore::acquire() {
    std::unique_lock ul{m};
    // wait until count positive
    cv.wait(ul, [this](){return count > 0 ;});
    --count;
}

/**
 * releases the resourse, notifying the sleeping
 * threads on the condition variable
 */
void CountingSemaphore::release() {
    {
        std::unique_lock ul{m};
        count++;
    }
    cv.notify_one();
}


#endif //LAB5_COUNTINGSEMAPHORE_H
