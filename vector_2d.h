#ifndef VECTOR_2D_H
#define VECTOR_2D_H

#ifndef PI
#	define PI 3.14159265358979323846
#endif

#include <iostream>
#include <cmath>
#include <string>

namespace algebra 
{
	class vector_2d 
	{
	protected:
		double x;
		double y;

	public:
		vector_2d();
		vector_2d(double, double);
		vector_2d(const vector_2d&);
		
	public:
		void set_x(double x) { this->x = x; }
		void set_y(double y) { this->y = y; }

		double xcor() const { return x; }
		double ycor() const { return y; }

		virtual double magnitude() const;
		double angle_deg() const;
		double angle_rad() const;

	public:
		vector_2d& operator = (const vector_2d&);
		vector_2d& operator += (const vector_2d&);
		vector_2d& operator -= (const vector_2d&);
		vector_2d& operator *= (double);
		vector_2d& operator /= (double);
	};

	std::ostream& operator << (std::ostream&, const vector_2d&);
	vector_2d operator + (const vector_2d&, const vector_2d&);
	vector_2d operator - (const vector_2d&, const vector_2d&);
	vector_2d operator * (double, const vector_2d&);
	vector_2d operator * (const vector_2d&, double);
	double operator * (const vector_2d&, const vector_2d&);


	// --- BLUEPRINTS ---

	// Empty Constructor
	vector_2d::vector_2d() {
		x = 0;
		y = 0;
	}

	// Explicit Constructor
	vector_2d::vector_2d(double x, double y) {
		this->x = x;
		this->y = y;
	}

	// Copy Constructor
	vector_2d::vector_2d(const vector_2d& prototype) {
		x = prototype.x;
		y = prototype.y;
	}


	// --- METHODS ---

	// Returns the magnitude of vector
	double vector_2d::magnitude() const {
		return sqrt(x * x + y * y);
	}

	// Returns the angle formed by the vector and the horizontal axis [IN RADIANS]
	double vector_2d::angle_rad() const {
		return atan2(y, x);
	}

	// Returns the angle formed by the vector and the horizontal axis [IN DEGREES]
	double vector_2d::angle_deg() const {
		return (180 * angle_rad()) / PI;
	}


	// --- OPERATORS ---

	// Assignment operator
	vector_2d& vector_2d::operator = (const vector_2d& arg) 
	{
		if (this != &arg) {
			x = arg.x;
			y = arg.y;
		}
		return *this;
	}

	// Plus-equals operator
	vector_2d& vector_2d::operator += (const vector_2d& arg) {
		x += arg.x;
		y += arg.y;
		return *this;
	}

	// Minus-equals operator
	vector_2d& vector_2d::operator -= (const vector_2d& arg) {
		x -= arg.x;
		y -= arg.y;
		return *this;
	}

	// Times-equals operator
	vector_2d& vector_2d::operator *= (double fctr) {
		x *= fctr;
		y *= fctr;
		return *this;
	}

	// Divided-equals operator
	vector_2d& vector_2d::operator /= (double fctr) {
		if (fctr == 0) {
			std::cerr << "Division error: cannot divide by zero";
			exit(EXIT_FAILURE);
		}
		x /= fctr;
		y /= fctr;
		return *this;
	}

	// Output stream operator
	std::ostream& operator << (std::ostream& os, const vector_2d& arg) {
		os << "(" << arg.xcor() << ", " << arg.ycor() << ")";
		return os;
	}

	// Addition operator
	vector_2d operator + (const vector_2d& one, const vector_2d& two) {
		vector_2d sum;
		sum.set_x(one.xcor() + two.xcor());
		sum.set_y(one.ycor() + two.ycor());
		return sum;
	}

	// Subtraction operator
	vector_2d operator - (const vector_2d& one, const vector_2d& two) {
		vector_2d diff;
		diff.set_x(one.xcor() - two.xcor());
		diff.set_y(one.ycor() - two.ycor());
		return diff;
	}

	// Returns the product of vector and number
	vector_2d operator * (double fctr, const vector_2d& arg) {
		vector_2d resized_vector;
		resized_vector.set_x(fctr * arg.xcor());
		resized_vector.set_y(fctr * arg.ycor());
		return resized_vector;
	}
	vector_2d operator * (const vector_2d& arg, double fctr) { return fctr * arg; }

	// Returns the inner product of two vectors
	double operator * (const vector_2d& one, const vector_2d& two) {
		return one.xcor() * two.xcor() + one.ycor() * two.ycor();
	}
}

#endif // VECTOR_2D_H