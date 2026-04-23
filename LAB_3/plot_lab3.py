import matplotlib.pyplot as plt

# Данные из замеров
processes = [1, 2, 4, 6, 12]
n_600 = [0.1138, 0.0549, 0.0330, 0.0316, 0.0364]
n_1200 = [1.2686, 0.8684, 0.6592, 0.6201, 0.4987]
n_1800 = [5.5955, 3.6910, 2.2249, 1.8271, 1.5703]

def plot_time():
    plt.figure(figsize=(10, 6))
    plt.plot(processes, n_600, marker='o', label='N=600')
    plt.plot(processes, n_1200, marker='o', label='N=1200')
    plt.plot(processes, n_1800, marker='o', label='N=1800')
    plt.xlabel('Processes (P)')
    plt.ylabel('Time (sec)')
    plt.title('Execution Time vs Processes (MPI)')
    plt.legend()
    plt.grid(True)
    plt.savefig('time_vs_processes.png')

def plot_speedup():
    plt.figure(figsize=(10, 6))
    # Ускорение S = T1 / Tp
    s_600 = [n_600[0]/t for t in n_600]
    s_1200 = [n_1200[0]/t for t in n_1200]
    s_1800 = [n_1800[0]/t for t in n_1800]
    
    plt.plot(processes, s_600, marker='s', label='N=600')
    plt.plot(processes, s_1200, marker='s', label='N=1200')
    plt.plot(processes, s_1800, marker='s', label='N=1800')
    plt.plot(processes, processes, '--', color='gray', label='Ideal')
    plt.xlabel('Processes (P)')
    plt.ylabel('Speedup')
    plt.title('Speedup vs Processes (MPI)')
    plt.legend()
    plt.grid(True)
    plt.savefig('speedup_vs_processes.png')

plot_time()
plot_speedup()
print("Графики сохранены.")