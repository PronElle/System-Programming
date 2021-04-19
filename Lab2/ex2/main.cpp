#include <iostream>
#include "MyVector.hpp"

int main() {
    MyVector<int> v;

    v.push_back(5);
    v.push_back(10);

    for(int i = 0; i < 10; ++i)
        v.push_back(i);

    for(int i = 0; i < v.size(); ++i)
        std::cout << v[i] << " ";

    v.pop_back();
    std::cout << "\nafter pop_back: \n";
    for(int i = 0; i < v.size(); ++i)
        std::cout << v[i] << " ";

    return 0;
}