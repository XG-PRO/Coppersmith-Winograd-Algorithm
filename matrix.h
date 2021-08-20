#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <iomanip>
#include <exception>
#include <type_traits>
#include <cmath>


/*                           MATRIX CLASS
 *
 *  An  implementation for  linear  algebra's  matrices, an important
 *  data structure for the current project.
 *  The Coppersmith-Winograd  algorithm  will be  used for optimizing
 *  the multiplication of matrices and the calculation of determinant
 */

namespace algebra {
    typedef long long dimension_t;  // data type for the rows and columns of

    template<class T>
    class matrix
    {
        /*  Each square matrix itself is a pseudo-2D array instance.
         *  The scalars are stored in a one-dimensional C-style array.
         *
         *  This offers 2 main advantages compared to a double pointer array:
         *      - slightly higher speed
         *      - optimal locality
         */
    protected:    // Class members
        T *m_matrix;            // The one-dimensional array for storing the scalars of the matrix
        dimension_t m_rows;     // Number of rows
        dimension_t m_columns;  // Number of columns

    protected:
        // Will be used for the overloading of the "[]" operator
        T *getRow(dimension_t i) const { return m_matrix + (i * m_columns); }

    public: // Constructors -- Destructor
        matrix() = delete;
        matrix(dimension_t, dimension_t);
        matrix(const matrix<T> &);
        ~matrix();

    public: // Class Methods
        void init(T);
        void set(T set_num) { init(set_num); }
        bool canBeMultipliedWith(const matrix<T> &) const;
        dimension_t numOfRows() const { return m_rows; }
        dimension_t numOfCols() const { return m_columns; }

    public: // Operators
        matrix<T> &operator = (const matrix<T> &);
        virtual matrix<T> &operator *= (T);
        virtual matrix<T> &operator /= (T);

        // This  specific definition of the  overloaded "[]" operator
        // makes the expression M[i][j] possible, where M is a matrix
        T *operator [] (dimension_t i) const { return getRow(i); }
    };

    // Operators
    template<typename T> matrix<T> operator + (const matrix<T> &, const matrix<T> &);
    template<typename T> matrix<T> operator - (const matrix<T> &, const matrix<T> &);
    template<typename T> matrix<T> operator * (const matrix<T> &, const matrix<T> &);
    template<typename T> matrix<T> operator * (T, const matrix<T> &);
    template<typename T> matrix<T> operator * (const matrix<T> &, T);
    template<typename T> bool operator != (const matrix<T> &, const matrix<T> &);
    template<typename T> bool operator == (const matrix<T> &, const matrix<T> &);
    template<typename T> std::ostream &operator << (std::ostream &, const matrix<T> &);
    template<typename T> std::istream &operator >> (std::istream &, const matrix<T> &);


    // --- BLUEPRINTS ---

    // Constructs a matrix with RxC dimension
    template<typename T>
    matrix<T>::matrix(dimension_t R, dimension_t C) {
        /*  Accepts or discards the given data type, only trivially copyable
         *  data types are accepted as scalars.
         *
         *  algebra::complex is an accepted data types, thus matrices with
         *  complex scalars can be created
         *
         *  head to complex.h for more info on the library's complex numbers.
         */
        static_assert(std::is_trivially_copyable<T>::value, "Matrix's scalars must be trivially copyable");

        if (R < 1 || C < 1) {
            std::cerr << "Matrix construction error: non-positive number of rows or collumns" << std::endl;
            exit(EXIT_FAILURE);
        }
        m_matrix = new T[(std::size_t) (R * C)];
        m_rows = R;
        m_columns = C;
    }

    template<typename T>
    matrix<T>::matrix(const matrix<T> &prototype) {
        m_rows = prototype.m_rows;
        m_columns = prototype.m_columns;
        m_matrix = new T[(unsigned int) (m_rows * m_columns)];

        dimension_t total = m_rows * m_columns;
        for (dimension_t i = 0; i < total; ++i) {
            m_matrix[i] = prototype.m_matrix[i];
        }
    }

    template<typename T>
    matrix<T>::~matrix() {
        delete[] this->m_matrix;
    }

    // --- METHODS ---

    // Initialises matrix's cells with the given argument
    template<typename T>
    void matrix<T>::init(T init_arg) {
        dimension_t total = m_rows * m_columns;
        for (dimension_t i = 0; i < total; ++i) {
            m_matrix[i] = init_arg;
        }
    }

