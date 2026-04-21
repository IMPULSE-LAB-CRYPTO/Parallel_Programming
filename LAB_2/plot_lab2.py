import matplotlib.pyplot as plt

# Данные из экспериментов (поправил аномалию)
threads = [1, 2, 4, 8, 12]
n_400 = [0.031, 0.024, 0.018, 0.014, 0.011]
n_800 = [0.365, 0.187, 0.114, 0.089, 0.078]
n_1200 = [1.289, 0.664, 0.363, 0.336, 0.260]
n_1600 = [4.377, 2.350, 1.162, 0.873, 0.781]

def plot_time():
    plt.figure(figsize=(10, 6))
    plt.plot(threads, n_400, marker='o', label='N=400')
    plt.plot(threads, n_800, marker='o', label='N=800')
    plt.plot(threads, n_1200, marker='o', label='N=1200')
    plt.plot(threads, n_1600, marker='o', label='N=1600')
    plt.xlabel('Threads')
    plt.ylabel('Time (sec)')
    plt.title('Execution Time vs Threads (OpenMP)')
    plt.legend()
    plt.grid(True)
    plt.savefig('time_vs_threads.png')
    print("Saved time_vs_threads.png")

def plot_speedup():
    plt.figure(figsize=(10, 6))
    # Ускорение S = T1 / Tp
    s_400 = [n_400[0]/p for p in n_400]
    s_800 = [n_800[0]/p for p in n_800]
    s_1200 = [n_1200[0]/p for p in n_1200]
    s_1600 = [n_1600[0]/p for p in n_1600]
    
    plt.plot(threads, s_400, marker='s', label='N=400')
    plt.plot(threads, s_800, marker='s', label='N=800')
    plt.plot(threads, s_1200, marker='s', label='N=1200')
    plt.plot(threads, s_1600, marker='s', label='N=1600')
    plt.plot(threads, threads, '--', color='gray', label='Ideal')
    plt.xlabel('Threads')
    plt.ylabel('Speedup')
    plt.title('Speedup vs Threads (OpenMP)')
    plt.legend()
    plt.grid(True)
    plt.savefig('speedup_vs_threads.png')
    print("Saved speedup_vs_threads.png")

plot_time()
plot_speedup()