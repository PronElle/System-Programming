//
// Created by elle on 09/06/21.
//

#ifndef LAB6_DYNAMIC_POOL_H
#define LAB6_DYNAMIC_POOL_H

#include <future>
#include <vector>
#include <thread>
#include <mutex>
#include <queue>
#include <map>

using task_t = std::packaged_task<void()>;

class dynamic_pool {
    bool running = true;

    int min_thread;
    int max_thread;

    std::queue<task_t> tasks;
    std::mutex m;  // queue mutex
    std::condition_variable exec_cv; // exec condition variable_

    std::map<std::thread::id, std::thread> threads;

    int free_threads;

    bool should_term(){
        return free_threads > min_thread && tasks.empty();
    }

public:
    dynamic_pool(int min_thread, int max_thread):
        min_thread(min_thread), max_thread(max_thread), free_threads(0) {};

    void schedule(task_t task){
        bool should_start;
        {
            std::unique_lock<std::mutex> lock(m);
            tasks.emplace(move(task));
            should_start = !tasks.empty() && threads.size() < max_thread;
        }

        if(should_start)
            start_thread();
        exec_cv.notify_one();
    }


    void start_thread(){
        auto thread_fun = [this](){
            while(true) {
                task_t task;
                {
                    std::unique_lock lock(m);
                    exec_cv.wait(lock, [this](){ return !tasks.empty() || !running || should_term(); });

                    // if woken up from wait and no tasks to execute, terminate
                    if(tasks.empty()) break;

                    free_threads--;
                    task = std::move(tasks.front());
                    tasks.pop();
                }
                // execute task
                task();
                {
                    std::unique_lock ul(m);
                    free_threads++;
                    exec_cv.notify_one(); // notifica anche i worker per testare se devono uscire
                }
            }

            // exiting
            std::thread::id id = std::this_thread::get_id();
            {
                std::unique_lock l(m);
                if(running) threads[id].detach(); // no one is joining
                threads.erase(id);
                free_threads--;
            }
        };

        /** --- creating the new thread --- **/
        std::thread t(thread_fun);
        {
            // load threads in the pool
            std::unique_lock l(m);
            threads[t.get_id()] = std::move(t);
            free_threads++;
        }
    }

    void finish(){
        std::vector<std::thread> join_threads;
        {
            std::unique_lock l(m);
            running = false;
            for(auto &[id, t]: threads) join_threads.push_back(move(t));
            exec_cv.notify_all();
        }

        for(auto &t: join_threads)
            t.join();
    }
};




#endif //LAB6_DYNAMIC_POOL_H
