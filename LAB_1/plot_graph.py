import matplotlib.pyplot as plt

# Данные из экспериментов
n_values = [200, 400, 500, 800, 1200, 1600]
times = [0.004958, 0.042165, 0.085004, 0.433051, 1.63821, 5.24381]

plt.figure(figsize=(10, 6))
plt.plot(n_values, times, marker='o', linestyle='-', color='b', label='Actual Time')

# Настройка оформления
plt.title('Dependency of Execution Time on Matrix Size (Sequential)', fontsize=14)
plt.xlabel('Matrix Size (N x N)', fontsize=12)
plt.ylabel('Execution Time (seconds)', fontsize=12)
plt.grid(True, linestyle='--', alpha=0.7)
plt.legend()

# Сохранение в файл
plt.savefig('graph.png')
print("График сохранен как graph.png")
# plt.show()