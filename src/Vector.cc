#include "tinyeigen/Vector.h"

#include <algorithm>
#include <stdexcept>

namespace tinyeigen {

    Vector::Vector(int size)
        : elements_(nullptr), size_(size)
    {
        if (size < 0) {
            throw std::invalid_argument("Vector size cannot be negative");
        }

        if (size_ > 0) {
            elements_ = new double[size_]();
        }
    }

    Vector::Vector(const Vector& other)
        : elements_(nullptr), size_(other.size_)
    {
        if (size_ > 0) {
            elements_ = new double[size_];
            std::copy(other.elements_, other.elements_ + size_, elements_);
        }
    }

    Vector& Vector::operator=(const Vector& other)
    {
        if (this == &other) {
            return *this;
        }

        double* new_elements = nullptr;
        if (other.size_ > 0) {
            new_elements = new double[other.size_];
            std::copy(other.elements_, other.elements_ + other.size_, new_elements);
        }

        delete[] elements_;
        elements_ = new_elements;
        size_ = other.size_;

        return *this;
    }

    Vector::~Vector()
    {
        delete[] elements_;
    }

    int Vector::Size() const
    {
        return size_;
    }

    double& Vector::operator[](int index)
    {
        if (index < 0 || index >= size_) {
            throw std::out_of_range("Vector index out of bounds");
        }
        return elements_[index];
    }

    const double& Vector::operator[](int index) const
    {
        if (index < 0 || index >= size_) {
            throw std::out_of_range("Vector index out of bounds");
        }
        return elements_[index];
    }

    Vector Vector::operator+(const Vector& other) const
    {
        if (size_ != other.size_) {
            throw std::invalid_argument("Vector sizes must match for addition");
        }

        Vector result(size_);
        for (int i = 0; i < size_; ++i) {
            result.elements_[i] = elements_[i] + other.elements_[i];
        }

        return result;
    }

    Vector Vector::operator-(const Vector& other) const
    {
        if (size_ != other.size_) {
            throw std::invalid_argument("Vector sizes must match for subtraction");
        }

        Vector result(size_);
        for (int i = 0; i < size_; ++i) {
            result.elements_[i] = elements_[i] - other.elements_[i];
        }

        return result;
    }

    Vector Vector::operator*(double scalar) const
    {
        Vector result(size_);
        for (int i = 0; i < size_; ++i) {
            result.elements_[i] = elements_[i] * scalar;
        }

        return result;
    }

    double Vector::Dot(const Vector& other) const
    {
        if (size_ != other.size_) {
            throw std::invalid_argument("Vector sizes must match for dot product");
        }

        double sum = 0.0;
        for (int i = 0; i < size_; ++i) {
            sum += elements_[i] * other.elements_[i];
        }

        return sum;
    }
}



