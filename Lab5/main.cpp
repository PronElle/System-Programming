#include <iostream>
#include <thread>
#include <fstream>
#include <vector>
#include "CountingSemaphore.h"

void semaphore_test(){
    uint8_t count = 4;
    uint8_t Nthreads = 8;

    std::ifstream ifs("loremipsum.txt");
    std::string to_find = "Aenean";
    std::vector<int> matches; // store the results (line numbers)
    unsigned nline = 0;

    // synch objects
    CountingSemaphore cs(count);
    std::thread threads[Nthreads];
    std::mutex line_m;
    std::mutex res_m;

    auto findInFile  = [&cs, &res_m, &line_m, &ifs, to_find, &matches, &nline](){
        while(true){
            cs.acquire();
            std::string s;
            unsigned int _nline;
            {
                std::lock_guard lg{line_m};
                if(!getline(ifs, s)){
                    cs.release();
                    break;
                }
                _nline = nline++;
            }

            if(s.find(to_find) != std::string::npos) {
                std::lock_guard lg{res_m};
                matches.push_back(_nline);
            }
            cs.release();
        }
    };

    for(size_t i = 0; i < Nthreads; ++i)
        threads[i] = std::thread(findInFile);

    for (auto &t : threads)
        t.join();

    for(auto lnum : matches)
        std::cout << "line " << lnum << " matched\n";
}


int main() {
    semaphore_test();
    return 0;
}