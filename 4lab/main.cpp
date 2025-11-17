#include <cstdio>
#include <malloc.h>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <cmath>

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

template<typename T>
int verify(const T *array, int16_t len){
    int16_t count_of_one = 0;
    int16_t count_of_null = 0;

    int16_t cicle = 0;
    int16_t count_1 = 0;
    int16_t count_2 = 0;
    int16_t count_3 = 0;
    int16_t count_4 = 0;
    int16_t count_5 = 0;



    for (size_t i = 0; i < len; i ++){
        cicle = 0;

        for (size_t j = i; (j < len) && (array[j] == 1); j ++){
            cicle += 1;
        }
        for (size_t j = i; (j < len) && (array[j] == 0); j ++){
            cicle += 1;
        }
        if (cicle == 1){
            count_1 += 1;
        } else if (cicle == 2) {
            count_2 += 1;
        } else if (cicle == 3) {
            count_3 += 1;
        } else if (cicle == 4) {
            count_4 += 1;
        } else{
            count_5 += 1;
        }

    }
    cout << "count_1: " << count_1 << endl;
    cout << "count_2: " << count_2 << endl;
    cout << "count_3: " << count_3 << endl;
    cout << "count_4: " << count_4 << endl;


    for (size_t i = 0; i < len; i++){
        if (array[i] == 1){
            count_of_one++;
        } else {
            count_of_null++;
        }
    }

    cout << "count_of_one: " << count_of_one << endl;
    cout << "count_of_null: " << count_of_null << endl;

    if (abs(count_of_one - count_of_null) > 1){
        return 1;
    }
    
    return 0;
}

// Вариант 20 - x = 10100 y = x + 7 = 11011

int main(){
    // Две последовательности битов  (линейно свдиговые регистры)
    size_t m = 5;
    int16_t Rex_x[] = {1, 0, 0, 0, 0};
    int16_t Rex_y[] = {0, 0, 1, 0, 0};

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
    if (verify(out, N) == 0){
        cout << "posledovatelnost: psevdoslu4aina" << endl;
    } else {
        cout << "posledovatelnost: nepsevdoslu4aina" << endl;
    }

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