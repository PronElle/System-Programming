#include <iostream>
#include "Matrix.hpp"
#define COL 10
#define ROW 15

void test_with_strings(){
    Matrix<std::string> mat(ROW,COL);

    for(int i = 0 ; i < ROW; ++i)
        for(int j = 0; j < COL; ++j)
            mat[i][j] = i*j ? "ciao" + std::to_string(j) : "ciaone" + std::to_string(i) ; // random val

    std::cout << mat;
}


void test_with_double(){
    Matrix<double> mat(ROW, COL);
    for(int i = 0 ; i < ROW; ++i)
        for(int j = 0; j < COL; ++j)
            mat[i][j] = i*j + 5 ; // random val

    std::cout << mat;

}


class Foo{
    int a;
public:
    Foo(){}
    explicit Foo(const int & _a) { a = _a; }
    ~Foo()= default;;
    int getA() const { return a; }
};

std::ostream & operator<< (std::ostream &out, const Foo &f) {
    out << f.getA();
    return out;
}


void test_with_class(){
    Matrix<Foo> mat(ROW, COL);

    for(int i = 0; i < ROW; ++i)
        for(int j=0; j<COL; ++j) {
            Foo f(i*j);
            mat[i][j] = f;
        }

    std::cout << mat;
}

int main() {
    std::cout << "------- with string -------\n";
    test_with_strings();
    std::cout << "------- with double -------\n";
    test_with_double();
    std::cout << "------- with custom class -------\n";
    test_with_class();
    return 0;
}