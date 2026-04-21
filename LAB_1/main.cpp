#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

using namespace std;

// Функция для чтения матрицы из файла
vector<double> readMatrix(const string& filename, int& n) {
    ifstream in(filename);
    in >> n;
    vector<double> matrix(n * n);
    for (int i = 0; i < n * n; ++i) in >> matrix[i];
    return matrix;
}

// Функция для записи матрицы в файл
void saveMatrix(const string& filename, const vector<double>& matrix, int n) {
    ofstream out(filename);
    out << n << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            out << matrix[i * n + j] << " ";
        }
        out << endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cout << "Usage: " << argv[0] << " <matrixA.txt> <matrixB.txt>" << endl;
        return 1;
    }

    int n1, n2;
    vector<double> A = readMatrix(argv[1], n1);
    vector<double> B = readMatrix(argv[2], n2);

    if (n1 != n2) {
        cerr << "Error: Matrices must be of the same size!" << endl;
        return 1;
    }

    int n = n1;
    vector<double> C(n * n, 0.0);

    cout << "Task size: " << n << "x" << n << endl;

    // Начало замера времени
    auto start = chrono::high_resolution_clock::now();

    // Классическое перемножение (наивный алгоритм)
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                C[i * n + j] += A[i * n + k] * B[k * n + j];
            }
        }
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> diff = end - start;

    cout << "Execution time: " << diff.count() << " seconds" << endl;

    saveMatrix("result.txt", C, n);
    return 0;
}
