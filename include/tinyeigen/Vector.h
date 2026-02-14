#ifndef TINYEIGEN_VECTOR_H_;
#define TINYEIGEN_VECTOR_H_;

namespace tinyeigen {

    class Vector
    {
    private:
        double* elements_;
        int size_;
    public:
        explicit Vector(int size);
        Vector(const Vector& other);
        Vector& operator=(const Vector& other);

        ~Vector();

        int Size() const;
        double& operator[](int index);
        const double& operator[](int index) const;

        Vector operator+(const Vector& other) const;
        Vector operator-(const Vector& other) const;

        Vector operator*(double scalar);

        double Dot(const Vector& other) const;
    };
    


}

#endif