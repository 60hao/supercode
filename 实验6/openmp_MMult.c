#include <unistd.h>
#include <stdio.h>
#include <omp.h>

void MY_MMult(int m, int n, int k, double *A, int lda,
               double *B, int ldb,
               double *C, int ldc)
{
    /*
    int i = 0;
    int j = 0;
    */
    // printf("%d\n",omp_get_thread_num());
    #pragma omp parallel for
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            // C[i*m + j] = beta*C[i*m + j];
            for (int  p = 0; p < k; p++)
            {
                C[i*m + j] += A[i*k + p]*B[p*n + j];
            }
        }
    }
}