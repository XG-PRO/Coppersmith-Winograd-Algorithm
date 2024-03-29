#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>

/*                     COMPLEX NUMBERS
 *
 *  The following code is an implementation of a trivially
 *  copyable  class for complex numbers. It is accepted as
 *  template parameter for the algebra::matrix class.
 */

namespace algebra
{
    class complex {
    protected:
        double a;	// Real part
        double b;	// Imaginary part

    public:	// Constructors
        complex();
        complex(double);
        complex(double, double);
        complex(const complex&) = default;
        ~complex() = default;

    public:	// Methods
        void set_real(double a) { this->a = a; }
        void set_imaginary(double b) { this->b = b; }

        double real() const { return a; }
        double imaginary() const { return b; }

    public:	// Operators
        complex& operator += (const complex&);
        complex& operator -= (const complex&);
        complex& operator /= (const complex&);
        complex& operator *= (const complex&);
    };

    // Operators
    complex operator + (const complex&, const complex&);
    complex operator - (const complex&, const complex&);
    complex operator * (const complex&, const complex&);
    complex operator / (const complex&, const complex&);
    std::istream& operator >> (std::istream&, complex&);
    std::ostream& operator << (std::ostream&, const complex&);


    // --- BLUEPRINTS ---

    // Empty Constructor
    complex::complex() {
        a = 0;
        b = 0;
    }
    // Converting Constructors
    complex::complex(double a, double b) {
        this->a = a;
        this->b = b;
    }
    complex::complex(double k) {
        this->a = k;
        this->b = 0;
    }


    // --- OPERATORS ---


    // Plus-equals operator
    complex& complex::operator += (const complex& arg) {
        a += arg.a;
        b += arg.b;
        return *this;
    }

    // Minus-equals operator
    complex& complex::operator -= (const complex& arg) {
        a -= arg.a;
        b -= arg.b;
        return *this;
    }

    // Times-equals operator
    complex& complex::operator *= (const complex& arg) {
        double c = arg.a;
        double d = arg.b;

        a = a * c - b * d;
        b = a * d + b * c;

        return *this;
    }

    // Divided-equals operator
    complex& complex::operator /= (const complex& arg) {
        double c = arg.a;
        double d = arg.b;
        double a_prev = this->real();

        a = (a * c + b * d) / (c * c + d * d);
        b = (b * c - a_prev * d) / (c * c + d * d);

        return *this;
    }

    // Addition operator
    complex operator + (const complex& one, const complex& two) {
        complex sum;
        sum.set_real(one.real() + two.real());
        sum.set_imaginary(one.imaginary() + two.imaginary());
        return sum;
    }

    // Subtraction operator
    complex operator - (const complex& one, const complex& two) {
        complex diff;
        diff.set_real(one.real() - two.real());
        diff.set_imaginary(one.imaginary() - two.imaginary());
        return diff;
    }

    // Multiplication operator
    complex operator * (const complex& one, const complex& two) {
        complex prod;

        // one = a + bi
        double a = one.real();
        double b = one.imaginary();
        // two = c + di
        double c = two.real();
        double d = two.imaginary();

        // one * two = (a*c - b*d) + (a*d + b*c)i
        prod.set_real(a * c - b * d);
        prod.set_imaginary(a * d + b * c);

        return prod;
    }

    // Division operator
    complex operator / (const complex& one, const complex& two) {
        complex div;

        // one = a + bi
        double a = one.real();
        double b = one.imaginary();
        // two = c + di
        double c = two.real();
        double d = two.imaginary();

        // one / two = [ (a*c + b*d) + (b*c - a*d)i ] / (c^2 + d^2)
        div.set_real((a * c + b * d) / (c * c + d * d));
        div.set_imaginary((b * c - a * d) / (c * c + d * d));

        return div;
    }

    // Input stream operator
    std::istream& operator >> (std::istream& is, complex& arg) {
        double a;
        double b;

        is >> a >> b;
        arg.set_real(a);
        arg.set_imaginary(b);

        return is;
    }

    // Output stream operator
    std::ostream& operator << (std::ostream& os, const complex& arg) {
        double b_abs = abs(arg.imaginary());

        os << arg.real();
        if (b_abs != 0) {
            os << (arg.imaginary() > 0 ? " + " : " - ");
            if (b_abs != 1) {
                os << b_abs;
            }
            os << "i";
        }
        return os;
    }
}

#endif // COMPLEX_H