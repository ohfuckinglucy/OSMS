#include <iostream>
#include <vector>
#include <string.h>
#include <cmath>

using namespace std;

// Ф-ия для расчета корреляции
double corr(const vector<int>& arr1, const vector<int>& arr2) {
    double sum = 0.0;
    for (size_t i = 0; i < arr1.size(); ++i) {
        sum += arr1[i] * arr2[i];
    }
    return sum;
}
// Ф-ия для расчета нормализованной корреляции
double norm_corr(const vector<int>& arr1, const vector<int>& arr2) {
    double sum1 = 0.0;
    double sum2 = 0.0;
    double sum3 = 0.0;

    for (size_t i = 0; i < arr1.size(); ++i) {
        sum1 += arr1[i] * arr2[i];
        sum2 += arr1[i] * arr1[i];
        sum3 += arr2[i] * arr2[i];
    }

    return sum1 / sqrt(sum2 * sum3);
}

int main() {
    vector<int> a = {8, 3, 7, 2, -2, -4, 1, 4};
    vector<int> b = {4, 2, 5, -1, -3, -7, 2, 1};
    vector<int> c = {-1, 0, -3, -9, 2, -2, 5, 1};

    // Вычисляем все пары
    double ab_corr = corr(a, b);
    double ac_corr = corr(a, c);
    double bc_corr = corr(b, c);

    double ab_norm = norm_corr(a, b);
    double ac_norm = norm_corr(a, c);
    double bc_norm = norm_corr(b, c);

    // Таблица корреляции
    cout << "Корреляция между a, b и c:\n";
    cout << "\\ | a   | b   | c\n";
    cout << "a | -   | " << ab_corr << " | " << ac_corr << "\n";
    cout << "b | " << ab_corr << " | -   | " << bc_corr << "\n";
    cout << "c | " << ac_corr << " | " << bc_corr << "   | -\n";

    // Таблица нормализованной корреляции
    cout << "\nНормализованная корреляция между a, b и c:\n";
    cout << "\\ | a         | b         | c\n";
    cout << "a | -         | " << ab_norm << "  | " << ac_norm << "\n";
    cout << "b | " << ab_norm << "  | -         | " << bc_norm << "\n";
    cout << "c | " << ac_norm << " | " << bc_norm << " | -\n";
}