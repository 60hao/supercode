#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 
#include <unistd.h>
#include <assert.h>

typedef struct {
    int num, now, d; // 总块数，当前块，块大小
    int m, n, k;     // 矩阵维度
    double *A, *B, *C; // 矩阵指针
} node;

// 矩阵乘法计算
void MMult(int m, int n, int k, int r1, int r2, double *A, double *B, double *C) {
    for (int i = r1 - 1; i < r2; i++) {
        for (int j = 0; j < n; j++) { 
            double temp = 0.0;
            for (int p = 0; p < k; p++) {
                temp += A[i * k + p] * B[p * n + j];
            }
            C[i * m + j] += temp;
        }
    }
}

// 线程执行函数
void *mythread(void *arg) {
    node *info = (node *)arg;

    int current_block = __sync_fetch_and_add(&(info->now), 1); // 获取当前块并递增
    int d = info->d;
    int m = info->m, n = info->n, k = info->k;

    int r1 = (current_block - 1) * d + 1;
    int r2 = (current_block == info->num) ? m : current_block * d; // 处理最后一个块的大小

    MMult(m, n, k, r1, r2, info->A, info->B, info->C); // 执行矩阵乘法

    return NULL;
}

// 多线程矩阵乘法函数
void MY_MMult(int m, int n, int k, double *A, int lda,
              double *B, int ldb, double *C, int ldc) {
    node info;
    info.num = 8; // 总线程数
    info.now = 1; // 初始化当前块为 1
    info.d = m / info.num; // 每个线程处理的行数
    info.m = m;
    info.n = n;
    info.k = k;
    info.A = A;
    info.B = B;
    info.C = C;

    pthread_t threads[info.num]; // 定义线程数组
    int rc;

    for (int i = 0; i < info.num; i++) {
        rc = pthread_create(&threads[i], NULL, mythread, &info);
        assert(rc == 0); // 检查线程创建是否成功
    }

    for (int i = 0; i < info.num; i++) {
        rc = pthread_join(threads[i], NULL);
        assert(rc == 0); // 确保线程完成
    }
}
