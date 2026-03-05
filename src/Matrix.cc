#include "tinyeigen/Vector.h"
#include "tinyeigen/Matrix.h"

#include <algorithm>
#include <stdexcept>

namespace tinyeigen {

    Matrix::Matrix(int rows, int cols) : elements_(nullptr), rows_(rows), cols_(cols){
        if (rows < 0 || cols < 0) {
            throw std::invalid_argument("Matrix dimensions cannot be negative");
        } 
        if (rows_ > 0 && cols_ > 0) {
            elements_ = new double[rows_ * cols_]();
        }
    }

    Matrix::Matrix(const Matrix& other) : elements_(nullptr), rows_(other.rows_), cols_(other.cols_)
    {
        if (rows_ > 0 && cols_ > 0) {
            elements_ = new double[rows_ * cols_];
            std::copy(other.elements_, other.elements_ + rows_ * cols_, elements_);
        }
    }

    Matrix& Matrix::operator=(const Matrix& other){
        if (this == &other) {
            return *this;
        }
    }
}