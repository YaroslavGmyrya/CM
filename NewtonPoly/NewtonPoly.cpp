#include <iostream>
#include <vector>
#include <fstream>
#include <cctype>

using namespace std;

vector<vector<double>> read_data(const string &filename){

    fstream file(filename);
    
    if(!file.is_open()){
        cout << "Error in reading data from file" << endl;
        return {};
    }

    vector<vector<double>> result;
    vector<double> row;

    char tmp_char;
    double tmp_num;
    string tmp_str;

    while(file.get(tmp_char)){

        if(tmp_char != ' ' && tmp_char != '\n' || tmp_char == '.' || tmp_char == '-')
            tmp_str += tmp_char;

        else {

            try{
                tmp_num = stod(tmp_str);
            }

            catch(const std::invalid_argument& e){
                cout << "Invalid value in file!" << endl;
                return {};
            }

            row.push_back(tmp_num);

            if(tmp_char == '\n'){
                result.push_back(row);
                row.clear();
            }
                

            tmp_str.clear();
        }
           
    }

    file.close();

    return result;
}

vector<double> div_diff(vector<vector<double>> data){
    int n = data[0].size();

    vector<vector<double>> diffTable(n, vector<double>(n, 0.0));
    vector<double> coef;

    for (int i = 0; i < n; ++i) {
        diffTable[i][0] = data[1][i];
    }

    for (int j = 1; j < n; ++j) {
        for (int i = 0; i < n - j; ++i) {
            diffTable[i][j] = (diffTable[i + 1][j - 1] - diffTable[i][j - 1]) / (data[0][i + j] - data[0][i]);
        }
    }

    for(int i = 0; i < n; ++i){
        coef.push_back(diffTable[0][i]);
    }

    return coef;
}

double NewtonPoly(string filename, double x){
    vector<vector<double>> data = read_data(filename);

    vector<double> coef = div_diff(data);

    double result = coef[0];
    double tmp = 1;

    for(int i = 1; i < coef.size(); ++i){
        for(int j = 0; j < i; ++j){
            tmp *= (x - data[0][j]);
        }

        result += coef[i] * tmp;
        tmp = 1;
    }

    return result;
}

int main(){
    double res = NewtonPoly("123", 10);
    cout << "Answer: " <<  res << endl;
    return 0;
}