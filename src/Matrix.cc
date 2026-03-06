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

        double* new_elements = nullptr;
        if (other.rows_ > 0 && other.cols_ > 0) {
            new_elements = new double[other.rows_ * other.cols_];
            std::copy(other.elements_, other.elements_ + other.rows_ * other.cols_, new_elements);
        }

        delete[] elements_;
        elements_ = new_elements;
        rows_ = other.rows_;
        cols_ = other.cols_;

        return *this;

    }

    Matrix::~Matrix(){
        delete[] elements_;
    }

    int Matrix::Rows() const {
        return rows_;
    }

    int Matrix::Cols() const {
        return cols_;
    }

    double& Matrix::operator()(int row, int col)
    {
        if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
            throw std::out_of_range("Matrix index out of bounds");
        }
        return elements_[row * cols_ + col];
    }

    const double& Matrix::operator()(int row, int col) const
    {
        if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
            throw std::out_of_range("Matrix index out of bounds");
        }
        return elements_[row * cols_ + col];
    }

    Matrix Matrix::operator+(const Matrix& other) const{
        if (rows_ != other.rows_ || cols_ != other.cols_) {
            throw std::invalid_argument("For addition, both matrices must have the same dimensions");
        }
        Matrix result(rows_, cols_);
        for (int i = 0; i < rows_ * cols_; ++i) {
            result.elements_[i] = elements_[i] + other.elements_[i];
        }

        return result;
    
    }

    Matrix Matrix::operator-(const Matrix& other) const{
        if (rows_ != other.rows_ || cols_ != other.cols_) {
            throw std::invalid_argument("For addition, both matrices must have the same dimensions");
        }

        Matrix result(rows_, cols_);
        for (int i = 0; i < rows_ * cols_; ++i) {
            result.elements_[i] = elements_[i] - other.elements_[i];
        }

        return result;
    }

    Matrix Matrix::operator*(double scalar) const{
        Matrix result(rows_, cols_);
        for (int i = 0; i < rows_ * cols_; ++i) {
            result.elements_[i] = elements_[i] * scalar;
        }
        return result;
    }

    Matrix Matrix::operator*(const Matrix& other) const{
        if (cols_ != other.rows_) {
            throw std::invalid_argument("Matrix dimensions incompatible for multiplication");
        }

        Matrix result(rows_, other.cols_);
        for (int i = 0; i < rows_; i++){
            for (int j = 0; j < other.cols_; j++){
                double sum = 0.0;
                for (int k = 0; k < cols_; k++){
                    sum += elements_[i * cols_ + k] * other.elements_[k * other.cols_ + j];
                }
                result.elements_[i * other.cols_ + j] = sum;
            }

        }
        return result;

    }

    Matrix Matrix::Transpose() const{
        Matrix result(cols_, rows_);
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                result.elements_[j* rows_ + i] = elements_[i * cols_ + j];
            }
        }
        return result;
    }

    Vector Matrix::operator*(const Vector& other) const {
        if (other.Size() != cols_) {
            throw std::invalid_argument("Vector size must match the number of columns in the matrix");
        }
        Vector result(rows_);
        for (int i = 0; i < rows_; ++i) {
            double sum = 0.0;
            for (int j = 0; j < cols_; ++j) {
                sum += elements_[i * cols_ + j] * other[j];
            }
            result[i] = sum;
        }
        return result;
    }



}