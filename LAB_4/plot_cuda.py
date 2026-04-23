import matplotlib.pyplot as plt

# Замеры (в мс)
n_values = [512, 1024, 2048]
naive_times = [0.50, 3.30, 26.67]
opt_times = [0.44, 2.54, 20.95]
cublas_times = [0.34, 0.84, 3.02]

plt.figure(figsize=(10, 6))
plt.plot(n_values, naive_times, marker='o', label='GPU Naive')
plt.plot(n_values, opt_times, marker='s', label='GPU Shared Memory')
plt.plot(n_values, cublas_times, marker='^', label='NVIDIA cuBLAS')

plt.xlabel('Matrix Size (N)')
plt.ylabel('Execution Time (ms)')
plt.title('CUDA Performance Comparison (RTX)')
plt.legend()
plt.grid(True)
plt.savefig('cuda_comparison.png')
print("График сохранен как cuda_comparison.png")