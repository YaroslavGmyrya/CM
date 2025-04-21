#include <iostream>
#include <cmath>

using namespace std;

double f(double x){
    return 0.5 * exp(-sqrt(x)) - 0.2 * sqrt(pow(x,3)) + 2;
}

bool check_solution(double a, double b){
    if((f(a) * f(b)) < 0)
        return true;
    return false;
}


double method_chord(double a, double b, double e){

    if(!check_solution(a,b))
        return 0;

    double x_next = 0;
    double tmp;

    do{
        tmp = x_next;
        x_next = a - f(a) * (b - a) / (f(b) - f(a));
        a = b;
        b = tmp;
    } while (abs(x_next - b) > e);

    return x_next;
}

int main(){

    double a,b;

    cout << "Enter left border" << endl;
    cin >> a;

    cout << "Enter right border" << endl;
    cin >> b;

    double e = 0.001;

    double x = method_chord(a, b, e);

    cout << "Solution: " << x << endl;

    return 0;
}



