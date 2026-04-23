#define BLOCK_SIZE 16

__global__ void matmul2(float* a, float* b, int n, float* c)
{
    __shared__ float as[BLOCK_SIZE][BLOCK_SIZE];
    __shared__ float bs[BLOCK_SIZE][BLOCK_SIZE];

    int bx = blockIdx.x; int by = blockIdx.y;
    int tx = threadIdx.x; int ty = threadIdx.y;

    int row = by * BLOCK_SIZE + ty;
    int col = bx * BLOCK_SIZE + tx;
    float sum = 0.0f;

    for (int m = 0; m < n / BLOCK_SIZE; ++m) {
        as[ty][tx] = a[row * n + (m * BLOCK_SIZE + tx)];
        bs[ty][tx] = b[(m * BLOCK_SIZE + ty) * n + col];
        __syncthreads();

        for (int k = 0; k < BLOCK_SIZE; ++k)
            sum += as[ty][k] * bs[k][tx];
        __syncthreads();
    }
    c[row * n + col] = sum;
}

#define kernel matmul2
#include "mainGPU.h"