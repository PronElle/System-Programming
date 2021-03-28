//
// Created by elle on 24/03/21.
//

#ifndef LAB1_DURATIONLOGGER_H
#define LAB1_DURATIONLOGGER_H
#include <iostream>
#include <chrono>

class DurationLogger {
    std::string name;
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    std::chrono::time_point<std::chrono::high_resolution_clock> stop;

public:
    DurationLogger(const std::string & _name);
    ~DurationLogger();
};


#endif //LAB1_DURATIONLOGGER_H
