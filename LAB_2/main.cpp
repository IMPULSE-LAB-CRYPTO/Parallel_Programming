#include <iostream>
#include <vector>
#include <fstream>
#include <omp.h>
#include <string>

using namespace std;

// Функция для чтения матрицы из файла (одномерный вектор для скорости)
bool readMatrix(const string& filename, int& n, vector<double>& matrix) {
    ifstream in(filename);
    if (!in.is_open()) return false;
    in >> n;
    matrix.resize(n * n);
    for (int i = 0; i < n * n; ++i) in >> matrix[i];
    return true;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <num_threads>" << endl;
        return 1;
    }

    int num_threads = stoi(argv[1]);
    int n1, n2;
    vector<double> A, B;

    if (!readMatrix("A.txt", n1, A) || !readMatrix("B.txt", n2, B)) {
        cerr << "Error opening files A.txt or B.txt!" << endl;
        return 1;
    }

    int n = n1;
    vector<double> C(n * n, 0.0);

    // Устанавливаем количество потоков
    omp_set_num_threads(num_threads);

    // Замер времени
    double start_time = omp_get_wtime();

    // Параллельное умножение
    // collapse(2) объединяет два внешних цикла в один большой итератор для нитей
    #pragma omp parallel for collapse(2) schedule(static)
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            double sum = 0.0;
            for (int k = 0; k < n; ++k) {
                sum += A[i * n + k] * B[k * n + j];
            }
            C[i * n + j] = sum;
        }
    }

    double end_time = omp_get_wtime();
    double exec_time = end_time - start_time;

    cout << "Threads: " << num_threads << " | Size: " << n << " | Time: " << exec_time << " sec." << endl;

    // Сохраняем результат для проверки корректности
    ofstream out("result.txt");
    out << n << endl;
    for (int i = 0; i < n * n; ++i) {
        out << C[i] << ( (i + 1) % n == 0 ? "\n" : " " );
    }

    return 0;
}
