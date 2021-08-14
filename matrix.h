#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <iomanip>
#include <exception>
#include <type_traits>
#include <cmath>


namespace algebra
{
	typedef long long dimension_t;

	template <class T> class matrix
	{
	protected:	// Class members
		T* m_matrix;
		dimension_t m_rows;
		dimension_t m_collumns;

	protected:
		T* getRow(dimension_t i) const { return m_matrix + (i * m_collumns); }

	public:	// Constructors -- Destructor
		matrix() = delete;
		matrix(dimension_t, dimension_t);
		matrix(const matrix<T>&);
		~matrix();

	public:	// Class Methods
		void init(T);
		void set(T set_num) { init(set_num); }
		bool canBeMultipliedWith(const matrix<T>&) const;

		dimension_t numOfRows() const { return m_rows; }
		dimension_t numOfColls() const { return m_collumns; }

	public:	// Operators
		matrix<T>& operator = (const matrix<T>&);
		virtual matrix<T>& operator *= (T);
		virtual matrix<T>& operator /= (T);
		T* operator [] (dimension_t i) const { return getRow(i); }
	};

	// Operators
	template <typename T> matrix<T> operator + (const matrix<T>&, const matrix<T>&);
	template <typename T> matrix<T> operator - (const matrix<T>&, const matrix<T>&);
	template <typename T> matrix<T> operator * (const matrix<T>&, const matrix<T>&);
	template <typename T> matrix<T> operator * (T, const matrix<T>&);
	template <typename T> matrix<T> operator * (const matrix<T>&, T);
	template <typename T> bool operator != (const matrix<T>&, const matrix<T>&);
	template <typename T> bool operator == (const matrix<T>&, const matrix<T>&);
	template <typename T> std::ostream& operator << (std::ostream&, const matrix<T>&);
	template <typename T> std::istream& operator >> (std::istream&, const matrix<T>&);


	// --- BLUEPRINTS ---

	// Constructs a matrix with RxC dimension
	template <typename T>
	matrix<T>::matrix(dimension_t R, dimension_t C)
	{
		// Accepts or discards the given data type
		static_assert(std::is_trivially_copyable<T>::value, "Matrix's scalars must be trivially copyable");

		if (R < 1 || C < 1) {
			std::cerr << "Matrix construction error: non-positive number of rows or collumns" << std::endl;
			exit(EXIT_FAILURE);
		}
		m_matrix = new T[(std::size_t)(R * C)];
		m_rows = R;
		m_collumns = C;
	}

	template <typename T>
	matrix<T>::matrix(const matrix<T>& prototype)
	{
		m_rows = prototype.m_rows;
		m_collumns = prototype.m_collumns;
		m_matrix = new T[(unsigned int)(m_rows * m_collumns)];

		dimension_t total = m_rows * m_collumns;
		for (dimension_t i = 0; i < total; ++i) {
			m_matrix[i] = prototype.m_matrix[i];
		}
	}

	template <typename T>
	matrix<T>::~matrix() {
		delete[] this->m_matrix;
	}
	
	// --- METHODS ---

	// Initialises matrice's cells with the given arguement
	template <typename T>
	void matrix<T>::init(T init_arg)
	{
		dimension_t total = m_rows * m_collumns;
		for (dimension_t i = 0; i < total; ++i) {
			m_matrix[i] = init_arg;
		}
	}

	// Returns whether the operation (*this) x arg can be performed
	template <typename T>
	bool matrix<T>::canBeMultipliedWith(const matrix<T>& arg) const {
		return this->numOfColls() == arg.numOfRows();
	}


	// --- OPERATORS ---

	// Assignment operator
	template <typename T>
	matrix<T>& matrix<T>::operator = (const matrix<T>& arg)
	{
		if (this != &arg) 
		{
			m_rows = arg.numOfRows();
			m_collumns = arg.numOfColls();

			delete[] m_matrix;
			m_matrix = new T[(std::size_t)(m_rows * m_collumns)];

			dimension_t total = m_rows * m_collumns;

			for (dimension_t i = 0; i < total; ++i) {
				m_matrix[i] = arg.m_matrix[i];
			}
		}
		return *this;
	}

	// Times-equals operator with number
	template <typename T>
	matrix<T>& matrix<T>::operator *= (T factor)
	{
		dimension_t total = m_rows * m_collumns;
		for (dimension_t i = 0; i < total; ++i) {
			m_matrix[i] *= factor;
		}
		return *this;
	}

	// Division-equals operator with number
	template <typename T>
	matrix<T>& matrix<T>::operator /= (T factor)
	{
		dimension_t total = m_rows * m_collumns;
		for (dimension_t i = 0; i < total; ++i) {
			m_matrix[i] /= factor;
		}
		return *this;
	}

