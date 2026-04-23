#define BLOCK_SIZE 16

__global__ void matmul1 (float* a, float* b, int n, float* c)
{
    int row = blockDim.y * blockIdx.y + threadIdx.y;
    int col = blockDim.x * blockIdx.x + threadIdx.x;
    float sum = 0.0f;

    if (row < n && col < n) {
        for (int k = 0; k < n; k++)
            sum += a[row * n + k] * b[k * n + col];
        c[row * n + col] = sum;
    }
}

#define kernel matmul1
#include "mainGPU.h"