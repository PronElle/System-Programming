#include <iostream>
#include <functional>
#include <thread>
#include <cmath>
#include "myptask.h"


void test_ptask(){
    auto test = [](double v1, double v2) {
        return v2 != 0 ? v1/v2 : std::numeric_limits<double>::quiet_NaN();
    };

    MyPackagedTask ptask(std::move(test), 8, 5);
    std::future f = ptask.get_future();

    // receives and executes the function embedded
    // in the packaged task
    std::thread t([&ptask](){
        ptask(); // execute the task
    });

    t.detach();
    std::cout << "result: " << f.get() ;
}



int main() {
    test_ptask();
    return 0;
}
