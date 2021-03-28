//
// Created by elle on 24/03/21.
//

#include "DurationLogger.h"

DurationLogger::DurationLogger(const std::string &_name) {
    name = _name;
    start = std::chrono::high_resolution_clock::now();
    std::cout << " >>>>>>>>>>>>>> starting [" << this->name << "]" << std::endl;
}

DurationLogger::~DurationLogger() {
    stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << " <<<<<<<<<<<<<<< ending [" << name << "]: [" << duration.count() << "] millisec " << std::endl;
}
