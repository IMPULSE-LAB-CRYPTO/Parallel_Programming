#include <cublas_v2.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>

void printmat(float* m, int n) {
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++)
            printf("%f ", m[i + j * n]);
        printf("\n");
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <n>\n", argv[0]);
        printf("Where n must be a multiplier of %d\n", BLOCK_SIZE);
        return 0;
    }

    int n = atoi(argv[1]);
    if (n % BLOCK_SIZE != 0) {
        printf("Invalid n: %d. n must be a multiplier of %d\n", n, BLOCK_SIZE);
        return 1;
    }

    printf("Matrix size: %d x %d | Block size: %d\n", n, n, BLOCK_SIZE);

    int n2 = n * n;
    int n2b = n2 * sizeof(float);

    float* a = (float*)malloc(n2b);
    float* b = (float*)malloc(n2b);
    float* c1 = (float*)malloc(n2b);
    float* c2 = (float*)malloc(n2b);

    for (int i = 0; i < n2; i++) {
        a[i] = (float)rand() / RAND_MAX;
        b[i] = (float)rand() / RAND_MAX;
    }

    float *adev, *bdev, *cdev;
    cudaMalloc((void**)&adev, n2b);
    cudaMalloc((void**)&bdev, n2b);
    cudaMalloc((void**)&cdev, n2b);

    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    cudaMemcpy(adev, a, n2b, cudaMemcpyHostToDevice);
    cudaMemcpy(bdev, b, n2b, cudaMemcpyHostToDevice);

    // Запуск ядра (kernel)
    dim3 threads(BLOCK_SIZE, BLOCK_SIZE);
    dim3 blocks(n / threads.x, n / threads.y);

    cudaEventRecord(start, 0);
    kernel<<<blocks, threads>>>(adev, bdev, n, cdev);
    
    cudaError_t err = cudaGetLastError();
    if (err != cudaSuccess) 
        printf("CUDA Error: %s\n", cudaGetErrorString(err));

    cudaEventRecord(stop, 0);
    cudaEventSynchronize(stop);

    float gpuTime = 0.0f;
    cudaEventElapsedTime(&gpuTime, start, stop);
    printf("Time spent executing kernel: %.2f ms\n", gpuTime);

    cudaMemcpy(c1, cdev, n2b, cudaMemcpyDeviceToHost);

    // Сравнение с CUBLAS (для проверки)
    cublasHandle_t handle;
    cublasCreate(&handle);
    float alpha = 1.0f, beta = 0.0f;
    
    cudaEventRecord(start, 0);
    cublasSgemm(handle, CUBLAS_OP_N, CUBLAS_OP_N, n, n, n, &alpha, adev, n, bdev, n, &beta, cdev, n);
    cudaEventRecord(stop, 0);
    cudaEventSynchronize(stop);

    float cublasTime = 0.0f;
    cudaEventElapsedTime(&cublasTime, start, stop);
    printf("Time spent executing CUBLAS: %.2f ms\n", cublasTime);

    // Проверка точности
    double maxdiff = 0;
    cudaMemcpy(c2, cdev, n2b, cudaMemcpyDeviceToHost);
    for (int i = 0; i < n2; i++) {
        float diff = abs(c1[i] - c2[i]);
        if (diff > maxdiff) maxdiff = diff;
    }
    printf("Max difference with CUBLAS: %e\n", maxdiff);

    cudaFree(adev); cudaFree(bdev); cudaFree(cdev);
    free(a); free(b); free(c1); free(c2);
    return 0;
}