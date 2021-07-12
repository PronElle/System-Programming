//
// Created by elle on 05/06/21.
//

#ifndef LAB5_MYLOCKGUARD_H
#define LAB5_MYLOCKGUARD_H

#include <mutex>

class MyLockGuard {
   std::mutex *m;
public:
    MyLockGuard(const MyLockGuard &mlg) = delete;
    MyLockGuard & operator = (const MyLockGuard & mlg) = delete;

    explicit  MyLockGuard(std::mutex & m): m(&m) {
        // acquire the lock when the object is constructed
        this->m->lock();
    }

    MyLockGuard & operator = (MyLockGuard && other) noexcept {
        if(this != &other) {
            m->unlock();
            m = other.m;
            other.m = nullptr;
        }
        return *this;
    }

    ~MyLockGuard(){
        // release the lock when the object
        // is destroyed
        if(m != nullptr) m->unlock();
    }


};


#endif //LAB5_MYLOCKGUARD_H
