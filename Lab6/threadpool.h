//
// Created by elle on 05/06/21.
//

#ifndef LAB6_THREADPOOL_H
#define LAB6_THREADPOOL_H

#include <future>
#include <vector>
#include <queue>

using task_t = std::packaged_task<void()>;

class thread_pool {
    std::vector<std::thread> workers;
    std::queue<task_t> tasks;
    std::mutex m;
    std::condition_variable cv;

    int N; // number of threads
    bool stop;

public:
    explicit thread_pool(const int &N = std::thread::hardware_concurrency());
    void enqueue(task_t task);
    ~thread_pool();
};


thread_pool::thread_pool(const int &N) : N(N), stop(false) {
    for(int i = 0; i < N ; ++i)
        // creating the N threads
        workers.emplace_back(
                [this](){
                    while(!stop || !tasks.empty()){
                        std::unique_lock ul{m};
                        //  "sleep" until a new task needs to get executed
                        // or if stop signal received
                        cv.wait(ul, [this]() { return !tasks.empty() || stop ; });
                        if( !tasks.empty())  { // something to do!
                            task_t task = std::move(tasks.front());
                            tasks.pop();
                            ul.unlock(); // release the lock
                            task();
                            ul.lock(); // get the lock again
                        }
                    }
                });
}


thread_pool::~thread_pool(){
    {
        std::unique_lock ul{m};
        stop = true;
    }
    cv.notify_all();
    for(auto &t : workers) t.join();
}

void thread_pool::enqueue(task_t t) {
    std::unique_lock ul{m};
    if (stop)
        throw std::logic_error("can't enqueue after stop signal");

    tasks.push(std::move(t));
    cv.notify_one();
}




#endif //LAB6_THREADPOOL_H
