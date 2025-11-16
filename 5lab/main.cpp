#include <cstdio>
#include <malloc.h>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <malloc.h>

using namespace std;

template <typename T>
void show_arr(string name, const T *array, size_t len){
    cout << name << ": ";
    for (size_t i = 0; i < len; i ++){
        cout << array[i];
    }
    cout << endl;
}

int compute_CRC(int16_t *bits, int16_t *res, int16_t *G_x, int16_t N, int16_t r){
    show_arr("Исходный битовый пакет", bits, N);

    int16_t *temp  = (int16_t*)calloc(N+r, sizeof(int16_t)); 

    for (size_t i = 0; i < N; i ++){
        temp[i] = bits[i];
    }

    if ((temp == NULL)){
        perror("malloc");
        return 1;
    }

    for(size_t i = 0; i < N; i ++){
        if (temp[i] == 1){
            for(size_t j = 0; j <= r; j++){
                temp[i+j] ^= G_x[j];
            }
        }
    }

    for(size_t i = 0; i < r; i++){
        res[i] = temp[N + i];
    }

    free(temp);
    
    show_arr("CRC", res, r);

    for(size_t i = N; i < N+r; i++){
        bits[i] = res[i - N];
    }

    show_arr("Битовый пакет с CRC", bits, N+r);

    return 0;
}


int verify(const int16_t *bits, int16_t *G_x, int16_t N, int16_t r){
    int16_t *temp  = (int16_t*)calloc(N+r, sizeof(int16_t)); 
    int16_t *res_temp  = (int16_t*)calloc(r, sizeof(int16_t));

    for (size_t i = 0; i < N+r; i ++){
        temp[i] = bits[i];
    }

    for(size_t i = 0; i < N; i ++){
        if (temp[i] == 1){
            for(size_t j = 0; j <= r; j++){
                temp[i+j] ^= G_x[j];
            }
        }
    }

    for (size_t i = N; i < N+r; i ++){
        res_temp[i - N] = temp[i];
    }

    free(temp);

    for(size_t i = 0; i < r; i ++){
        if(res_temp[i] != 0){
            free(res_temp);
            return 1;
        }
    }
    free(res_temp);

    return 0;
}

void verify_count(const int16_t *bits, int16_t *G_x, int16_t N, int16_t r){
    int16_t *temp  = (int16_t*)calloc(N+r, sizeof(int16_t)); 
    int16_t detected = 0;
    int16_t missed = 0;

    for (size_t i = 0; i < N+r; i ++){
        temp[i] = bits[i];
    }

    for (int i = 0; i < 257; i++) {
        temp[i] ^= 1;
        if (verify(temp, G_x, N, r) != 0){
            detected++;
        } else{
            missed++;
        }
    }

    cout << "Для N = " << N << endl;
    cout << "Обнаружено " << detected << " ошибок" << endl;
    cout << "Не обнаружено " << missed << " ошибок" << endl;

    free(temp);
}

// G(x) = 1, 1, 1, 0, 1, 1, 1, 0

int main(){
    srand(time(0));
    int16_t N = 20 + 20; // Длина бит: 20 + порядковый номер в журнале
    int16_t r = 7; // Стень полинома
    int16_t *bits = (int16_t*)calloc(N+r, sizeof(int16_t));
    int16_t *res = (int16_t*)malloc(r * sizeof(int16_t));
       
    if ((bits == NULL) || (res == NULL)){
        perror("malloc");
        return 1;
    }

    int16_t G_x[] = {1, 1, 1, 0, 1, 1, 1, 0};

    for (size_t i = 0; i < N; i ++){
        bits[i] = rand() % 2;
    }

    compute_CRC(bits, res, G_x, N, r);
    cout << "verify: " << verify(bits, G_x, N, r) << endl;
    cout << endl;

    free(bits);

    N = 250;
    int16_t *bits2 = (int16_t*)calloc(N+r, sizeof(int16_t));

    for (size_t i = 0; i < N; i ++){
        bits2[i] = rand() % 2;
    }

    compute_CRC(bits2, res, G_x, N, r);
    cout << "verify: " << verify(bits2, G_x, N, r) << endl;
    cout << endl;
    verify_count(bits2, G_x, N, r);

    free(res);
    
    return 0;
}