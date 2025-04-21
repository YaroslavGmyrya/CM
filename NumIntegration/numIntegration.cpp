#include <iostream>
#include <cmath>

using namespace std;

double f(double x){
    return exp(-x*x);
}

double center_rectangle(double a, double b, double n){
    double h = (b-a)/n;
    double x,s = 0;

    for(int i = 0; i < n; ++i){
        x = a + h/2 + i * h;
        s += f(x);
    }

    s *= h;

    return s;
}

double unge(double a, double b, double epsilon){
    double n = 1;
    double s1,s2 = 0;
    double k = 2;
    double d = 100;

    do{

        s1 = center_rectangle(a,b,n);
    
        n *= 2;
    
        s2 = center_rectangle(a,b,n);
    
        d = abs(s2-s1)/2;

    }while(d >= epsilon);

    return s2;

}

int main(){
    double a,b,eps;

    cout << "Enter left border: ";
    cin >> a;

    cout << "Enter right border: ";
    cin >> b;

    cout << "Enter epsilon: ";
    cin >> eps;

    double result = unge(a,b,eps);

    cout << result << endl;

    return 0;
}