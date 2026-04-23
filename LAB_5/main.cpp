#define MS_MPI_NO_SAL
#include <iostream>
#include <vector>
#include <fstream>
#include <mpi.h>

using namespace std;

// Функция для чтения матрицы (только процессом 0)
void readMatrix(const string& filename, int& n, vector<double>& matrix) {
    ifstream in(filename.c_str());
    in >> n;
    matrix.resize(n * n);
    for (int i = 0; i < n * n; ++i) in >> matrix[i];
}

int main(int argc, char* argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);              // Инициализация MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Получение номера текущего процесса
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Получение общего количества процессов

    int n;
    vector<double> A, B, C;

    // 1. Процесс 0 читает данные и сообщает размер остальным
    if (rank == 0) {
        readMatrix("A.txt", n, A);
        readMatrix("B.txt", n, B);
        if (n % size != 0) {
            cerr << "Error: N must be divisible by process count!" << endl;
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
    }

    // Рассылаем размер N всем процессам
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int rows_per_proc = n / size;
    vector<double> local_A(rows_per_proc * n);
    vector<double> local_C(rows_per_proc * n, 0.0);
    
    // Если процесс не 0, ему все равно нужна память под B для вычислений
    if (rank != 0) B.resize(n * n);

    // 2. Рассылаем всю матрицу B всем (Bcast) и части матрицы A (Scatter)
    double start_time = MPI_Wtime();

    MPI_Bcast(B.data(), n * n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Scatter(A.data(), rows_per_proc * n, MPI_DOUBLE, 
                local_A.data(), rows_per_proc * n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // 3. Вычисления локальной части
    for (int i = 0; i < rows_per_proc; ++i) {
        for (int j = 0; j < n; ++j) {
            double sum = 0;
            for (int k = 0; k < n; ++k) {
                sum += local_A[i * n + k] * B[k * n + j];
            }
            local_C[i * n + j] = sum;
        }
    }

    // 4. Сборка результатов (Gather)
    if (rank == 0) C.resize(n * n);
    MPI_Gather(local_C.data(), rows_per_proc * n, MPI_DOUBLE, 
               C.data(), rows_per_proc * n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    double end_time = MPI_Wtime();

    // 5. Вывод (только процессом 0)
    if (rank == 0) {
        cout << "Processes: " << size << " | Size: " << n << " | Time: " << end_time - start_time << " sec." << endl;
        
        ofstream out("result.txt");
        out << n << endl;
        for (int i = 0; i < n * n; ++i) {
            out << C[i] << ((i + 1) % n == 0 ? "\n" : " ");
        }
    }

    MPI_Finalize(); // Завершение MPI
    return 0;
}
