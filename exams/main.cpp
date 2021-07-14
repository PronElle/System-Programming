#include <iostream>
#include <assert.h>

#include "Joiner.h"
#include "CBuffer.h"
#include "Exchanger.h"

void test_joiner(){
    const int N = 5; // N threads
    int iter = 1000; // n computations (each computations provides N samples)
    Joiner joiner(N);

    auto f = [&joiner, N, iter](bool print){
        for (int i = 0 ; i < iter ; i++){
            auto m = joiner.supply(i);
            assert( m.size() == N);
            for(auto p: m){
                if (p.second != i) std::cout << "Expected: " << i << "\tfound: " << p.second << '\n';
                assert(p.second == i);
            }

            if (print) {
                // stampa e a capo ogni 10, solo per vederli meglio
                std::cout << i << " ";
                if ( i % 10 == 9) std::cout << '\n';
            }
        }
    };

    std::thread threads[N];
    for(int i = 0; i < N; i++)
        threads[i] = std::thread(f, i == 0); // solo il primo stampa

    for(auto & t : threads)
        t.join();
}

void test_buffer (){
    const uint16_t  N = 10000; // values to produce
    CBuffer<int> buf;

    std::thread prod([&buf](){
        for(int i = 0 ; i < N; ++i) {
            std::cout << "enqueing: " << i << std::endl;
            buf.next(i);
        }

        buf.terminate();
    });

    std::thread cons([&buf](){
        for(int i = 0; i < N; ++i)
            std::cout << "consuming: " << buf.consume().value() << std::endl;
    });

    prod.join();
    cons.join();
}


// test buffer out of scope
// to show why the destructor is indeed needed
void test_buffer_oos() {
    const uint16_t  N = 10000; // values to produce
    auto threads = std::vector<std::thread>();

    {
        CBuffer<int> buf;

        // producer
        threads.emplace_back([&buf]() {
            for (auto i = 0; i < N; ++i)
                buf.next(i);

            //buf.terminate();
        });

        // consumer
        threads.emplace_back([&buf] () {
            while(true) {
                auto value = buf.consume();
                if (!value) return;
                std::cout << value.value() << std::endl;
            }
        });


    } // buf goes out of scope here, but consumer might be still waiting

    for (auto& t : threads)
        t.join();
}


void test_exchanger(){
    const uint16_t N = 40;
    Exchanger<int> exchanger;
    std::mutex atomic_print;

    auto fun = [ &exchanger, &atomic_print](int val){
        int t = exchanger.exchange(val);
        atomic_print.lock();
        std::cout << "id:\t" << std::this_thread::get_id()
                  << "\tdeposited:\t" << val
                  << "\treceived\t: " << t << '\n';
        atomic_print.unlock();
    };

    std::thread threads[N];
    for(size_t i = 0; i < N; ++i)
        threads[i] = std::thread(fun, i);

    for(auto & t: threads)
        t.join();

    // l'output deve far sì che le coppie siano corrette
    // cioè devono esserci delle coppie del tipo
    // deposita A riceve B
    // deposita B riceve A
    // anche (ovviamente!) non in righe successive
}



int main() {
 //test_joiner();
 //test_buffer();
 // test_buffer_oos();
 test_exchanger();
 return 0;
}