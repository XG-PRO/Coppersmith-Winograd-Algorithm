#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Recursive function for calculating the determinant of an NxN square matrix
//Lower triangular matrix used for optimal speed.
double Det(int N,float M[][N]) 	//Input: square matrix and its dimension
{
  //"sum" variable will be returned as the determinant of the matrix
  double sum=0;
  int i,j,k,k2,sign;
  
  //Terminal condition: minor has reached 2x2 dimensions
  if (N==2)			
    return M[0][0]*M[1][1] - M[1][0]*M[0][1];
  
  //Submatrix P formed by removing the 0th row and the ith column of matrix B
  float P[N-1][N-1];

  for (i=0;i<N;i++) {
    //sign of terms according to Laplace expansion method for calculating determinant
    if (i%2==0)
      sign = 1;
    else
      sign = -1;
    //formation of the submatrix P
    for (j=1;j<N;j++)
      for (k=k2=0;k<N;k++)
        if (k!=i) {
          P[j-1][k2] = M[j][k];
          k2++;
        }
    //Laplace expansion
    if (M[0][i]!=0)                                  //Lower triangular matrix used for optimal speed.
        sum += sign*M[0][i]*Det(N-1,P);
  }
  
  return sum;
}

//Function implementing PA = LU decomposition for the given Matrix
void LU_Decomposition(int n, int a[][n],float L[][n], float U[][n])
{
    int i,j,k;

    for(j=0; j<n; j++) {
        for(i=0; i<n; i++) {
            if(i<=j) {
                U[i][j]=a[i][j];
                for(k=0; k<i; k++)
                    U[i][j]-=L[i][k]*U[k][j];
                if(i==j)
                    L[i][j]=1;
                else
                    L[i][j]=0;
            }
            else {
                L[i][j]=a[i][j];
                for(k=0; k<=j-1; k++)
                    L[i][j]-=L[i][k]*U[k][j];
                L[i][j]/=U[j][j];
                U[i][j]=0;
            }
        }
    }
}

//Function for creating the inverse of square matrix U (value assignment U = U^T)
//After using this function we can proceed to take advantage of the property: det(U^T) = det(U)
//This way function Det will return the value of det(U) at optimal speed.
void upperToLower(int N, float U[][N]) {
    int i,j;
    float temp;

    for (i=0;i<N;i++) {
        for (j=i+1;j<N;j++) {
            temp = U[i][j];
            U[i][j] = U[j][i];
            U[j][i] = temp;
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

//Auxiliary function for printing a 2D array (type float).
void printArrayFloat(int M,int N,float A[][N]) {
    int i,j;
    for (i=0;i<M;i++) {
        printf("| ");
        for (j=0;j<N;j++)
            printf("%7.2f ",A[i][j]);
        printf("|\n");
    }
}

int main() {
  int N;
  char mode;

  srand(time(NULL));

  printf("Give size of A:NxN -> ");				//Declaration of square matrix's size
  scanf("%d",&N);
  while((mode=getchar())!='\n' && mode!=EOF);

  if (N<=1) {
    printf("Wrong Input\n");
    exit(1);
  }

  int (*A)[N];

  printf("\nSelect array creation method\n");
  printf("R for random, M for manual, other for exit: ");	//Array creation method (manual/random numbers)
  scanf("%c",&mode);

  if (mode == 'M' || mode == 'm')
    A = createArray2D(N, N);
  else if (mode == 'R' || mode == 'r')
    A = randomArr(N, N);
  else
    exit(2);

  float (*L)[N],(*U)[N];
  L = malloc(N*N * sizeof(float));
  U = malloc(N*N * sizeof(float));
  LU_Decomposition(N,A,L,U);                    //Formation of lower and upper triangular matrices


  //Printing matrices A:NxN, L:NxN and U:NxN
  //Conditions used for aesthetic purposes; Matrices shall not exceed screen size.
  if (N<40) {
      printf("\nMatrix(A):\n");
      printArray(N, N, A);
      if (N < 15) {
          printf("\nMatrix(L):\n");
          printArrayFloat(N, N, L);
          printf("\nMatrix(U):\n");
          printArrayFloat(N, N, U);
      }
  }
  upperToLower(N,U);

  //printf("\nMatrix(U):\n");
  //printArrayFloat(N,N,U);

  double detA, detL, detU;

  detL = Det(N,L);
  detU = Det(N,U);
  detA = detL * detU;                           //Property: det(AxB) = det(A) * det(B)

  printf("\n|A| = %.0lf\n",detA);				//Determinant of matrix

  return 0;
}
