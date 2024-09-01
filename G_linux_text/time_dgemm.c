#include "stdio.h"
#include "stdlib.h"
#include "sys/time.h"
#include "time.h"
#include <cblas.h>

// 编译 gcc -o time_dgemm time_dgemm.c –lopenblas
// 运行 ./time_dgemm 1024


void naive_dgemm(double A[],double B[],double C[],int M,int N,int K){
  for(int i=0; i<M; i++){
      for(int j=0; j<N; j++){
          C[i*N+j] = 0.0;
          for (int k = 0; k < K; k++) {  
                C[i*N+j] += A[i*K+k] * B[k*N+j];  
            }
      }
  }
  return ;
}

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    printf("Input Error\n");
    return 1;
  }

  printf("test!\n");
  int i, m, n, k;
  m = n = k = atoi(argv[1]);//atoi函数把字符串转换为整数型

  int sizeofa = m * k;
  int sizeofb = k * n;
  int sizeofc = m * n;
  int lda = m;
  int ldb = k;
  int ldc = m;

  double alpha = 1.2;
  double beta = 0.001;

  struct timeval start, finish;
  //struct timeval结构体在time.h中定义,微妙精度

  double duration;
  struct timeval start2,finish2;
  double duration2;


  double *A = (double *)malloc(sizeof(double) * sizeofa);
  double *B = (double *)malloc(sizeof(double) * sizeofb);
  double *C = (double *)malloc(sizeof(double) * sizeofc);
  double *D = (double *)malloc(sizeof(double) * sizeofc);
  srand((unsigned)time(NULL));

  for (i = 0; i < sizeofa; i++)
  {
    A[i] = i % 3 + 1; // (rand() % 100) / 100.0;
  }

  for (i = 0; i < sizeofb; i++)
  {
    B[i] = i % 3 + 1; //(rand()%100)/10.0;
  }

  for (i = 0; i < sizeofc; i++)
  {
    C[i] = 0.1;
    D[i] = 0.1;
  }

  printf("m=%d,n=%d,k=%d,alpha=%lf,beta=%lf,sizeofc=%d\n", m, n, k, alpha, beta, sizeofc);
  gettimeofday(&start, NULL);
  cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc);
  gettimeofday(&finish, NULL);

  // 转成成秒数
  duration = (double)(finish.tv_sec - start.tv_sec) + (double)(finish.tv_usec - start.tv_usec) / 1.0e6;
  double gflops = 4.0 * m * n * k;
  gflops = gflops / duration * 1.0e-9;
  //每秒10亿次的浮点运算数

  printf("m=%d,n=%d,k=%d,alpha=%lf,beta=%lf,sizeofc=%d\n", m, n, k, alpha, beta, sizeofc);
  gettimeofday(&start2, NULL);
  naive_dgemm(D, A, B, m, n, k);
  gettimeofday(&finish2, NULL);

  duration2 = (double)(finish2.tv_sec - start2.tv_sec) + (double)(finish2.tv_usec - start2.tv_usec) / 1.0e6;
  double gflops2 = 4.0 * m * n * k;
  gflops2 = gflops / duration * 1.0e-9;

  int flag=0;
  for (int i=0; i<m*n; i++){
    if(C[i]-D[i]>1e-1||D[i]-C[i]>1e-1){
      printf("get a wrong answer\n");
      flag =1;
      break;
    }
  }
  if (flag == 0){
    printf("the two answers are same\n");
  }

  FILE *fp;//fp是结构体指针变量
  fp = fopen("timeDGEMM.txt", "a"); // 追加写
  fprintf(fp,"time%d下的cblas运算\t",m);
  fprintf(fp, "%dx%dx%d\t%lf s\t%lf GFLOPS\n", m, n, k, duration, gflops);
  fprintf(fp,"time%d下的naive运算\t",m);
  fprintf(fp, "%dx%dx%d\t%lf s\t%lf GFLOPS\n", m, n, k, duration2, gflops2);
  fclose(fp);

  free(A);
  free(B);
  free(C);
  return 0;
}
