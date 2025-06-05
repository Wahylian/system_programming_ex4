// rido1607@gmail.com
#include "complex.hpp"

complex::complex(double r, double i) : real(r), imag(i) {}

double& complex::x() {
    return real;
}

double& complex::y() {
    return imag;
}

const double& complex::x() const {
    return real;
}

const double& complex::y() const {
    return imag;
}

complex complex::operator+(const complex& other) const {
    return complex(real + other.real, imag + other.imag);
}

complex complex::operator-(const complex& other) const {
    return complex(real - other.real, imag - other.imag);
}

complex complex::operator*(const complex& other) const {
    return complex(real * other.real - imag * other.imag, real * other.imag + imag * other.real);
}

complex complex::operator/(const complex& other) const {
    double denominator = other.real * other.real + other.imag * other.imag;
    if (denominator == 0) {
        throw std::runtime_error("Division by zero in complex division");
    }
    return complex((real * other.real + imag * other.imag) / denominator,
                   (imag * other.real - real * other.imag) / denominator);
}

complex complex::operator-() const {
    return complex(-real, -imag);
}

complex& complex::operator+=(const complex& other) {
    real += other.real;
    imag += other.imag;
    return *this;
}

complex& complex::operator-=(const complex& other) {
    real -= other.real;
    imag -= other.imag;
    return *this;
}

complex& complex::operator*=(const complex& other) {
    double tempReal = real * other.real - imag * other.imag;
    imag = real * other.imag + imag * other.real;
    real = tempReal;
    return *this;
}

complex& complex::operator/=(const complex& other) {
    double denominator = other.real * other.real + other.imag * other.imag;
    if (denominator == 0) {
        throw std::runtime_error("Division by zero in complex division");
    }
    double tempReal = (real * other.real + imag * other.imag) / denominator;
    imag = (imag * other.real - real * other.imag) / denominator;
    real = tempReal;
    return *this;
}

bool complex::operator==(const complex& other) const {
    return real == other.real && imag == other.imag;
}

bool complex::operator!=(const complex& other) const {
    return !(*this == other);
}

bool complex::operator>(const complex& other) const {
    return (real > other.real) || (real == other.real && imag > other.imag);
}

bool complex::operator<(const complex& other) const {
    return (real < other.real) || (real == other.real && imag < other.imag);
}

bool complex::operator>=(const complex& other) const {
    return *this > other || *this == other;
}

bool complex::operator<=(const complex& other) const {
    return *this < other || *this == other;
}

std::ostream& operator<<(std::ostream& os, const complex& c) {
    os << c.x() << " + " << c.y() << "i";
    return os;
}