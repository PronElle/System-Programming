//
// Created by elle on 18/04/21.
//

#ifndef EX2_MYVECTOR_HPP
#define EX2_MYVECTOR_HPP

#include <iostream>

template <class T> // the text asked for a non-template version
class MyVector {
    unsigned int _size;
    T* vec_buf; // internal data structure
public:
    // constructors
    MyVector();
    explicit MyVector(unsigned int size);
    MyVector(unsigned int size, const T & val);
    MyVector(const MyVector<T> & v);

    ~MyVector();

    unsigned int size() const;
    void push_back(const T & val) const;
    void pop_back();
    void clear();
    T & operator[] (unsigned int index);
    T & front();
    T & back();
    bool empty() const;
};

template<class T>
MyVector<T>::MyVector() {
    _size = 0;
    vec_buf = nullptr;
}


/**
 * Initializes vector with given size
 * @tparam T
 * @param size: init size
 */
template<class T>
MyVector<T>::MyVector(unsigned int size) {
    _size = size;
    vec_buf = new T[size];
}


/**
 * initializes vector with given size and given initial val
 * (for all cells)
 * @tparam T
 * @param size: init size
 * @param val: init val
 */
template<class T>
MyVector<T>::MyVector(unsigned int size, const T &val) {
    _size = size;
    vec_buf = new T[size];
    for(int i = 0; i < _size; ++i )
        vec_buf[i] = val;
}

/**
 * copy constructor
 * @tparam T
 * @param v: vector to copy
 */
template<class T>
MyVector<T>::MyVector(const MyVector<T> &v) {
    _size = v._size;
    this->vec_buf = new T[_size];
    for(int i = 0; i < _size; ++i )
        vec_buf[i] = v.vec_buf[i];
}

template<class T>
MyVector<T>::~MyVector(){
    delete[] vec_buf;
}


/**
 * retrieves size of vector
 * @tparam T
 * @return number of elements
 */
template<class T>
unsigned int MyVector<T>::size() const {
    return _size;
}

/**
 * pushes new val to vector
 * @tparam T
 * @param val to be pushed
 */
template<class T>
void MyVector<T>::push_back(const T &val) const {

}

/**
 *
 * @tparam T
 */
template<class T>
void MyVector<T>::pop_back() {

}

/**
 * makes vector empty
 * @tparam T
 */
template<class T>
void MyVector<T>::clear() {

}

/**
 * overload of "[]" operator
 * @tparam T
 * @param index
 * @return vector[index]
 */
template<class T>
T &MyVector<T>::operator[](unsigned int index) {
    return vec_buf[index];
}

/**
 * retrieves front element of vector
 * @tparam T
 * @return front val
 */
template<class T>
T &MyVector<T>::front() {
    return vec_buf[0];
}

/**
 * retrieves back val of vector
 * @tparam T
 * @return back val
 */
template<class T>
T &MyVector<T>::back() {
    return vec_buf[_size - 1];
}

/**
 * detects wether vector is empty or not
 * @tparam T
 * @return true if empty, false otherwise
 */
template<class T>
bool MyVector<T>::empty() const {
    return _size == 0;
}
#endif //EX2_MYVECTOR_HPP


