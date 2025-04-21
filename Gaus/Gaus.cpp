#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
using namespace std;


void print_matrix(vector<vector<double>> matrix){
    for(int i = 0; i < matrix.size(); ++i){
        for(int j = 0; j < matrix.size() + 1; ++j){
            cout << matrix[i][j] << " ";
        }

        cout << endl;
    }
}

vector<vector<double>> read_matrix(const string &filename, int n){
    vector<vector<double>>matrix(n, vector<double>(n+1, 0));

    ifstream file(filename, ios_base::binary);
    if (!file.is_open()) {
        cout << "Error in opening file" << endl;
        return vector<vector<double>>(n,vector<double>(n+1, 0));
    }

    for (int i = 0; i < n; ++i) {
        file.read((char*)(matrix[i].data()), matrix[i].size() * sizeof(double));
    }

    file.close();

    return matrix;
}


vector<vector<double>> inputMatrixFromKeyboard() {
    int n;
    cout << "Введите количество уравнений: ";
    cin >> n;

    vector<vector<double>> matrix(n, vector<double>(n + 1));

    cout << "Введите элементы матрицы (коэффициенты и свободные члены):" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n + 1; ++j) {
            if (j == n) {
                cout << "Введите свободный член для уравнения " << i + 1 << ": ";
            } else {
                cout << "Введите коэффициент a[" << i + 1 << "][" << j + 1 << "]: ";
            }
            cin >> matrix[i][j];
        }
    }

    return matrix;
}

vector<double> solveGauss(vector<vector<double>> matrix) {
    int n = matrix.size();

    for (int i = 0; i < n; ++i) {
        int maxRow = i;
        for (int k = i + 1; k < n; ++k) {
            if (abs(matrix[k][i]) > abs(matrix[maxRow][i])) {
                maxRow = k;
            }
        }

        swap(matrix[i], matrix[maxRow]);

        for (int k = i + 1; k < n; ++k) {
            double div = matrix[k][i] / matrix[i][i];
            for (int j = i; j < n + 1; ++j) {
                matrix[k][j] -= div * matrix[i][j];
            }
        }
    }

    vector<double> result(n);
    for (int i = n - 1; i >= 0; --i) {
        result[i] = matrix[i][n] / matrix[i][i];
        for (int k = i - 1; k >= 0; --k) {
            matrix[k][n] -= matrix[k][i] * result[i];
        }
    }

    return result;
}

int main() {

    vector<vector<double>> matrix;
    int choice;
    int n;
    
    cout << "Выберите способ ввода матрицы:" << endl;
    cout << "1. Ввод с клавиатуры" << endl;
    cout << "2. Загрузить из файла" << endl;

    cin >> choice;

    switch(choice){

        case 1: 
            matrix = inputMatrixFromKeyboard();
            break;

        case 2:
            cout << "Введите количество уравнений: ";
            cin >> n;
            switch(n){

                case 2:
                    matrix = read_matrix("2x2", 2);
                    break;

                case 3:
                    matrix = read_matrix("3x3", 3);
                    break;

                case 4:
                    matrix = read_matrix("4x4", 4);
                    break;

                default:
                    cout << "Ошибка ввода" << endl;
                    return -1;
            }   
    }

    cout << endl << "Исходная матрица:" << endl;

    print_matrix(matrix);

    auto start_time = chrono::steady_clock::now();
    vector<double> result = solveGauss(matrix);
    auto end_time = std::chrono::steady_clock::now();
    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);

    cout << "Решение системы:" << endl;
    for (int i = 0; i < result.size(); ++i) {
        cout << "x" << i << " = " << result[i] << endl;
    }

    std::cout << "Время работы программы: " << elapsed_ns.count() << " ns\n";

    return 0;
}