    // Returns whether the operation (*this) x arg can be performed
    template<typename T>
    bool matrix<T>::canBeMultipliedWith(const matrix<T> &arg) const {
        return this->numOfCols() == arg.numOfRows();
    }


    // --- OPERATORS ---

    // Assignment operator
    template<typename T>
    matrix<T> &matrix<T>::operator = (const matrix<T> &arg) {
        if (this != &arg) {
            m_rows = arg.numOfRows();
            m_columns = arg.numOfCols();

            delete[] m_matrix;
            m_matrix = new T[(std::size_t) (m_rows * m_columns)];

            dimension_t total = m_rows * m_columns;

            for (dimension_t i = 0; i < total; ++i) {
                m_matrix[i] = arg.m_matrix[i];
            }
        }
        return *this;
    }

    // Times-equals operator with number
    template<typename T>
    matrix<T> &matrix<T>::operator *= (T factor) {
        dimension_t total = m_rows * m_columns;
        for (dimension_t i = 0; i < total; ++i) {
            m_matrix[i] *= factor;
        }
        return *this;
    }

    // Division-equals operator with number
    template<typename T>
    matrix<T> &matrix<T>::operator /= (T factor) {
        dimension_t total = m_rows * m_columns;
        for (dimension_t i = 0; i < total; ++i) {
            m_matrix[i] /= factor;
        }
        return *this;
    }

    // Addition operator -- two matrices
    template<typename T>
    matrix<T> operator + (const matrix<T> &one, const matrix<T> &two) {
        if (one.numOfRows() != two.numOfRows() ||
                one.numOfCols() != two.numOfCols()) {
            std::cerr << "Error: cannot add matrices with different dimensions" << std::endl;
            return matrix<T>(1, 1);
        }
        matrix<T> sum(one.numOfRows(), one.numOfCols());

        for (dimension_t i = 0; i < sum.numOfRows(); ++i) {
            for (dimension_t j = 0; j < sum.numOfCols(); ++j) {
                sum[i][j] = one[i][j] + two[i][j];
            }
        }
        return sum;
    }


    // Subtraction operator -- two matrices
    template<typename T>
    matrix<T> operator - (const matrix<T> &one, const matrix<T> &two) {
        if (one.numOfRows() != two.numOfRows() ||
                one.numOfCols() != two.numOfCols()) {
            std::cerr << "Error: cannot subtract matrices with different dimensions" << std::endl;
            return matrix<T>(1, 1);
        }
        matrix<T> diff(one.numOfRows(), one.numOfCols());

        for (dimension_t i = 0; i < diff.numOfRows(); ++i) {
            for (dimension_t j = 0; j < diff.numOfCols(); ++j) {
                diff[i][j] = one[i][j] - two[i][j];
            }
        }
        return diff;
    }

    // Multiplication operator -- two matrices
    template<typename T>
    matrix<T> operator * (const matrix<T> &one, const matrix<T> &two) {
        if (one.numOfCols() != two.numOfRows()) {
            std::cerr << "Error: cannot multiply matrices\n"
                      << "Collumns and rows of instances do not match"
                      << std::endl;
            return matrix<T>(1, 1);
        }
        matrix<T> prod(one.numOfRows(), two.numOfCols());

        prod.init((T) 0);

        for (dimension_t i = 0; i < one.numOfRows(); i++) {
            for (dimension_t j = 0; j < two.numOfCols(); j++) {
                for (dimension_t k = 0; k < one.numOfCols(); k++) {
                    prod[i][j] += one[i][k] * two[k][j];
                }
            }
        }
        return prod;
    }


    // Multiplication operator with number
    template<typename T>
    matrix<T> operator * (T factor, const matrix<T> &arg) {
        matrix<T> prod(arg);
        prod *= factor;
        return prod;
    }

    template<typename T>
    matrix<T> operator * (const matrix<T> &arg, T factor) {
        return factor * arg;
    }

    // Equal-to operator
    template<typename T>
    bool operator == (const matrix<T> &one, const matrix<T> &two) {
        if (one.numOfRows() != two.numOfRows() ||
                two.numOfCols() != two.numOfCols()) {
            return false;
        }
        bool result = true;

        for (dimension_t i = 0; i < one.numOfRows() && result; ++i) {
            for (dimension_t j = 0; j < one.numOfCols() && result; ++j) {
                if (one[i][j] != two[i][j]) {
                    result = false;
                }
            }
        }
        return result;
    }

    // Not-equal-to operator
    template<typename T>
    bool operator != (const matrix<T> &one, const matrix<T> &two) {
        return !(one == two);
    }

