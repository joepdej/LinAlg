#include "tinyeigen/Vector.h"
#include "tinyeigen/Matrix.h"

#include <cmath>
#include <iostream>

namespace {
    bool AlmostEqual(double a, double b, double eps = 1e-12)
    {
        return std::fabs(a - b) < eps;
    }

    int Fail(const char* message)
    {
        std::cerr << "[FAIL] " << message << '\n';
        return 1;
    }

}

int main(){
        using tinyeigen::Matrix;

        Matrix m2(3, 3);

        m2(0, 0) = 1.0; m2(0, 1) = 2.0; m2(0, 2) = 3.0;
        m2(1, 0) = 4.0; m2(1, 1) = 5.0; m2(1, 2) = 6.0;
        m2(2, 0) = 7.0; m2(2, 1) = 8.0; m2(2, 2) = 9.0;



        Matrix m(2, 3);
        if (m.Rows() != 2 || m.Cols() != 3) {
            return Fail("Rows()/Cols() returned wrong values");
        }

        // Element assignment and retrieval
        m(0, 0) = 1.0;
        m(0, 1) = 2.0;
        m(0, 2) = 3.0;
        m(1, 0) = 4.0;
        m(1, 1) = 5.0;
        m(1, 2) = 6.0;

        if (!AlmostEqual(m(0, 0), 1.0) || !AlmostEqual(m(1, 2), 6.0)) {
            return Fail("Element access failed");
        }

        // Copy constructor
        Matrix copy(m);
        if (!AlmostEqual(copy(0, 1), 2.0) || !AlmostEqual(copy(1, 0), 4.0)) {
            return Fail("Copy constructor failed");
        }

        // Assignment operator
        Matrix assigned(1, 1);
        assigned = m;
        if (!AlmostEqual(assigned(0, 2), 3.0) || !AlmostEqual(assigned(1, 1), 5.0)) {
            return Fail("Assignment operator failed");
        }

        // Addition
        Matrix addend(2, 3);
        addend(0, 0) = 10.0;
        addend(0, 1) = 20.0;
        addend(0, 2) = 30.0;
        addend(1, 0) = 40.0;
        addend(1, 1) = 50.0;
        addend(1, 2) = 60.0;

        Matrix sum = m + addend;
        if (!AlmostEqual(sum(0, 0), 11.0) || !AlmostEqual(sum(1, 2), 66.0)) {
            return Fail("operator+ failed");
        }

        // Subtraction
        Matrix diff = addend - m;
        if (!AlmostEqual(diff(0, 0), 9.0) || !AlmostEqual(diff(1, 2), 54.0)) {
            return Fail("operator- failed");
        }

        // Scalar multiplication
        Matrix scaled = m * 2.0;
        if (!AlmostEqual(scaled(0, 2), 6.0) || !AlmostEqual(scaled(1, 1), 10.0)) {
            return Fail("operator*(double) failed");
        }

        // Matrix multiplication: (2x3) * (3x2) = (2x2)
        Matrix rhs(3, 2);
        rhs(0, 0) = 7.0;
        rhs(0, 1) = 8.0;
        rhs(1, 0) = 9.0;
        rhs(1, 1) = 10.0;
        rhs(2, 0) = 11.0;
        rhs(2, 1) = 12.0;

        Matrix prod = m * rhs;
        if (prod.Rows() != 2 || prod.Cols() != 2) {
            return Fail("operator*(Matrix) returned wrong dimensions");
        }
        if (!AlmostEqual(prod(0, 0), 58.0) || !AlmostEqual(prod(0, 1), 64.0) ||
            !AlmostEqual(prod(1, 0), 139.0) || !AlmostEqual(prod(1, 1), 154.0)) {
            return Fail("operator*(Matrix) returned wrong values");
        }

        // Bounds checks
        bool threw_out_of_range = false;
        try {
            (void)m(2, 0);
        } catch (const std::out_of_range&) {
            threw_out_of_range = true;
        }
        if (!threw_out_of_range) {
            return Fail("operator() should throw on out-of-range access");
        }

        // Dimension mismatch checks
        bool threw_invalid_argument = false;
        try {
            Matrix wrong(4, 1);
            (void)(m + wrong);
        } catch (const std::invalid_argument&) {
            threw_invalid_argument = true;
        }
        if (!threw_invalid_argument) {
            return Fail("operator+ should throw on mismatched dimensions");
        }

        threw_invalid_argument = false;
        try {
            Matrix wrong_mul(4, 2);
            (void)(m * wrong_mul);
        } catch (const std::invalid_argument&) {
            threw_invalid_argument = true;
        }
        if (!threw_invalid_argument) {
            return Fail("operator*(Matrix) should throw on incompatible dimensions");
        }

        std::cout << "[PASS] matrix_tests\n";
        return 0;
}

