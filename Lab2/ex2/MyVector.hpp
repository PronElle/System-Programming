//
// Created by elle on 18/04/21.
//

#ifndef EX2_MYVECTOR_HPP
#define EX2_MYVECTOR_HPP

#include <iostream>

template <class T> // the text asked for a non-template version
class MyVector {
    unsigned int _size;
    unsigned int _capacity;
    T* buf; // internal data structure
public:
    // constructors
    MyVector();
    explicit MyVector(unsigned int size);
    MyVector(unsigned int size, const T & val);
    MyVector(const MyVector<T> & v);
    MyVector(MyVector<T> && v) noexcept;

    ~MyVector();

    unsigned int size() const;
    void push_back(T  val) ;
    void pop_back();
    void clear();
    T & front();
    T & back();
    bool empty() const;

    // operator overloads
    T & operator[] (unsigned int index);
    MyVector & operator = (const MyVector<T> &v);
    MyVector & operator = (MyVector<T> && v) noexcept ;
};

template<class T>
MyVector<T>::MyVector() {
    _size = 0;
    _capacity = 0;
    buf = nullptr;
}


/**
 * Initializes vector with given size
 * @tparam T
 * @param size: init size
 */
template<class T>
MyVector<T>::MyVector(unsigned int size) {
    _size = size;
    _capacity = size;
    buf = new T[size];
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
    _capacity = size;
    buf = new T[size];
    for(int i = 0; i < _size; ++i )
        buf[i] = val;
}

/**
 * copy constructor
 * @tparam T
 * @param v: vector to copy
 */
template<class T>
MyVector<T>::MyVector(const MyVector<T> &v) {
    _size = v._size;
    _capacity = v._capacity;
    this->buf = new T[_size];
    for(int i = 0; i < _size; ++i )
        buf[i] = v.buf[i];
}

/**
 * movement constructor
 * @tparam T
 * @param v : to move
 */
template<class T>
MyVector<T>::MyVector(MyVector<T> &&v) noexcept {
    _size = v._size;
    _capacity = v._capacity;
    buf = v.buf;

    v.buf = nullptr;
    v._size = 0;
    v._capacity = 0;
}


template<class T>
MyVector<T>::~MyVector(){
    delete[] buf;
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
void MyVector<T>::push_back(T val)  {
  if(_size == _capacity){
      // reallocating
      _capacity ++; // as requested
      T* tmp = new T[_capacity];

      // copying vals
      for(int i = 0; i < _size; ++i)
          tmp[i] = buf[i];

      // storing val
      tmp[_size] = val;
      _size++;

      delete[] buf;
      buf = tmp;
  }else
      buf[_size++] = val;
}

/**
 *
 * @tparam T
 */
template<class T>
void MyVector<T>::pop_back() {
    if(_size > 0) _size --;
}

/**
 * makes vector empty
 * (but it doesn't frees the memory yet)
 * @tparam T
 */
template<class T>
void MyVector<T>::clear() {
 // TODO: to be implemented
}

/**
 * overload of "[]" operator
 * @tparam T
 * @param index
 * @return vector[index]
 */
template<class T>
T &MyVector<T>::operator[](unsigned int index) {
    if(index > _size - 1 || index < 0)
        throw std::out_of_range("out of scope");

    return buf[index];
}

/**
 * overload of "=" operator
 * @tparam T
 * @param v : vector to assign
 * @return
 */
template<class T>
MyVector<T> &MyVector<T>::operator=(const MyVector<T> &v)  {
    // TODO: to be implemented
}

/**
 * overload of "=" operator
 * @tparam T
 * @param v
 * @return
 */
template<class T>
MyVector<T> & MyVector<T>::operator=(MyVector<T> &&v) noexcept{
    // TODO: to be implemented
}

/**
 * retrieves front element of vector
 * @tparam T
 * @return front val
 */
template<class T>
T &MyVector<T>::front() {
    return buf[0];
}

/**
 * retrieves back val of vector
 * @tparam T
 * @return back val
 */
template<class T>
T &MyVector<T>::back() {
    if(_size > 0)
        return buf[_size - 1];
    else
        throw std::logic_error("vector is empty");
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


