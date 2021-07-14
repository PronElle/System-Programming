//
// Created by elle on 14/07/21.
//

#ifndef EXAMS_JOINER_H
#define EXAMS_JOINER_H

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <map>

class Joiner {
private:
    std::mutex _m;
    std::condition_variable _cv;
    int _N;
    int count;
    std::map<std::thread::id, double> _map;
    bool newcomputation;

public:
    explicit Joiner(int N): _N(N), count(0), newcomputation(true) {}

    std::map<std::thread::id, double> supply(double value){
        std::unique_lock lock(_m);

        // doppia porta : avoid last thread being "too" fast
        // the thread passes this door only if a "clean" computation
        // started

        _cv.wait(lock, [this](){ return newcomputation;});
        // enter critic section, place data in the map
        _map[std::this_thread::get_id()] = value;

        if(++count < _N)
            // wait until wakeup using lambda to avoid unwanted wakeups
            _cv.wait(lock, [this]() { return !newcomputation; });
        else {
            // wakeup all threads
            _cv.notify_all();
            // set newcomputation to false to make sure all threads
            // are actually waken up
            newcomputation = false;
        }

        if( --count == 0) { // each thread waken up decreases count
            // ready for new computation
            newcomputation = true;
            _cv.notify_all();

            // employing the copy constructor to create a new map
            std::map<std::thread::id, double> _mapcpy(_map);
            // clear previous map for next iterations
            _map.clear();
            return _mapcpy;
        }


        return _map;
    }
};


#endif //EXAMS_JOINER_H
