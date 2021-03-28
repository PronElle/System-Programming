//
// Created by elle on 24/03/21.
//

#ifndef LAB1_MESSAGESTORE_H
#define LAB1_MESSAGESTORE_H

#include "Message.h"
#include <optional>
#include <tuple>
#include <cstdio>


class MessageStore {
    Message* messages;
    int dim; // current array size
    int n;  // mem increment
    int next_pos; // next free pos

    // private members
    bool find(long id);
    void resize();

public:
    explicit MessageStore(int n);
    ~MessageStore();

    void add(Message &m);

    std::optional<Message> get(long id);
    bool remove(long id);

    std::tuple<int, int> stats();
    void compact();
};


#endif //LAB1_MESSAGESTORE_H
