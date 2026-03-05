#ifndef TINYEIGEN_MATRIX_H_
#define TINYEIGEN_MATRIX_H_

namespace tinyeigen {

    class Matrix
    {
        private:
            double* elements_;
            int rows_;
            int cols_;
        public:
            Matrix(int rows, int cols);
            Matrix(const Matrix& other);
            Matrix& operator=(const Matrix& other);

            ~Matrix();

            int Rows() const;
            int Cols() const;

            double& operator()(int row, int col);
            const double& operator()(int row, int col) const;

            Matrix operator+(const Matrix& other) const;
            Matrix operator-(const Matrix& other) const;
            Matrix operator*(double scalar) const;
            Matrix operator*(const Matrix& other) const;

    };

}



#endif