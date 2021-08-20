#include <iostream>
#include <fstream>
#include "algebra.h"

/*              TODO: PA = LU decomposition problem
 *  During  the  decomposition  of  the  5x5 matrix found in matrices.txt
 *  the two triangular matrices, U and L, have shown to have an inf value
 *  as one of their elements.
 *
 *  Head to matrix.h file -- line 405 for more details.
 *  DO NOT EDIT THE MAIN FUNCTION BEFORE DOING SO
 */


/*                  UPDATE -- 20/08/2021:
 *  New  implementation  for  row  echelon form is on the way,
 *  this will  make the  determinant  calculation more  robust
 *  for scalars in all number sets, like negatives and complex
 *  numbers.
 */

int main()
{
    // Constructs two square matrices with 5x5 and 3x3 dimensions, respectively.
	algebra::sqr_matrix<int> A(5);
	algebra::sqr_matrix<int> B(3);

	// File input stream for reading the two aforementioned matrices
	std::ifstream ifs;

	ifs.open("matrices.txt", std::ios::in);

	if (ifs.is_open()) 
	{
		std::cout << "First Matrix: " << std::endl;
		ifs >> A;
		std::cout << A << std::endl;

		std::cout << "Second Matrix:" << std::endl;
		ifs >> B;
		std::cout << B << std::endl;

		std::cout << "Det(A): " << std::endl;
		std::cout << A.determinant() << std::endl;

        ifs.close();
	}
	else
	{
		std::cerr << "File Error!" << std::endl;
		return 1;
	}


	return 0;
}