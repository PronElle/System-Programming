#include <iostream>
#include "Message.h"
#include "MessageStore.h"
#include "DurationLogger.h"

int main() {
    MessageStore ms(10);

    for(auto i = 0; i < 100; ++i){
        Message m = Message(10*1024*1024);
        ms.add(m);
    }

    for(auto i = 0; i < 100 ; i += 2)
        ms.remove(i);



    return 0;
}