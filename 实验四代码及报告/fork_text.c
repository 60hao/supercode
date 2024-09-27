#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define M 513
#define N 513
#define K 513


void dgemm(int m, int n, int k, int beta,
          double A[][k], double B[][n], double C[][n]){
    for(int i=0; i< m;i ++){    //C[i] 
        for(int j=0; j< n; j++){  //C[i][j]
            C[i][j] = beta*C[i][j];
            for(int p=0; p< k; p++){  
                C[i][j] += A[i][p]*B[p][j]; 
             }
        }
    }
}

void printf_matrix(int row, int col, double matrix[row][col] ){
  for(int i=0; i<row; i++){
    for(int j=0; j<col;j++){
        printf("%lf ", matrix[i][j]);
    }
    printf("\n");
  }
  printf("\n\n");
}

int
main(int argc, char *argv[])
{
    double A[M][K];   
    for(int i=0;i<M;i++){
        for(int j=0;j<M;j++){
            A[i][j]=i-j;
        }
    }   
    double B[K][N];
    for(int i=0;i<M;i++){
        for(int j=0;j<M;j++){
            B[i][j]=i+j;
        }
    }   
    double C[M][N] ;
    for(int i=0;i<M;i++){
        for(int j=0;j<M;j++){
            C[i][j]=1;
        }
    }    

    printf("hello world (pid:%d)\n", (int) getpid());
    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        printf("hello, I am child (pid:%d)\n", (int) getpid());
        for(int i=0;i<6;i++){
            dgemm(M,N,K,2, A,B,C);
        }
       
    } else {
        // parent goes down this path (original process)
        int wc = wait(NULL);
        printf("hello, I am parent of %d (wc:%d) (pid:%d)\n",
               rc, wc, (int) getpid());
        for(int i=0;i<6;i++){
            dgemm(M,N,K,2, A,B,C);
        }
    }
    return 0;
}
//dgemm(M,N,K,2, A,B,C);