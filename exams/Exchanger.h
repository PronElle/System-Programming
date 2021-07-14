//
// Created by elle on 14/07/21.
//

#ifndef EXAMS_EXCHANGER_H
#define EXAMS_EXCHANGER_H

#include <mutex>
#include <thread>
#include <condition_variable>

/** 19/06/21
 *  La classe generica Exchanger<T> permette a due thread di scambiarsi un valore di
 *  tipo T. Essa offre esclusivamente il metodo pubblico T exchange( T t) che blocca il
 *  thread chiamante senza consumare CPU fino a che un altro thread non invoca lo
 *  stesso metodo, sulla stessa istanza. Quando questo avviene, il metodo restituisce
 *  l’oggetto passato come parametro dal thread opposto.
 *  Si implementi tale classe, usando la libreria standard C++11.
 **/


template <typename T>
class Exchanger {
    std::mutex m;
    std::condition_variable cv;
    bool set, entering;
    T val;
public:
    Exchanger() : set(false), entering(true) {}

    T exchange(T t){
        std::unique_lock ul(m);
        // doppia porta
        cv.wait(ul, [this]() { return entering; });

        // prendo il mutex
        if(set) { // se ho già settato val
            T copy = val;
            val = t;
            entering = false;
            cv.notify_all();
            return copy;
        }else {  // primo thread
            val = t; // deposito il valore
            set = true; // lo marco settato
            cv.wait(ul, [this]() { return !entering; });
            entering = true;
            set = false;
            cv.notify_all();
            return val;
        }
    }
};


#endif //EXAMS_EXCHANGER_H
