# Лабораторная работа №1: Последовательное перемножение матриц

**Студент:** Симонов Илья Андреевич  
**Группа:** 6311  
**Зачетная книжка:** 2023-01764  

## 1. Цель работы
Изучить методы обработки файлов на языке C++, реализовать базовый последовательный алгоритм перемножения квадратных матриц и провести исследование зависимости времени выполнения программы от размерности задачи. Данная версия программы является эталонной для последующих параллельных реализаций.

## 2. Теоретические сведения
Произведение матриц $C = A \times B$ вычисляется по формуле:
$$C_{ij} = \sum_{k=1}^{n} A_{ik} \cdot B_{kj}$$

Где:
- $A, B$ — исходные матрицы.
- $C$ — результирующая матрица.

Алгоритмическая сложность данного метода составляет $O(N^3)$, так как для вычисления каждого из $N^2$ элементов результирующей матрицы требуется произвести $N$ операций умножения и сложения. Общее количество операций оценивается как $2N^3$.

## 3. Описание алгоритма
Программа реализует классический алгоритм умножения:
1. Чтение размерности матрицы $N$ из входного файла.
2. Динамическое выделение памяти под матрицы $A, B$ и $C$.
3. Заполнение матриц данными из файлов `matrix_1.txt` и `matrix_2.txt`.
4. Перемножение матриц с помощью трех вложенных циклов.
5. Замер времени выполнения вычислительного блока с использованием библиотеки `<chrono>`.
6. Сохранение результата в файл `result.txt`.

## 4. Исходный код программы
Программа скомпилирована с использованием флага оптимизации `-O3`.

```cpp
#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>

using namespace std;

vector<vector<double>> readMatrix(string filename, int& n) {
    ifstream file(filename);
    if (!file.is_open()) return {};
    file >> n;
    vector<vector<double>> matrix(n, vector<double>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            file >> matrix[i][j];
    file.close();
    return matrix;
}

void writeMatrix(string filename, const vector<vector<double>>& matrix) {
    ofstream file(filename);
    int n = matrix.size();
    file << n << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            file << matrix[i][j] << " ";
        file << endl;
    }
    file.close();
}

int main() {
    int n1, n2;
    vector<vector<double>> A = readMatrix("A.txt", n1);
    vector<vector<double>> B = readMatrix("B.txt", n2);

    if (A.empty() || B.empty() || n1 != n2) {
        cout << "Error: Check matrix files or sizes!" << endl;
        return 1;
    }

    int n = n1;
    vector<vector<double>> C(n, vector<double>(n, 0));

    auto start = chrono::high_resolution_clock::now();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    writeMatrix("result.txt", C);

    cout << "Matrix size: " << n << "x" << n << endl;
    cout << "Execution time: " << duration.count() << " seconds" << endl;

    return 0;
}
```

## 5. Автоматическая верификация

Для проверки корректности используется скрипт на языке Python с библиотекой NumPy.

```python
import numpy as np

def load_matrix(filename):
    with open(filename, 'r') as f:
        n = int(f.readline())
        return np.loadtxt(f).reshape(n, n)

A = load_matrix("A.txt")
B = load_matrix("B.txt")
C_cpp = load_matrix("result.txt")
C_py = np.dot(A, B)

if np.allclose(C_cpp, C_py, atol=1e-7):
    print("VERIFICATION SUCCESSFUL: Results match!")
else:
    print("VERIFICATION FAILED: Results do not match!")
```

Результат верификации:
VERIFICATION SUCCESSFUL: Results match!


## 6. Результаты экспериментов
Тестирование проводилось на процессоре Intel i7. Для компиляции использовался флаг оптимизации `-O3`.

| Размер матрицы N | Кол-во операций (2*N^3) | Время выполнения (сек) |
| :--- | :---: | :---: |
| 200 | 1.6 * 10^7 | 0.004958 |
| 400 | 1.28 * 10^8 | 0.042165 |
| 500 | 2.5 * 10^8 | 0.085004 |
| 800 | 1.02 * 10^9 | 0.433051 |
| 1200 | 3.45 * 10^9 | 1.638210 |
| 1600 | 8.19 * 10^9 | 5.243810 |

## 7. Анализ результатов и вывод
В ходе выполнения лабораторной работы был реализован и исследован последовательный алгоритм умножения квадратных матриц. 

Основные выводы:
1. **Верификация:** Результаты работы программы на C++ полностью совпадают с результатами библиотеки NumPy (Python), что подтверждает корректность реализованного алгоритма.
2. **Сложность:** Экспериментально подтверждена теоретическая сложность $O(N^3)$. При увеличении размерности $N$ в 2 раза (например, с 800 до 1600), время выполнения увеличилось примерно в 12 раз. Это значение даже выше теоретических 8 ($2^3$), что объясняется дополнительными задержками при обращении к оперативной памяти, когда данные перестают помещаться в кэш-память процессора.
3. **Оптимизация:** Использование флага `-O3` при компиляции крайне важно для высокопроизводительных вычислений, так как позволяет компилятору эффективно оптимизировать вложенные циклы.