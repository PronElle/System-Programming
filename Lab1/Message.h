//
// Created by elle on 24/03/21.
//

#ifndef LAB1_MESSAGE_H
#define LAB1_MESSAGE_H

#include <iostream>

class Message {

    long id ;
    char * data ;
    int size ;
    static long curr_id;

   // private members
    char* getData() const;
    static char* mkMessage(int n);

public:
    /* constructors */
    Message(); // default constr
    explicit Message(const long & _size); // constr
    Message(const Message & other); // copy constr
    Message(Message && source) noexcept ; // mov constr

    ~Message();

    /* getters */
    int getSize() const;
    long getId() const;

    /* operator overloads */
    friend std::ostream & operator << (std::ostream & out, const Message &m);
    Message & operator = (const Message &source);
};


#endif //LAB1_MESSAGE_H
