#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <iomanip>

using namespace std;

// Функция для безопасного ввода целого положительного числа
int read_positive_int(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value && value > 0) {
            return value;
        }
        cout << "Ошибка! Введите положительное целое число." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Функция для безопасного ввода вещественного числа
double read_double(const string& prompt) {
    double value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            return value;
        }
        cout << "Ошибка! Введите число." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Приведение матрицы к трапециевидной форме (прямой ход метода Гаусса)
void to_trapezoidal(vector<vector<double>>& A, const double eps = 1e-9) {
    int m = A.size();
    int n = A[0].size();
    int row = 0;
    for (int col = 0; col < n && row < m; ++col) {
        // Поиск строки с ненулевым элементом в столбце col
        int pivot = -1;
        for (int i = row; i < m; ++i) {
            if (fabs(A[i][col]) > eps) {
                pivot = i;
                break;
            }
        }
        if (pivot == -1) continue;

        // Меняем местами строки row и pivot
        if (pivot != row) {
            swap(A[row], A[pivot]);
        }

        // Нормируем ведущую строку (делим на ведущий элемент)
        double div = A[row][col];
        for (int j = col; j < n; ++j) {
            A[row][j] /= div;
        }

        // Обнуляем элементы под ведущим
        for (int i = row + 1; i < m; ++i) {
            double factor = A[i][col];
            if (fabs(factor) > eps) {
                for (int j = col; j < n; ++j) {
                    A[i][j] -= factor * A[row][j];
                }
            }
        }
        ++row;
    }
}

// Вычисление ранга как числа ненулевых строк
int matrix_rank(const vector<vector<double>>& A, const double eps = 1e-9) {
    int rank = 0;
    for (const auto& row : A) {
        for (double x : row) {
            if (fabs(x) > eps) {
                ++rank;
                break;
            }
        }
    }
    return rank;
}

// Вывод матрицы
void print_matrix(const vector<vector<double>>& A) {
    for (const auto& row : A) {
        for (double x : row) {
            cout << setw(10) << fixed << setprecision(4) << x;
        }
        cout << endl;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    cout << "Программа вычисления ранга матрицы методом Гаусса.\n" << endl;

    int m = read_positive_int("Введите количество строк: ");
    int n = read_positive_int("Введите количество столбцов: ");

    vector<vector<double>> A(m, vector<double>(n));
    cout << "Вводите элементы матрицы построчно (через пробел или Enter):" << endl;
    for (int i = 0; i < m; ++i) {
        cout << "Строка " << i + 1 << ": ";
        for (int j = 0; j < n; ++j) {
            A[i][j] = read_double("");
        }
    }

    // Копия для вывода исходной матрицы
    auto original = A;

    to_trapezoidal(A);

    cout << "\nИсходная матрица:\n";
    print_matrix(original);
    cout << "\nТрапециевидная форма:\n";
    print_matrix(A);

    int rank = matrix_rank(A);
    cout << "\nРанг матрицы: " << rank << endl;

    return 0;
}