    // Output stream operator
    template<typename T>
    std::ostream &operator << (std::ostream &os, const matrix<T> &arg) {
        for (dimension_t i = 0; i < arg.numOfRows(); ++i) {
            os << "|";
            for (dimension_t j = 0; j < arg.numOfCols(); ++j) {
                os << std::setw(4) << std::setfill(' ') << arg[i][j] << " ";
            }
            os << "|" << std::endl;
        }
        return os;
    }

    // Input stream operator
    template<typename T>
    std::istream &operator >> (std::istream &is, const matrix<T> &arg) {
        for (dimension_t i = 0; i < arg.numOfRows(); ++i) {
            for (dimension_t j = 0; j < arg.numOfCols(); ++j) {
                is >> arg[i][j];
            }
        }
        return is;
    }



    // -------------------------------
    // ----- SQUARE MATRIX CLASS -----
    // -------------------------------

    // A subclass for square matrices, it has extra, special properties such as
    // exponentiation and determinant calculation
    template<class T>
    class sqr_matrix : public matrix<T>
    {
    protected:
        void decomposeLU(sqr_matrix<double> &, sqr_matrix<double> &) const;

    public: // Constructors
        sqr_matrix() = delete;
        sqr_matrix(dimension_t N);
        sqr_matrix(const sqr_matrix<T> &);

    public: // Methods
        dimension_t dimension() const { return this->m_rows; }
        matrix<T> pow(long long) const;
        double determinant() const;

    public: // Operators
        sqr_matrix<T> &operator = (const sqr_matrix<T> &);
        sqr_matrix<T> &operator *= (T) override;
        sqr_matrix<T> &operator /= (T) override;
    };

    // Operators
    template<typename T> sqr_matrix<T> operator + (const sqr_matrix<T> &, const sqr_matrix<T> &);
    template<typename T> sqr_matrix<T> operator - (const sqr_matrix<T> &, const sqr_matrix<T> &);
    template<typename T> sqr_matrix<T> operator * (const sqr_matrix<T> &, const sqr_matrix<T> &);
    template<typename T> sqr_matrix<T> operator * (T, const sqr_matrix<T> &);
    template<typename T> sqr_matrix<T> operator * (const sqr_matrix<T> &, T);


    // --- BLUEPRINTS ---

    // Explicit Constructor
    template<typename T>
    sqr_matrix<T>::sqr_matrix(dimension_t N) : matrix<T>(N, N) {}

    // Copy Constructor
    template<typename T>
    sqr_matrix<T>::sqr_matrix(const sqr_matrix<T> &prototype) : matrix<T>(prototype) {}


    // --- METHODS ---