	// Addition operator -- two matrices
	template <typename T>
	matrix<T> operator + (const matrix<T>& one, const matrix<T>& two)
	{
		if (one.numOfRows() != two.numOfRows() ||
			one.numOfColls() != two.numOfColls())
		{
			std::cerr << "Error: cannot add matrices with different dimensions" << std::endl;
			return matrix<T>(1, 1);
		}
		matrix<T> sum(one.numOfRows(), one.numOfColls());

		for (dimension_t i = 0; i < sum.numOfRows(); ++i) {
			for (dimension_t j = 0; j < sum.numOfColls(); ++j) {
				sum[i][j] = one[i][j] + two[i][j];
			}
		}
		return sum;
	}


	// Subtraction operator -- two matrices
	template <typename T>
	matrix<T> operator - (const matrix<T>& one, const matrix<T>& two)
	{
		if (one.numOfRows() != two.numOfRows() ||
			one.numOfColls() != two.numOfColls())
		{
			std::cerr << "Error: cannot subtract matrices with different dimensions" << std::endl;
			return matrix<T>(1, 1);
		}
		matrix<T> diff(one.numOfRows(), one.numOfColls());

		for (dimension_t i = 0; i < diff.numOfRows(); ++i) {
			for (dimension_t j = 0; j < diff.numOfColls(); ++j) {
				diff[i][j] = one[i][j] - two[i][j];
			}
		}
		return diff;
	}

	// Multiplication operator -- two matrices
	template <typename T>
	matrix<T> operator * (const matrix<T>& one, const matrix<T>& two)
	{
		if (one.numOfColls() != two.numOfRows()) {
			std::cerr << "Error: cannot multiply matrices\n"
				<< "Collumns and rows of instances do not match"
				<< std::endl;
			return matrix<T>(1, 1);
		}
		matrix<T> prod(one.numOfRows(), two.numOfColls());

		prod.init((T)0);

		for (dimension_t i = 0; i < one.numOfRows(); i++) {
			for (dimension_t j = 0; j < two.numOfColls(); j++) {
				for (dimension_t k = 0; k < one.numOfColls(); k++) {
					prod[i][j] += one[i][k] * two[k][j];
				}
			}
		}
		return prod;
	}


	// Multiplication operator with number
	template <typename T>
	matrix<T> operator * (T factor, const matrix<T>& arg)
	{
		matrix<T> prod(arg);
		prod *= factor;
		return prod;
	}
	template <typename T>
	matrix<T> operator * (const matrix<T>& arg, T factor) {
		return factor * arg;
	}

	// Equal-to operator
	template <typename T>
	bool operator == (const matrix<T>& one, const matrix<T>& two) 
	{
		if (one.numOfRows()  != two.numOfRows() ||
			two.numOfColls() != two.numOfColls()) {
			return false;
		}
		bool result = true;

		for (dimension_t i = 0; i < one.numOfRows() && result; ++i) {
			for (dimension_t j = 0; j < one.numOfColls() && result; ++j) {
				if (one[i][j] != two[i][j]) {
					result = false;
				}
			}
		}
		return result;
	}

	// Not-equal-to operator
	template <typename T>
	bool operator != (const matrix<T>& one, const matrix<T>& two) {
		return !(one == two);
	}

	// Output stream operator
	template <typename T>
	std::ostream& operator << (std::ostream& os, const matrix<T>& arg) 
	{	
		for (dimension_t i = 0; i < arg.numOfRows(); ++i) {
			os << "|";
			for (dimension_t j = 0; j < arg.numOfColls(); ++j) {
				os << std::setw(4) << std::setfill(' ') << arg[i][j] << " ";
			}
			os << "|" << std::endl;
		}
		return os;
	}

	// Input stream operator
	template <typename T>
	std::istream& operator >> (std::istream& is, const matrix<T>& arg)
	{
		for (dimension_t i = 0; i < arg.numOfRows(); ++i) {
			for (dimension_t j = 0; j < arg.numOfColls(); ++j) {
				is >> arg[i][j];
			}
		}
		return is;
	}



	// -------------------------------
	// ----- SQUARE MATRIX CLASS -----
	// -------------------------------

	// A subclass for square matrices, it has extra special properties such as
	// exponentiation and determinant calculation 
	template <class T> class sqr_matrix : public matrix<T>
	{
	protected:
		void decomposeLU(sqr_matrix<double>&, sqr_matrix<double>&) const;

	public:	// Constructors
		sqr_matrix() = delete;
		sqr_matrix(dimension_t N);
		sqr_matrix(const sqr_matrix<T>&);

	public:	// Methods
		dimension_t dimension() const { return this->m_rows; }
		matrix<T> pow(unsigned long long) const;
		double determinant() const;

	public:	// Operators
		sqr_matrix<T>& operator = (const sqr_matrix<T>&);
		sqr_matrix<T>& operator *= (T) override;
		sqr_matrix<T>& operator /= (T) override;
	};


	// --- BLUEPRINTS ---

	// Explicit Constructor
	template <typename T>
	sqr_matrix<T>::sqr_matrix(dimension_t N) : matrix<T>(N, N) {}

	// Copy Constructor
	template <typename T>
	sqr_matrix<T>::sqr_matrix(const sqr_matrix<T>& prototype) : matrix<T>(prototype) {}


