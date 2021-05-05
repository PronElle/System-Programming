//
// Created by elle on 22/04/21.
//

#ifndef EX2_MATRIX_HPP
#define EX2_MATRIX_HPP

#endif //EX2_MATRIX_HPP
#include "Row.hpp"

template <typename T>
class Matrix {
public:
    Matrix(const unsigned int &_rows, const unsigned int &_cols);
    Row<T>& operator[](const unsigned int  &index) const;
    unsigned int getRows() const;
    unsigned int getCols() const;
private:
    unsigned int rows;
    unsigned int cols;
    std::unique_ptr<Row<T>[]> mat;
};

template <typename T>
Matrix<T>::Matrix(const unsigned int& _rows, const unsigned int& _cols): mat(new Row<T>[_rows]) {
    rows = _rows;
    cols = _cols;

    for(int i=0; i< rows; i++)
        mat[i] = Row<T>(cols);
}



template <typename T>
std::ostream & operator<<(std::ostream &out, const Matrix<T> &mat) {
    for(int i=0; i< mat.getRows(); i++) {
        for (int j = 0; j < mat.getCols(); j++)
            out << mat[i][j] << ' ';
        out << '\n';
    }
    return out;
}

template <typename T>
Row<T> & Matrix<T>::operator[](const unsigned int& index) const {
    return mat[index];
}

template<typename T>
unsigned int Matrix<T>::getRows() const {
    return rows;
}

template<typename T>
unsigned int Matrix<T>::getCols() const {
    return cols;
}
