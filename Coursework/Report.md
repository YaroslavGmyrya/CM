# Метод Эйлера для решения системы дифференциальных уравнений на примере математического моделирования и прогнозирование COVID-19 в Новосибирской области

### Цели:
- Изучить метод Эйлера для решения систем дифферециальных уравнений
- Применить метод Эйлера в моделировании и прогнозировании COVID-19 в Новосибирской области 

<h3 align="center">Ход работы: </h3>

1. Изучить метод Эйлера для решения систем дифферециальных уравнений

- **Метод Эйлера** 

Численный метод решения обыкновенных дифференциальных уравнений (ОДУ) первого порядка. Он используется, когда аналитическое решение найти сложно или невозможно. Метод основан на приближенном вычислении значений искомой функции на дискретной сетке точек

- **Основная идея**

[![2025-04-19-135305.png](https://i.postimg.cc/3J7PxqX3/2025-04-19-135305.png)](https://postimg.cc/5j7PPnKr)

[![2025-04-19-135440.png](https://i.postimg.cc/7ZtcXYpL/2025-04-19-135440.png)](https://postimg.cc/JsJPzm7w)

- Пример

[![2025-04-19-135616.png](https://i.postimg.cc/VLYV8Cw6/2025-04-19-135616.png)](https://postimg.cc/K4HN74RS)

2. Применить метод Эйлера в моделировании и прогнозировании COVID-19 в Новосибирской области 

- **Постановка задачи:**

- Решите систему уравнений модель SEIR-D для Новосибирской области с коэффициентами из таблицы 11. Решение найдите с помощью метода Эйлера на участке времени от 0 до 90 дней с точностью до 2 знака после запятой.

- Начальные данные для рассчетов

[![2025-04-19-140053.png](https://i.postimg.cc/5thf7mZj/2025-04-19-140053.png)](https://postimg.cc/Ffxt10FQ)

[![2025-04-19-143948.png](https://i.postimg.cc/6334NKcT/2025-04-19-143948.png)](https://postimg.cc/sBkgpttR)

[![2025-04-19-143958.png](https://i.postimg.cc/zBVwFK9d/2025-04-19-143958.png)](https://postimg.cc/47RhJ74t)

- Таблица с описанием и диапазоном значений для каждой переменной

[![2025-04-19-140031.png](https://i.postimg.cc/9Qv3CQ1n/2025-04-19-140031.png)](https://postimg.cc/NK7CxY36)

- Система дифференциальных уравнений, которую необходимо решить

[![2025-04-19-140015.png](https://i.postimg.cc/Vs435RDM/2025-04-19-140015.png)](https://postimg.cc/F1dPBjts)

- **Схема алгоритма**

[![2025-04-19-143704.png](https://i.postimg.cc/RCYK4Wjm/2025-04-19-143704.png)](https://postimg.cc/V5jdFkfZ)

- **Листинг программы:**

```
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

double a(int t) {
    return 2.5;
}

double c(int t) {
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

void adaptive_euler(double t_start, double t_end, double epsilon, std::vector<double>& y) {
    double t = t_start;
    double h = 1.0; 
    std::vector<double> dydt(5);
    std::vector<double> y_temp(5), y_half(5), y_full(5);
    
    while (t < t_end) {
        
        y_temp = y;
        y_half = y;
        y_full = y;
        
        derivatives(t, y_temp, dydt);
        
        for (int j = 0; j < 5; ++j) {
            y_full[j] += h * dydt[j];
        }
        
        for (int j = 0; j < 5; ++j) {
            y_half[j] += (h/2) * dydt[j];
        }

        derivatives(t + h/2, y_half, dydt);

        for (int j = 0; j < 5; ++j) {
            y_half[j] += (h/2) * dydt[j];
        }
        
        double error = 0.0;

        for (int j = 0; j < 5; ++j) {
            error = max(error, abs(y_full[j] - y_half[j]));
        }
        
        if (error < epsilon) {
            y = y_half; 
            t += h;
            h *= 1.5;
        } else {
            h *= 0.5;
            continue;
        }
    }
}

int main() {
    std::vector<double> y = {
        N - 50 - 10,  // S0 = N - E0 - I0 - R0 - D0
        0,            // E0
        10,           // I0
        0,            // R0
        0             // D0
    };

    double t_start = 0.0;
    double t_end = 90.0;
    double epsilon = 0.01; 

    adaptive_euler(t_start, t_end, epsilon, y);

    cout << fixed << setprecision(2);
    cout << "Результаты на день " << t_end << ":\n";
    cout << "S = " << y[0] << "\n";
    cout << "E = " << y[1] << "\n";
    cout << "I = " << y[2] << "\n";
    cout << "R = " << y[3] << "\n";
    cout << "D = " << y[4] << "\n";

    return 0;
}
```
