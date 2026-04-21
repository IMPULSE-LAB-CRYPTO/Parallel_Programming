import random
import sys

def generate_matrix(n, filename):
    with open(filename, 'w') as f:
        f.write(f"{n}\n") # Первая строка - размерность
        for _ in range(n):
            # Генерируем строку случайных чисел через пробел
            row = [round(random.uniform(0, 100), 2) for _ in range(n)]
            f.write(" ".join(map(str, row)) + "\n")

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Использование: python gen_matrices.py <N>")
        sys.exit(1)
    
    n = int(sys.argv[1])
    generate_matrix(n, "A.txt")
    generate_matrix(n, "B.txt")
    print(f"Матрицы A.txt и B.txt размером {n}x{n} успешно созданы.")
