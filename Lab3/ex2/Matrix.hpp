//
// Created by elle on 22/04/21.
//

#ifndef EX2_MATRIX_HPP
#define EX2_MATRIX_HPP

#endif //EX2_MATRIX_HPP
#include "Row.hpp"

template <typename T, typename R>
class Matrix {
public:
    Matrix(R _rows, R _cols);
    Row<T, R>& operator[](R index) const;
    R getRows() const;
    R getCols() const;
private:
    R rows;
    R cols;
    std::unique_ptr<Row<T, R>[]> mat;
};

template <typename T, typename R>
Matrix<T, R>::Matrix(R _rows, R _cols): mat(new Row<T,R>[_rows]) {
    rows = _rows;
    cols = _cols;

    for(R i=0; i< rows; i++) {
        mat[i] = Row<T,R>(cols);
    }
}



template <typename T, typename R>
std::ostream & operator<<(std::ostream &out, const Matrix<T, R> &mat) {
    for(R i=0; i< mat.getRows(); i++) {
        for (R j = 0; j < mat.getCols(); j++)
            out << mat[i][j] << ' ';
        out << '\n';
    }
    return out;
}

template <typename T, typename R>
Row<T, R> & Matrix<T, R>::operator[](R index) const {
    return mat[index];
}

template<typename T, typename R>
R Matrix<T, R>::getRows() const {
    return rows;
}

template<typename T, typename R>
R Matrix<T, R>::getCols() const {
    return cols;
}
