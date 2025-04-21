#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void print_matrix(vector<vector<double>> matrix){
    for(int i = 0; i < matrix.size(); ++i){
        for(int j = 0; j < matrix.size() + 1; ++j){
            cout << matrix[i][j] << " ";
        }

        cout << endl;
    }
}

void write_matrix(const string &filename, vector<vector<double>> matrix){

    int n = matrix.size();         

    ofstream file(filename, ios_base::binary);
    if (!file.is_open()) {
        cout << "Error in opening file" << endl;
        return;
    }

    for (int i = 0; i < n; ++i) {
        file.write((char*)(matrix[i].data()), matrix[i].size() * sizeof(double));
    }

    file.close();
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

int main() {

    vector<vector<double>> _2x2 = { //x0 = 0.571428 x1 = 1.28571
        {2, 3, 5},  
        {4, -1, 1} 
    };

    vector<vector<double>> _3x3 = { //x0 = 7. x1 = 5, x2 = 2
        {2, 4, 1, 36},  
        {5, 2, 1, 47}, 
        {2, 3, 4, 37}  
    };

    vector<vector<double>> _4x4 = {    //x0 = 0.5, x1 = 1, x2 = x3 = -0.5
        {2, -1, 3, -5, 1}, 
        {1, -1, -5, 0, 2},  
        {3, -2, -2, -5, 3}, 
        {7, -5, -9, -10, 8} 
    };


    write_matrix("2x2", _2x2);
    write_matrix("3x3", _3x3);
    write_matrix("4x4", _4x4);  
    
    return 0;
}


void writeMatrixToFile(vector<vector<double>>& matrix, const string& filename) {
    ofstream File(filename, ios::app | ios::binary);
    if (!File) {
        cout << "Ошибка открытия файла для записи!" << endl;
        return;
    }

    int n = matrix.size();
    File.write((char*)(n), sizeof(n));

    for (int i = 0; i < matrix.size(); ++i) {
        File.write((char*)(matrix[i].data()), matrix.size() * sizeof(double));
    }

    File.close();
}

vector<vector<double>> readMatrixFromFile(const string& filename, int n) {
    ifstream inFile(filename, ios::binary);
    if (!inFile) {
        cout << "Ошибка открытия файла для чтения!" << endl;
        return {};
    }

    vector<vector<double>> matrix;

    while (inFile) {

        int read_n;
        inFile.read((char*)(&read_n), sizeof(read_n));

        if (read_n == n) {
            matrix.resize(read_n, vector<double>(read_n));
            for (int i = 0; i < read_n; ++i) {
                inFile.read((char*)(matrix[i].data()), read_n * sizeof(double));
            }
            break; 
        } else {
            inFile.seekg(read_n * read_n * sizeof(double), ios::cur);
        }
    }

    inFile.close();
    return matrix;
}
