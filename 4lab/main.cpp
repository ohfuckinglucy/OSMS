#include <cstdio>
#include <malloc.h>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <tgmath.h>

using namespace std;

int16_t temp1, temp2;

template <typename T>
void show_arr(string name, const T *array, size_t len){
    cout << name << ": ";
    for (size_t i = 0; i < len; i ++){
        cout << array[i];
    }
    cout << endl;
}

template <typename T>
void autocorr(const T *eq_array, size_t len){
    double result[len];

    cout << "Сдвиг | ";
    for (size_t i = 1; i <= len; i ++){
        cout << "Бит" << setw(2) << setfill('0') << i << " | ";
    }
    cout << "Автокорреляция" << endl;

    T *array = (T*)malloc(len * sizeof(T));

    for (size_t j = 0; j < len+1; j ++){
        for (size_t i = 0; i < len; i ++){
            array[i] = eq_array[i];
        }

        cout << setw(2) << setfill('0') << j << "    | ";

        T *temp_shift = (T*)malloc(len * sizeof(T));
        for (size_t i = 0; i < len; i++) {
            temp_shift[i] = array[(i - j + len) % len];
        }
        for (size_t i = 0; i < len; i++) {
            array[i] = temp_shift[i];
        }
        free(temp_shift);

        for (size_t i = 0; i < len; i ++){
            cout << array[i] << "     | ";
        }

        int16_t eq = 0;
        int16_t neq = 0;

        for (size_t i = 0; i < len; i ++){
            if (array[i] == eq_array[i]){
                eq ++;
            } else {
                neq ++;
            }
        }

        result[j] = ((1/(double)len)*(eq-neq));

        cout << " " << result[j] << endl;
    }

    free(array);
}

template <typename T>
bool check_balance(const T *seq, size_t len){
    int ones = 0;
    int zeros = 0;
    for (size_t i = 0; i < len; i++){
        if (seq[i] == 1) ones++;
        else zeros++;
    }
    cout << "Сбалансированность: 0 = " << zeros << ", 1 = " << ones << endl;
    return abs(ones - zeros) <= 1;
}

template <typename T>
bool check_cycles(const T *seq, size_t len){
    cout << "Цикличность (длины одинаковых битов подряд): ";
    int count = 1;
    int max_len = 5;
    int cycle_count[max_len] = {0};
    int total_cycles = 0;

    for (size_t i = 1; i < len; i++){
        if (seq[i] == seq[i-1]){
            count++;
        } else {
            cout << count << " ";
            if (count >= max_len) return false;
            cycle_count[count]++;
            total_cycles++;
            count = 1;
        }
    }
    cout << count << endl;
    if (count >= max_len) return false;
    cycle_count[count]++;
    total_cycles++;

    cout << "Кол-во циклов размером 1, 2, 3, 4" << endl;

    for (size_t i = 1; i < max_len; i ++){
        cout << cycle_count[i] << " ";
    }
    cout << endl;
    cout << "Всего циклов: " << total_cycles << endl;
    for (int i = 1; i < max_len; i++){
        if (cycle_count[i] > 0){
            double fraction = (double)cycle_count[i] / total_cycles;
            double expected = 1.0 / (1 << i);
            if (fabs(fraction - expected) > 0.15) return false;
        }
    }

    return true;
}

template <typename T>
bool check_autocorr(const T *seq, size_t len){
    double max_corr = 0;
    double result[len];

    T *array = (T*)malloc(len * sizeof(T));
    for (size_t j = 1; j < len; j ++){
        for (size_t i = 0; i < len; i ++){
            array[i] = seq[i];
        }

        T *temp_shift = (T*)malloc(len * sizeof(T));
        for (size_t i = 0; i < len; i++) {
            temp_shift[i] = array[(i - j + len) % len];
        }
        for (size_t i = 0; i < len; i++) {
            array[i] = temp_shift[i];
        }
        free(temp_shift);

        int16_t eq = 0;
        int16_t neq = 0;
        for (size_t i = 0; i < len; i ++){
            if (array[i] == seq[i]) eq++;
            else neq++;
        }
        result[j] = ((1/(double)len)*(eq-neq));
        if (fabs(result[j]) > max_corr) max_corr = fabs(result[j]);
    }

    free(array);

    cout << "Максимальная автокорреляция на сдвигах != 0: " << max_corr << endl;

    return max_corr < 0.3;
}

template <typename T>
void check_properties(const T *seq, size_t len){
    bool balance_ok = check_balance(seq, len);
    bool cycles_ok = check_cycles(seq, len);
    bool autocorr_ok = check_autocorr(seq, len);

    cout << "Свойства: " << ((balance_ok && cycles_ok && autocorr_ok) ? "соблюдены" : "не соблюдены") << endl;
}


// Вариант 20 - x = 10100 y = x + 7 = 11011

int main(){
    // Две последовательности битов  (линейно свдиговые регистры)
    size_t m = 5;
    int16_t Rex_x[] = {1, 0, 1, 0 , 0};
    int16_t Rex_y[] = {1, 1, 0, 1 , 1};

    size_t N = 31;
    int16_t *out = (int16_t*)malloc(N * sizeof(int16_t));

    for (size_t i = 0; i < N; i ++){
        out[i] = Rex_x[4] ^ Rex_y[4];

        temp1 = Rex_x[2] ^ Rex_x[4];
        temp2 = Rex_y[2] ^ Rex_y[4];

        for (size_t j = m-1; j > 0; j --){
            Rex_x[j] = Rex_x[j-1];
            Rex_y[j] = Rex_y[j-1];
        }
        Rex_x[0] = temp1;
        Rex_y[0] = temp2;
    }

    show_arr("Rex_x[]", Rex_x, m);
    show_arr("Rex_y[]", Rex_y, m);

    show_arr("out[]", out, N);

    check_properties(out, N);

    autocorr(out, N);

    // теперь x = 10101, а y = 10110
    int16_t Rex_x_2[] = {1, 0, 1, 0 , 1};
    int16_t Rex_y_2[] = {1, 0, 1, 1 , 0};

    int16_t *out_2 = (int16_t*)malloc(N * sizeof(int16_t));


    for (size_t i = 0; i < N; i ++){
        out_2[i] = Rex_x_2[4] ^ Rex_y_2[4];

        temp1 = Rex_x_2[2] ^ Rex_x_2[4];
        temp2 = Rex_y_2[2] ^ Rex_y_2[4];

        for (size_t j = 4; j > 0; j --){
            Rex_x_2[j] = Rex_x_2[j-1];
            Rex_y_2[j] = Rex_y_2[j-1];
        }
        Rex_x_2[0] = temp1;
        Rex_y_2[0] = temp2;
    }


    show_arr("Rex_x_2[]", Rex_x_2, m);
    show_arr("Rex_y_2[]", Rex_y_2, m);

    show_arr("out_2[]", out_2, N);
    check_properties(out_2, N);

    int16_t eq = 0;
    int16_t neq = 0;

    for (size_t i = 0; i < N; i ++){
        if (Rex_x_2[i] == Rex_y_2[i]){
            eq ++;
        } else {
            neq ++;
        }
    }

    double result = ((1/(double)N)*(eq-neq));

    cout << "Корреляция исходной и новой битовой последовательности: " << result << endl;

    free(out);
    free(out_2);

    return 0;
}