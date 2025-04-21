#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

#define a_E 0.999
#define a_I 0.999
#define k 0.042
#define p 0.952
#define B 0.999
#define u 0.0188
#define c_isol 0
#define E0 99
#define R0 24
#define tau 2
#define N 1625631
#define gamma 0

using namespace std;

double a(int t){
    return 2.5;
}

double c(int t){
    return 1 + c_isol * (1 - ((2 * a(t)) / 5));
}

void derivatives(double t, const std::vector<double>& y, std::vector<double>& dydt) {
    double S = y[0], E = y[1], I = y[2], R = y[3], D = y[4];
    
    dydt[0] = -c(t - tau) * (a_I * S * I / N + a_E * S * E / N) + gamma * R;
    dydt[1] = c(t - tau) * (a_I * S * I / N + a_E * S * E / N) - (k + p) * E;
    dydt[2] = k * E - B * I - u * I;
    dydt[3] = B * I + p * E - gamma * R;
    dydt[4] = u * I;
}


void euler(double t_start, double t_end, int steps, std::vector<double>& y) {
    double h = (t_end - t_start) / steps;
    std::vector<double> dydt(5); 

    for (int i = 0; i < steps; ++i) {
        double t = t_start + i * h;
        derivatives(t, y, dydt);
        
        for (int j = 0; j < 5; ++j) {
            y[j] += h * dydt[j];
        }
    }
}

int main(){

    std::vector<double> y = {
        N - 50 - 10,  // S0 = N - E0 - I0 - R0 - D0
        0,           // E0
        10,           // I0
        0,            // R0
        1             // D0
    };

    double t_start = 0.0;
    double t_end = 90.0;
    int steps = 90;  

    euler(t_start, t_end, steps, y);

    cout << fixed << setprecision(2);
    cout << "Результаты на день " << t_end << ":\n";
    cout << "S = " << y[0] << "\n";
    cout << "E = " << y[1] << "\n";
    cout << "I = " << y[2] << "\n";
    cout << "R = " << y[3] << "\n";
    cout << "D = " << y[4] << "\n";

    return 0;
}