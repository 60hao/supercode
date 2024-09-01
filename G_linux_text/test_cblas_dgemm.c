#include <cblas.h>
#include <stdio.h>

#define M 3
#define N 3
#define K 2

int main()
{
  int i = 0;
  double A[M * K] = {1.0, 2.0, 1.0, -3.0, 4.0, -1.0};
  double B[K * N] = {1.0, 2.0, 1.0, -3.0, 4.0, -1.0};
  double C[M * N] = {.5, .5, .5, .5, .5, .5, .5, .5, .5};
  //double D[M * N] = {.5, .5, .5, .5, .5, .5, .5, .5, .5};
  double alpha = 1.0;
  double beta = 2.0;

  int lda = M;
  int ldb = K;
  int ldc = M;
  cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
  //（行优先，不转置A，不转置B，AC的行数，BC的列数，A列B行，AB乘积的比例因子，，A矩阵第一维大小，，B第一维，矩阵C的比例因子，C地址，C第一维）
  //C=α∗AB+β∗C
  //cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, M, N, K, alpha, A, ldb, B, lda, beta, D, ldc);

  printf("列主序的输出\n");
  for (i = 0; i < 9; i++)
    {printf("%lf ", C[i]);}
  printf("\n");
  /*printf("行主序的输出\n");
  for (i = 0; i < 9; i++)
    {printf("%lf ", D[i]);}
  printf("\n");*/
  return 0;
}