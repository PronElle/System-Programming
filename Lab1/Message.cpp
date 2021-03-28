//
// Created by elle on 24/03/21.
//

#include "Message.h"

long Message::curr_id = 0;

Message::Message():id(-1), size(0), data(mkMessage(0)){}

/**
 * initializes new message object
 * with
 *  - given size
 *  - incremental id
 *  - pseudo-random content
 * @param _size
 */
Message::Message(const long &_size){
    id = curr_id++;
    size = _size;
    data = mkMessage(size);
}

/**
 * copy constructor
 * @param other
 */
Message::Message(const Message &other) {
    id = other.id;
    size = other.size;

    if(other.data != nullptr){
        data = new (std::nothrow) char [size + 1];
        if(data != nullptr)
            *data = *other.data;
    } else
        data = nullptr;
}

/**
 * movement constructor
 * @param source
 */
Message::Message(Message &&source) noexcept {
    this->id = source.id;
    this->size = source.size;
    this->data = source.data;
    source.data = nullptr;
}

/**
 * destroys data pointer
 */
Message::~Message() {
  if(data != nullptr){
      delete[] data;
      data = nullptr;
  }
}


/**
 * @brief retrieves id
 * @param None
 * @return id
 */
long Message::getId() const{
    return id;
}

/**
 * @brief retrieves data
 * @param None
 * @return data
 */
char *Message::getData() const{
    return data;
}

/**
 * @brief retrieves size
 * @param None
 * @return size
 */
int Message::getSize() const{
    return size;
}

/**
 * @brief static member generating a pseudo-rand msg
 * @param n: msg size
 * @return message
 */
char *Message::mkMessage(int n) {
    std::string vowels = "aeiou" ;
    std::string consonants = "bcdfghlmnpqrstvz" ;
    char * m = new (std::nothrow) char [n+1];
    if ( m != nullptr ) {
        for (int i = 0; i < n ; i ++)
            m[i] = i % 2 ? vowels [rand() % vowels.size()] :
                             consonants [rand() % consonants.size()];

        m[n] = '\0';
    }
    return m;
}


/**
 * overloaded << operator
 * @param out
 * @param m: msg to print
 * @return
 */
std::ostream & operator<< (std::ostream & out, const Message &m) {
    std::string s ( m.getData ());
    out <<" [id:" << m.getId () << "] [size:"
        << m.getSize() <<"] [data:"
        << s.substr(0 , 20) << "]" ;
    return out ;
}

/**
 * overloaded = operator
 * @param source : msg to assign
 * @return
 */
Message &Message::operator=(const Message &source) {
    if (this != &source) {
        delete[] this->data;
        this->data = nullptr;
        this->id = source.id;
        this->size = source.size;
        this->data = new (std::nothrow) char[this->size];

        if(this->data != nullptr)
            *data = *source.data;
    }

    return *this;
}










