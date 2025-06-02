#pragma once
#include <iostream>
struct complex
{
    private:
        double real;   // Real part of the complex number
        double imag;   // Imaginary part of the complex number

    public:
        // Constructor to initialize complex number
        complex(double r = 0.0, double i = 0.0);

        // gets a reference to the real part of the complex number
        double& x();

        // gets a reference to the imaginary part of the complex number
        double& y();

        // gets a const reference to the real part of the complex number
        const double& x() const;

        // get a const reference to the imaginary part of the complex number
        const double& y() const;

        // Overload the addition operator
        complex operator+(const complex& other) const;

        // Overload the subtraction operator
        complex operator-(const complex& other) const;

        // Overload the multiplication operator
        complex operator*(const complex& other) const;

        // Overload the division operator
        complex operator/(const complex& other) const;

        // Overload the unary minus operator
        complex operator-() const;

        // Overload the addition assignment operator
        complex& operator+=(const complex& other);

        // Overload the subtraction assignment operator
        complex& operator-=(const complex& other);

        // Overload the multiplication assignment operator
        complex& operator*=(const complex& other);

        // Overload the division assignment operator
        complex& operator/=(const complex& other);

        // Overload the equality operator
        bool operator==(const complex& other) const;

        // Overload the inequality operator
        bool operator!=(const complex& other) const;

        // Overload the > operator
        bool operator>(const complex& other) const;

        // Overload the < operator
        bool operator<(const complex& other) const;

        // Overload the >= operator
        bool operator>=(const complex& other) const;

        // Overload the <= operator
        bool operator<=(const complex& other) const;

        // Overload the output stream operator for easy printing 
        friend std::ostream& operator<<(std::ostream& os, const complex& c);

};
