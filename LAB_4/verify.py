import numpy as np

def load_matrix(filename):
    with open(filename, 'r') as f:
        n = int(f.readline())
        return np.loadtxt(f).reshape(n, n)

try:
    A = load_matrix("A.txt")
    B = load_matrix("B.txt")
    res_cpp = load_matrix("result.txt")

    # Вычисляем эталон
    res_py = np.dot(A, B)

    # Сравниваем с погрешностью (из-за особенностей float/double)
    if np.allclose(res_cpp, res_py, atol=1e-5):
        print("ВЕРИФИКАЦИЯ ПРОЙДЕНА: Результаты совпадают.")
    else:
        print("ОШИБКА: Результаты не совпадают!")
except Exception as e:
    print(f"Ошибка при верификации: {e}")
