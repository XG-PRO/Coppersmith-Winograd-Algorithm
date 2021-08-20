#ifndef VECTOR_3D_H
#define VECTOR_3D_H

#include "vector_2d.h"

namespace algebra 
{
	class vector_3d : public vector_2d
	{
	protected:
		double z;

	public:
		vector_3d();
		vector_3d(double, double, double);
		vector_3d(const vector_2d&);
		vector_3d(const vector_3d&);

	public:
		void set_z(double z) { this->z = z; }
		double zcor() const { return z; }
		double magnitude() const override;

	public:
		vector_3d& operator = (const vector_3d&);
		vector_3d& operator += (const vector_3d&);
		vector_3d& operator -= (const vector_3d&);
		vector_3d& operator *= (double);
		vector_3d& operator /= (double);
	};

	std::ostream& operator << (std::ostream&, const vector_3d&);
	vector_3d operator + (const vector_3d&, const vector_3d&);
	vector_3d operator - (const vector_3d&, const vector_3d&);
	vector_3d operator * (double, const vector_3d&);
	vector_3d operator * (const vector_3d&, double);
	double operator * (const vector_3d&, const vector_3d&);


	// --- BLUEPRINTS ---

	// Empty Constructor
	vector_3d::vector_3d() {
		x = 0;
		y = 0;
		z = 0;
	}

	// Explicit Constructor
	vector_3d::vector_3d(double x, double y, double z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	// Copy Constructor [2D VECTOR]
	vector_3d::vector_3d(const vector_2d& prototype) {
		x = prototype.xcor();
		y = prototype.ycor();
		z = 0;
	}

	// Copy Constructor [3D VECTOR]
	vector_3d::vector_3d(const vector_3d& prototype) {
		x = prototype.x;
		y = prototype.y;
		z = prototype.z;
	}


	// --- METHODS ---

	// Returns the magnitude of vector
	double vector_3d::magnitude() const {
		return sqrt(x * x + y * y + z * z);
	}


	// --- OPERATORS ---

	// Assignment operator
	vector_3d& vector_3d::operator = (const vector_3d& arg)
	{
		if (this != &arg) {
			x = arg.x;
			y = arg.y;
			z = arg.z;
		}
		return *this;
	}

	// Plus-equals operator
	vector_3d& vector_3d::operator += (const vector_3d& arg) {
		x += arg.x;
		y += arg.y;
		z += arg.z;
		return *this;
	}

	// Minus-equals operator
	vector_3d& vector_3d::operator -= (const vector_3d& arg) {
		x -= arg.x;
		y -= arg.y;
		z -= arg.z;
		return *this;
	}

	// Times-equals operator
	vector_3d& vector_3d::operator *= (double fctr) {
		x *= fctr;
		y *= fctr;
		z *= fctr;
		return *this;
	}

	// Divided-equals operator
	vector_3d& vector_3d::operator /= (double fctr) {
		if (fctr == 0) {
			std::cerr << "Division error: cannot divide by zero";
			exit(EXIT_FAILURE);
		}
		x /= fctr;
		y /= fctr;
		z /= fctr;
		return *this;
	}

	// Output stream operator
	std::ostream& operator << (std::ostream& os, const vector_3d& arg) {
		os << "(" << arg.xcor() << ", " << arg.ycor() << ", " << arg.zcor() << ")";
		return os;
	}

	// Addition operator
	vector_3d operator + (const vector_3d& one, const vector_3d& two) {
		vector_3d sum;
		sum.set_x(one.xcor() + two.xcor());
		sum.set_y(one.ycor() + two.ycor());
		sum.set_z(one.zcor() + two.zcor());
		return sum;
	}

	// Subtraction operator
	vector_3d operator - (const vector_3d& one, const vector_3d& two) {
		vector_3d diff;
		diff.set_x(one.xcor() - two.ycor());
		diff.set_y(one.xcor() - two.ycor());
		diff.set_z(one.zcor() - two.zcor());
		return diff;
	}

	// Returns the product of vector and number
	vector_3d operator * (double fctr, const vector_3d& arg) {
		vector_3d resized_vector;
		resized_vector.set_x(fctr * arg.xcor());
		resized_vector.set_y(fctr * arg.ycor());
		resized_vector.set_z(fctr * arg.zcor());
		return resized_vector;
	}
	vector_3d operator * (const vector_3d& arg, double fctr) { return fctr * arg; }

	// Returns the inner product of two vectors
	double operator * (const vector_3d& one, const vector_3d& two) {
		return (one.xcor() * two.xcor() + 
				one.ycor() * two.ycor() +
				one.zcor() * two.zcor());
	}
}

#undef PI

#endif // VECTOR_3D_H