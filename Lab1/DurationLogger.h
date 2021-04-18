#include <utility>

//
// Created by elle on 24/03/21.
//

#ifndef LAB1_DURATIONLOGGER_H
#define LAB1_DURATIONLOGGER_H

#include <iostream>
#include <string>

class DurationLogger {

    clock_t t0;
    std::string name;
public:
    explicit DurationLogger(std::string name):name(std::move(name)) {
        t0 = clock();
    }

    ~DurationLogger(){
        std::cout<<"["<<name<<"][duration:"<<clock()-t0<<"]"<<std::endl;
    }
};


#endif //LAB1_DURATIONLOGGER_H
