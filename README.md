# TinyEigen

A tiny, dependency-free C++ linear-algebra library for dense vectors and matrices.

[!NOTE]
Student Project: This is a personal side project I’m developing to deepen my understanding of C++, linear algebra internals, and library design. It prioritizes readability and ease of use over the hyper-optimized performance of industrial-grade libraries like Eigen or OpenBLAS.

## Features

- **Vector** – element access, addition, subtraction, scalar multiplication, dot product, norm, normalisation, vector × matrix multiplication
- **Matrix** – element access, addition, subtraction, scalar multiplication, matrix × matrix multiplication, transpose, matrix × vector multiplication
- No external dependencies – only the C++ standard library

## Requirements

| Tool  | Minimum version |
|-------|-----------------|
| C++ compiler | C++17 |
| CMake | 3.23 |

## Building

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

### Running tests

```bash
ctest --test-dir build --output-on-failure
```

### Installing

```bash
cmake --install build --prefix /usr/local   # or any prefix you prefer
```

## Usage

### Using with CMake (`find_package`)

After installing, consume the library from another CMake project:

```cmake
find_package(tinyeigen 0.1 REQUIRED)
target_link_libraries(myapp PRIVATE tinyeigen::tinyeigen)
```

### Using as a subdirectory

Add this repository as a git submodule or copy it into your project tree, then:

```cmake
add_subdirectory(LinAlg)
target_link_libraries(myapp PRIVATE tinyeigen::tinyeigen)
```

### Quick example

```cpp
#include "tinyeigen/Vector.h"
#include "tinyeigen/Matrix.h"

int main()
{
    using tinyeigen::Vector;
    using tinyeigen::Matrix;

    // Vectors
    Vector a(3);
    a[0] = 1.0; a[1] = 2.0; a[2] = 3.0;

    Vector b(3);
    b[0] = 4.0; b[1] = 5.0; b[2] = 6.0;

    Vector c = a + b;          // element-wise addition
    double  d = a.Dot(b);     // dot product  → 32
    double  n = a.Norm();     // L2 norm      → √14
    Vector  u = a.Normalize(); // unit vector

    // Matrices
    Matrix m(2, 2);
    m(0, 0) = 1.0; m(0, 1) = 2.0;
    m(1, 0) = 3.0; m(1, 1) = 4.0;

    Matrix t = m.Transpose();
    Matrix s = m * 2.0;       // scalar multiplication
    Matrix p = m * m;         // matrix multiplication

    // Matrix × Vector
    Vector v(2);
    v[0] = 1.0; v[1] = 2.0;
    Vector r = m * v;         // → [5, 11]

    return 0;
}
```

## License

This project is licensed under the [MIT License](LICENSE).