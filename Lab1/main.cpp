#include <iostream>

#include "Message.h"
#include "MessageStore.h"
#include "DurationLogger.h"

using namespace std;

int main() {
    MessageStore ms(10);

    DurationLogger dl("assign");
    // loading 100 messages of 10MB each
    for(auto i = 0; i < 100; ++i){
        Message m = Message(10*1024*1024);
        ms.add(m);
    }

    auto st = ms.stats();

    // printing stats
    std::cout << std::get<0>(st) << "\t" <<  std::get<1>(st) << std::endl;

    // removing 50 messages
    for(auto i = 0; i < 100 ; i += 2)
        ms.remove(i);

    // compacting the array
    ms.compact();

    // getting new stats
    st = ms.stats();

    // printing new stats
    std::cout << std::get<0>(st) << "\t" <<  std::get<1>(st) << std::endl;

    return 0;
}

