#include <stdio.h>
#include <stdlib.h>

//Function for calculating the determinant of a square triangular matrix
double DetTr(int N,float Tr[][N]) {
    double prod = 1;
    for (int i=0;i<N;i++)
        prod *= Tr[i][i];
    return prod;
}

//Function implementing PA = LU decomposition for the given Matrix
void LU_Decomposition(int n, int a[][n],float L[][n], float U[][n])
{
    int i,j,k;

    for(j=0; j<n; j++) {
        for(i=0; i<n; i++) {
            if(i<=j) {
                U[i][j]=(float)a[i][j];
                for(k=0; k<i; k++)
                    U[i][j]-=L[i][k]*U[k][j];
                if(i==j)
                    L[i][j]=1;
                else
                    L[i][j]=0;
            }
            else {
                L[i][j]=(float)a[i][j];
                for(k=0; k<=j-1; k++)
                    L[i][j]-=L[i][k]*U[k][j];
                L[i][j]/=U[j][j];
                U[i][j]=0;
            }
        }
    }
}


//Auxiliary function for creating a 2D array manually.
void *createArray2D(int M, int N) {
    int (*A)[N],i,j;

    A = malloc(sizeof(int[M][N]));
    for (i=0;i<M;i++)
        for (j=0;j<N;j++) {
            printf("A[%d][%d] = ",i,j);
            scanf("%d",&A[i][j]);
        }
    return A;
}

//Auxiliary function for assigning random values in a 2D array, forming a lower triangular matrix. Range: [1,10]
void *randomArrLower(int M,int N) {
    int (*P)[N],i,j;

    P = calloc(M*N,sizeof(int));
    for (i=0;i<M;i++)
        for (j=0;j<i+1;j++)
            P[i][j] = (rand()%10)+1;
    return P;
}

//Auxiliary function for assigning random values in a 2D array. Range: [1,10]
void *randomArr(int M, int N) {
    int (*P)[N],i,j;

    P = malloc(sizeof(int[M][N]));
    for (i=0;i<M;i++)
        for (j=0;j<N;j++)
            P[i][j] = (rand()%10)+1;
    return P;
}

//Auxiliary function for printing a 2D array (type int).
void printArray(int M,int N,int A[][N]) {
    int i,j;
    for (i=0;i<M;i++) {
        printf("| ");
        for (j=0;j<N;j++)
            printf("%2d ",A[i][j]);
        printf("|\n");
    }
}