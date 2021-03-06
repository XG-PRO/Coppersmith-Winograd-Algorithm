#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

double DetTr(int ,double (*)[]);
void LU_Decomposition(int , int (*)[],double (*)[], double (*)[]);
void *createArray2D(int , int );
void *randomArrLower(int ,int );        //Obsolete function, used at early stages for experimentation.
void *randomArr(int , int );
void printArray(int ,int ,int (*)[]);


//Main Program
int main() {
    int N;
    char mode;
    struct timeval  tv1, tv2;

    srand(time(NULL));

    printf("Give size of A:NxN -> ");				                //Declaration of square matrix's size
    scanf("%d",&N);
    while((mode=getchar())!='\n' && mode!=EOF);

    if (N<=1) {
        printf("Wrong Input\n");
        exit(1);
    }

    int (*A)[N];

    printf("\nSelect array creation method\n");
    printf("R for random, M for manual, other for exit: ");	        //Array creation method (manual/random numbers)
    scanf("%c",&mode);

    if (mode == 'M' || mode == 'm')
        A = createArray2D(N, N);
    else if (mode == 'R' || mode == 'r')
        A = randomArr(N, N);
    else
        exit(2);

    gettimeofday(&tv1, NULL);

    double (*L)[N],(*U)[N];
        L = malloc(N*N * sizeof(double));
        U = malloc(N*N * sizeof(double));
        LU_Decomposition(N,A,L,U);                  //Formation of lower and upper triangular matrices

        /* We will use the property det(LxU) = det(L)*det(U) to calculate the determinant of the initial matrix.
         * It is proven that the determinant of a triangular matrix (either upper or lower) is equal to
         * the product of its diagonal elements, or more mathematically:
         *
         * det(M) = m11*m22*m33*...*mNN
         * where M:NxN a triangular matrix
         *
         * In this case: det(A) = det(L) * det(U) = l11*l22*...*lNN * u11*u22*...*uNN
         */

        /* According to PA = LU decomposition, the diagonal elements of the lower triangular matrix will be 1.
         * This way the lower triangular matrix is not necessary because:
         * det(A) = det(L)*det(U) = 1*det(U) = det(U)
         */

        free(L);

        //Printing matrix A:NxN.
        //Conditions used for aesthetic purposes; Matrix shall not exceed screen size.
        //if (N<40) {
        //    printf("\nMatrix(A):\n");
        //    printArray(N, N, A);
        //}

        //printf("\nMatrix(U):\n");
        //printArrayFloat(N,N,U);

        double detU;
        detU = DetTr(N,U);

    gettimeofday(&tv2, NULL);

    printf("\n|A| = %.0lf\n",detU);				//Determinant of matrix
    printf ("\nTotal time = %f seconds\n", (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 + (double) (tv2.tv_sec - tv1.tv_sec));

    return 0;
}