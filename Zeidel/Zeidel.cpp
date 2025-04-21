#include <iostream>
#include <vector>
#include <cmath>

using namespace std;


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

bool validation_matrix(vector<vector<double>> &matrix) {
    int sum_row;
    int sum_column;
    int n = matrix.size();

    for (int i = 0; i < n; ++i) {
        if (matrix[i][i] == 0)
            return false;
    }

    for (int i = 0; i < n; ++i) {
        sum_row = sum_column = 0;
        for (int j = 0; j < n; ++j) {
            sum_row += abs(matrix[i][j]);
            sum_column += abs(matrix[j][i]);
        }

        if (!sum_row || !sum_column)
            return false;
    }

    for (int i = 0; i < n; ++i) {
        sum_row = 0;
        for (int j = 0; j < n; ++j) {
            sum_row += abs(matrix[i][j]);
        }

        if(abs(matrix[i][i]) < (sum_row - abs(matrix[i][i])))
            return false;
    }

    return true;
}

bool stop_Zeidel(vector<double> &main_approximation, vector<double> &prev_approximation, double epsilon) {
    int coincidence = 0;
    double delta;
    for (int i = 0; i < main_approximation.size(); ++i) {
        delta = abs(main_approximation[i] - prev_approximation[i]);
        if (epsilon > delta)
            ++coincidence;
    }

    if (coincidence == main_approximation.size())
        return true;
    else
        return false;
}

vector<double> Zeidel(vector<vector<double>> &matrix, const double epsilon) {
    int n = matrix.size();
    double sum = 0;

    if (!validation_matrix(matrix)) {
        cout << "Не валидная матрица" << endl;
        return vector<double>(n, -1);
    }

    vector<double> main_approximation(n, 0);
    vector<double> tmp_approximation(n, 0);
    vector<double> prev_approximation(n, 0);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j)
                matrix[i][j] = -matrix[i][j] / matrix[i][i];
        }
        matrix[i][n] /= matrix[i][i];
        matrix[i][i] = 1;
    }

    do {
        prev_approximation = main_approximation;
        for (int i = 0; i < n; ++i) {
            sum = matrix[i][n];
            for (int j = i+1; j < n; ++j) {
               // if (i != j)
                 sum += matrix[i][j] * prev_approximation[j];
            }
            for (int j = 0; j < i; ++j) {
                // if (i != j)
                  sum += matrix[i][j] * tmp_approximation[j]; }

        tmp_approximation[i] = sum;

        }

    main_approximation = tmp_approximation;
    
    } while (!stop_Zeidel(main_approximation, prev_approximation, epsilon));

    return main_approximation;
}

int main() {

    double epsilon = 0.0001;
    vector<vector<double>> matrix = inputMatrixFromKeyboard();

    vector<double> result = Zeidel(matrix, epsilon);

    for (int i = 0; i < result.size(); ++i) {
        cout << "X" << i << " = " << result[i] << endl;
    }

    return 0;
}