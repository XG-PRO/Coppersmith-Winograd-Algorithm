#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

//Recursive function for calculating the determinant of an NxN square matrix
long int Det(int N,int A[][N]) 	//Input: square matrix and its dimension
{
  //"sum" variable will be returned as the determinant of the matrix
  long int sum=0;
  int i,j,k,k2,sign;
  
  //Terminal condition: minor has reached 2x2 dimensions
  if (N==2)			
    return A[0][0]*A[1][1] - A[1][0]*A[0][1];
  
  //Submatrix P formed by removing the ith row and the jth column of matrix B
  int P[N-1][N-1];

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
          P[j-1][k2] = A[j][k];
          k2++;
        }
    //Laplace expansion
    if (A[0][i]!=0)
        sum += sign*A[0][i]*Det(N-1,P);
  }
  
  return sum;
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


//Auxiliary function for assigning random values in a 2Darray, forming a lower triangular matrix. Range: [1,10]
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

//Auxiliary function for printing a 2D array.
void printArray(int *A,int M,int N) {
  int i,j;
  for (i=0;i<M;i++) {
    printf("| ");
    for (j=0;j<N;j++)
        printf("%2d ",A[i*N+j]);
    printf("|\n");
  }
}

int main() {
  int N;
  int i,j;
  char mode;

  srand(time(NULL));

  printf("Give size of A:NxN -> ");				//Decleration of square matrice's size
  scanf("%d",&N);
  while((mode=getchar())!='\n' && mode!=EOF);

  if (N<=1) {
    printf("Wrong Input\n");
    exit(1);
  }

  int (*A)[N];
  A = malloc(sizeof(int[N][N]));

  printf("\nSelect array creation method\n");
  printf("R for random, M for manual, other for exit: ");	//Array creation method (manual/random numbers)
  scanf("%c",&mode);

  if (mode == 'M' || mode == 'm')
    A = createArray2D(N, N);
  else if (mode =='R' || mode == 'r')
    A = randomArrLower(N, N);
  else
    exit(2);

  printf("\nMatrix(A):\n");
  printArray((int *)A,N,N);

  printf("\n|A| = %ld\n",Det(N,A));				//Determinant of matrix

  return 0;
}
