#include <iostream>
#include "Matrix.hpp"
#define COL 10
#define ROW 15

int main() {
    Matrix<int, int> mat(ROW,COL);

    for(int i = 0 ; i < ROW; ++i)
        for(int j = 0; j < COL; ++j)
            mat[i][j] = i*j + 5; // random val


    std::cout << mat;
    return 0;
}