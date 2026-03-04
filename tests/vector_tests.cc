#include "tinyeigen/Vector.h"

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

int main()
{
    using tinyeigen::Vector;

    Vector a(3);
    a[0] = 1.0;
    a[1] = 2.0;
    a[2] = 3.0;

    if (a.Size() != 3) {
        return Fail("Size() returned wrong value");
    }

    Vector copy(a);
    if (!AlmostEqual(copy[0], 1.0) || !AlmostEqual(copy[1], 2.0) || !AlmostEqual(copy[2], 3.0)) {
        return Fail("Copy constructor failed");
    }

    // Addition
    Vector b(3);
    b[0] = 4.0;
    b[1] = 5.0;
    b[2] = 6.0;

    Vector c = a + b;
    if (!AlmostEqual(c[0], 5.0) || !AlmostEqual(c[1], 7.0) || !AlmostEqual(c[2], 9.0)) {
        return Fail("operator+ failed");
    }

    // Subtraction
    Vector d = b - a;
    if (!AlmostEqual(d[0], 3.0) || !AlmostEqual(d[1], 3.0) || !AlmostEqual(d[2], 3.0)) {
        return Fail("operator- failed");
    }

    // Scalar multiply
    Vector e = a * 2.0;
    if (!AlmostEqual(e[0], 2.0) || !AlmostEqual(e[1], 4.0) || !AlmostEqual(e[2], 6.0)) {
        return Fail("operator* failed");
    }

    // Dot product
    const double dot = a.Dot(b);  // 1*4 + 2*5 + 3*6 = 32
    if (!AlmostEqual(dot, 32.0)) {
        return Fail("Dot() failed");
    }

    std::cout << "[PASS] vector_tests\n";
    return 0;
}