	// --- METHODS ---

	// Returns the matrix to the power of the argument,
	// the following algorithm strives for efficient exponentiation
	// with O(log2(exp)) time complexity, where exp is the exponent
	template <typename T>
	matrix<T> sqr_matrix<T>::pow(unsigned long long exp) const
	{
		if (exp <= 1) {
			if (exp <= 0)
				std::cerr << "Error: Exponent of matrix must be greater than zero!" << std::endl;
			return (*this);
		}
		if (exp == 2) {
			return (*this) * (*this);
		}
		if (exp == 3) {
			return (*this) * (*this) * (*this);
		}

		std::size_t len = (int)log2(exp) + 2;
		auto** p = new matrix<T>* [len];

		for (std::size_t k = 0; k < len; ++k) {
			p[k] = new matrix<T>(this->dimension(), this->dimension());
		}

		unsigned int i = 0;
		unsigned int current_exp = 1;
		unsigned int prev_exp;

		*(p[0]) = *this;

		while (current_exp <= exp)
		{
			++i;
			current_exp = current_exp << 1;
			*(p[i]) = *(p[i - 1]) * *(p[i - 1]);
		}

		current_exp = current_exp >> 1;
		prev_exp = current_exp >> 1;

		*(p[i]) = *(p[i - 1]);

		while (current_exp < exp) {
			if (prev_exp + current_exp <= exp) {
				*(p[i]) = *(p[i]) * *(p[(int)log2(prev_exp)]);
				current_exp += prev_exp;
			}
			prev_exp = prev_exp >> 1;
		}

		matrix<T> result = *(p[i]);

		for (std::size_t k = 0; k < len; ++k) {
			delete p[k];
		}
		delete[] p;

		return result;
	}

	// Function implementing PA = LU decomposition for the given Matrix
	template <typename T>
	void sqr_matrix<T>::decomposeLU(sqr_matrix<double>& L, sqr_matrix<double>& U) const
	{
		for (dimension_t j = 0; j < this->dimension(); j++) {
			for (dimension_t i = 0; i < this->dimension(); i++) {
				if (i <= j) {
					U[i][j] = (double)(*this)[i][j];
					for (dimension_t k = 0; k < i; k++) {
						U[i][j] -= L[i][k] * U[k][j];
					}
					L[i][j] = (i == j ? 1 : 0);
				}
				else {
					L[i][j] = (double)(*this)[i][j];
					for (dimension_t k = 0; k <= j - 1; k++) {
						L[i][j] -= L[i][k] * U[k][j];
					}
					if (U[j][j] == 0) {
						std::cout << j << std::endl;
						std::cout << "Problem" << std::endl;
					}
					// TODO: Fix U[j][j] == 0 problem
					// If the program gets executed, you'll see "Problem" being
					// printed at the command line, which means the following:
					if (U[j][j] == 0)
					    std::cout << "Problem" << std::endl;
					// This leads to inf values in the L and U matrices as well
					// as wrong calculation of the determinant.
					L[i][j] /= U[j][j];
					U[i][j] = 0;

					// For more insight run the program.
				}
			}
		}
	}

	// Returns the determinant of a square matrix
	template <typename T>
	double sqr_matrix<T>::determinant() const
	{
		sqr_matrix<double> L(this->dimension());
		sqr_matrix<double> U(this->dimension());

		L.init(0);
		U.init(0);

		decomposeLU(L, U);

		std::cout << "L = \n" << L << std::endl;
		std::cout << "U = \n" << U << std::endl;

		double detU = 1;

		for (dimension_t i = 0; i < this->dimension(); ++i) {
			detU *= U[i][i];
		}
		return detU;
	}

	// --- OPERATORS ---

	// Assignment operator
	template <typename T>
	sqr_matrix<T>& sqr_matrix<T>::operator = (const sqr_matrix<T>& arg)
	{
		if (this != &arg) 
		{
			this->m_rows = arg.dimension();
			this->m_collumns = arg.dimension();

			delete[] this->m_matrix;
			this->m_matrix = new T[(std::size_t)(this->m_rows * this->m_collumns)];

			dimension_t total = this->m_rows * this->m_collumns;

			for (dimension_t i = 0; i < total; ++i) {
				this->m_matrix[i] = arg.m_matrix[i];
			}
		}
		return *this;
	}

	// Times-equals operator with number
	template <typename T>
	sqr_matrix<T>& sqr_matrix<T>::operator *= (T factor)
	{
		dimension_t total = this->m_rows * this->m_collumns;
		for (dimension_t i = 0; i < total; ++i) {
			this->m_matrix[i] *= factor;
		}
		return *this;
	}

	// Division-equals operator with number
	template <typename T>
	sqr_matrix<T>& sqr_matrix<T>::operator /= (T factor)
	{
		dimension_t total = this->m_rows * this->m_collumns;
		for (dimension_t i = 0; i < total; ++i) {
			this->m_matrix[i] /= factor;
		}
		return *this;
	}

}

#endif // MATRIX_H