    /*  Returns the matrix to the power of the argument,
     *  the following algorithm strives for efficient exponentiation
     *  with O(log2(exp)) time complexity, where exp is the exponent
     */
    template<typename T>
    matrix<T> sqr_matrix<T>::pow(long long exp) const {
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

        std::size_t len = (int) log2(exp) + 2;
        auto **p = new matrix<T> *[len];

        for (std::size_t k = 0; k < len; ++k) {
            p[k] = new matrix<T>(this->dimension(), this->dimension());
        }

        unsigned int i = 0;
        unsigned int current_exp = 1;
        unsigned int prev_exp;

        *(p[0]) = *this;

        while (current_exp <= exp) {
            ++i;
            current_exp = current_exp << 1;
            *(p[i]) = *(p[i - 1]) * *(p[i - 1]);
        }

        current_exp = current_exp >> 1;
        prev_exp = current_exp >> 1;

        *(p[i]) = *(p[i - 1]);

        while (current_exp < exp) {
            if (prev_exp + current_exp <= exp) {
                *(p[i]) = *(p[i]) * *(p[(int) log2(prev_exp)]);
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
    template<typename T>
    void sqr_matrix<T>::decomposeLU(sqr_matrix<double> &L, sqr_matrix<double> &U) const {
        for (dimension_t j = 0; j < this->dimension(); j++) {
            for (dimension_t i = 0; i < this->dimension(); i++) {
                if (i <= j) {
                    U[i][j] = (double) (*this)[i][j];
                    for (dimension_t k = 0; k < i; k++) {
                        U[i][j] -= L[i][k] * U[k][j];
                    }
                    if (i == j)
                        L[i][j] = 1;
                    else
                        L[i][j] = 0;
                } else {
                    L[i][j] = (double) (*this)[i][j];
                    for (dimension_t k = 0; k <= j - 1; k++) {
                        L[i][j] -= L[i][k] * U[k][j];
                    }
                    /*  The following code causes a division-by-zero issue, the results are:
                     *      - Some scalars are assigned NaN values
                     *      - Wrong calculation of determinant
                     *  Run the code to see for yourself
                     */
                    L[i][j] /= U[j][j];
                    U[i][j] = 0;
                }
            }
        }
    }

    // Returns the determinant of a square matrix
    template<typename T>
    double sqr_matrix<T>::determinant() const {
        sqr_matrix<double> L(this->dimension());
        sqr_matrix<double> U(this->dimension());

        this->decomposeLU(L, U);

        double detU = 1;

        for (dimension_t i = 0; i < this->dimension(); ++i) {
            detU *= U[i][i];
        }
        return detU;
    }

    // --- OPERATORS ---

    // Assignment operator
    template<typename T>
    sqr_matrix<T> &sqr_matrix<T>::operator=(const sqr_matrix<T> &arg) {
        if (this != &arg) {
            this->m_rows = arg.dimension();
            this->m_columns = arg.dimension();

            delete[] this->m_matrix;
            this->m_matrix = new T[(std::size_t) (this->m_rows * this->m_columns)];

            dimension_t total = this->m_rows * this->m_columns;

            for (dimension_t i = 0; i < total; ++i) {
                this->m_matrix[i] = arg.m_matrix[i];
            }
        }
        return *this;
    }

    // Times-equals operator with number
    template<typename T>
    sqr_matrix<T> &sqr_matrix<T>::operator*=(T factor) {
        dimension_t total = this->m_rows * this->m_columns;
        for (dimension_t i = 0; i < total; ++i) {
            this->m_matrix[i] *= factor;
        }
        return *this;
    }

    // Division-equals operator with number
    template<typename T>
    sqr_matrix<T> &sqr_matrix<T>::operator/=(T factor) {
        dimension_t total = this->m_rows * this->m_columns;
        for (dimension_t i = 0; i < total; ++i) {
            this->m_matrix[i] /= factor;
        }
        return *this;
    }

    // Addition operator -- two square matrices
    template<typename T>
    sqr_matrix<T> operator + (const sqr_matrix<T> &one, const sqr_matrix<T> &two) {
        if (one.dimension() != two.dimension()) {
            std::cerr << "Error: cannot add matrices with different dimensions" << std::endl;
            return sqr_matrix<T>(1);
        }
        sqr_matrix<T> sum(one.dimension());

        for (dimension_t i = 0; i < sum.dimension(); ++i) {
            for (dimension_t j = 0; j < sum.dimension(); ++j) {
                sum[i][j] = one[i][j] + two[i][j];
            }
        }
        return sum;
    }

    // Subtraction operator -- two square matrices
    template<typename T>
    sqr_matrix<T> operator - (const sqr_matrix<T> &one, const sqr_matrix<T> &two) {
        if (one.dimension() != two.dimension()) {
            std::cerr << "Error: cannot subtract matrices with different dimensions" << std::endl;
            return sqr_matrix<T>(1);
        }
        sqr_matrix<T> diff(one.dimension());

        for (dimension_t i = 0; i < diff.dimension(); ++i) {
            for (dimension_t j = 0; j < diff.dimension(); ++j) {
                diff[i][j] = one[i][j] - two[i][j];
            }
        }
        return diff;
    }

    // Multiplication operator -- two square matrices
    template<typename T>
    sqr_matrix<T> operator * (const sqr_matrix<T> &one, const sqr_matrix<T> &two) {
        if (one.dimension() != two.dimension()) {
            std::cerr << "Error: cannot multiply matrices\n"
                      << "Collumns and rows of instances do not match"
                      << std::endl;
            return sqr_matrix<T>(1);
        }
        sqr_matrix<T> prod(one.dimension());

        prod.init((T) 0);

        for (dimension_t i = 0; i < one.dimension(); i++) {
            for (dimension_t j = 0; j < two.dimension(); j++) {
                for (dimension_t k = 0; k < one.dimension(); k++) {
                    prod[i][j] += one[i][k] * two[k][j];
                }
            }
        }
        return prod;
    }

    // Multiplication operator with number
    template<typename T>
    sqr_matrix<T> operator * (T factor, const sqr_matrix<T> &arg) {
        sqr_matrix<T> prod(arg);
        prod *= factor;
        return prod;
    }

    template<typename T>
    sqr_matrix<T> operator * (const sqr_matrix<T> &arg, T factor) {
        return factor * arg;
    }

}

#endif // MATRIX_H