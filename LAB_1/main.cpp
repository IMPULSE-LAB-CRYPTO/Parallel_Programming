#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>

using namespace std;

// Функция для выделения памяти и чтения из файла
bool readMatrix(const string& filename, int& n, vector<double>& matrix) {
    ifstream in(filename);
    if (!in.is_open()) return false;
    in >> n;
    matrix.resize(n * n);
    for (int i = 0; i < n * n; ++i) {
        if (!(in >> matrix[i])) break;
    }
    return true;
}

int main(int argc, char* argv[]) {
    int n;
    vector<double> A, B;

    // 1. Считываем данные
    if (!readMatrix("A.txt", n, A) || !readMatrix("B.txt", n, B)) {
        cerr << "Ошибка открытия файлов матриц!" << endl;
        return 1;
    }

    vector<double> C(n * n, 0.0);

    // 2. Вычисления (замеряем только этот блок)
    auto start = chrono::high_resolution_clock::now();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            double sum = 0;
            for (int k = 0; k < n; ++k) {
                sum += A[i * n + k] * B[k * n + j];
            }
            C[i * n + j] = sum;
        }
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    // 3. Вывод результатов
    cout << "Размерность матрицы: " << n << endl;
    cout << "Время выполнения: " << duration.count() << " сек." << endl;

    // Сохраняем результат для верификации
    ofstream out("result.txt");
    out << n << endl;
    for (int i = 0; i < n * n; ++i) {
        out << C[i] << ( (i + 1) % n == 0 ? "\n" : " " );
    }

    return 0;
}
