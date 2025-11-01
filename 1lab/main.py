import matplotlib.pyplot as plt
import numpy as np

## 1 - Сгенерировать и визуализировать сигнал

f = 7
t = np.linspace(0, 1, 1000)

s_t = np.cos(4*np.pi * f * t) + np.cos(6*np.pi*f*t)

plt.plot(t, s_t, 'r')
plt.title("Визуализация исходного сигнала")
plt.xlabel("Время")
plt.ylabel("Амплитуда")
plt.grid()
plt.show()

## 2 - Определить максимальную частоту в спектре: w = 2pi*f f = f = w/2pi -> 42pi/2pi = 21

## 3 - По теореме Котельникова fs >= fmax * 2 -> fs >= 42

## 4 - Оцифровать сигнал с fs

fs = 42
N = fs


t_sampled = np.linspace(0, 1, N, endpoint=False)
s_t_sampled = np.cos(4*np.pi * f * t_sampled) + np.cos(6 * np.pi * f * t_sampled)

## 5 - Прямое дискретное преобразование Фурье 

# ДПФ

s_t_sampled_f = np.zeros(N, dtype=complex)

for k in range(0, N):
    sum_val = 0
    for n in range(0, N):
        sum_val = sum_val + (s_t_sampled[n] * np.exp(-1j*2*np.pi*((k*n)/N)))
    s_t_sampled_f[k] = sum_val

s_t_sampled_f_amplitude = np.abs(s_t_sampled_f[:N//2 + 1]) # Амплитудная ось
s_t_sampled_f_amplitude_N = np.abs(s_t_sampled_f[:N//2 + 1])/N # Амплитудная ось (Нормированная)

s_t_sampled_f_freq = np.zeros(N//2 + 1) # Частотная ось
for k in range(0, N//2 + 1):
    s_t_sampled_f_freq[k] = (k/N)*fs

# Находим ширину спектра
peak_freqs = s_t_sampled_f_freq[s_t_sampled_f_amplitude_N > 0.4]

bandwidth = peak_freqs.max() - peak_freqs.min()

print(f'Ширина спектра: {bandwidth}.')

# Находим обьем памяти занимаемый s_t_sampled_f

print(f'Объем памяти выделенной под массив временных отсчетов сигнала: {s_t_sampled_f.nbytes} байт.')

## 6 - Сравнение оригинального и воставновленного сигнала

plt.plot(t, s_t, 'b', label="Оригинальный сигнал")
plt.plot(t_sampled, s_t_sampled, 'm--', marker='o', label="Востанновленный сигнал")
plt.title("Сравнение восстановленного и оригинального сигнала. (fs = 42)")
plt.xlabel("t, c.")
plt.ylabel("qwe")
plt.grid()
plt.legend()
plt.show()

## 7 - Увеличьте частоту дискретизации в 4 раза и проделайте задания из п.4-6. 

# 7.4 Оцифровать сигнал с fs

fs = 42*4
N = fs


t_sampled = np.linspace(0, 1, N, endpoint=False)
s_t_sampled = np.cos(4*np.pi * f * t_sampled) + np.cos(6 * np.pi * f * t_sampled)

# 7.5 Прямое дискретное преобразование Фурье 

# ДПФ

s_t_sampled_f = np.zeros(N, dtype=complex)

for k in range(0, N):
    sum_val = 0
    for n in range(0, N):
        sum_val = sum_val + (s_t_sampled[n] * np.exp(-1j*2*np.pi*((k*n)/N)))
    s_t_sampled_f[k] = sum_val

s_t_sampled_f_amplitude = np.abs(s_t_sampled_f[:N//2 + 1]) # Амплитудная ось
s_t_sampled_f_amplitude_N = np.abs(s_t_sampled_f[:N//2 + 1])/N # Амплитудная ось (Нормированная)

s_t_sampled_f_freq = np.zeros(N//2 + 1) # Частотная ось
for k in range(0, N//2 + 1):
    s_t_sampled_f_freq[k] = (k/N)*fs

# Находим ширину спектра
peak_freqs = s_t_sampled_f_freq[s_t_sampled_f_amplitude_N > 0.4]

bandwidth = peak_freqs.max() - peak_freqs.min()

print(f'Ширина спектра: {bandwidth}. (fs = 42*4)')

# Находим обьем памяти занимаемый s_t_sampled_f

print(f'Объем памяти выделенной под массив временных отсчетов сигнала: {s_t_sampled_f.nbytes} байт. (fs = 42*4)')

# 7.6 Сравнение оригинального и воставновленного сигнала

plt.plot(t, s_t, 'b', label="Оригинальный сигнал")
plt.plot(t_sampled, s_t_sampled, 'm--', marker='o', label="Востанновленный сигнал")
plt.title("Сравнение восстановленного и оригинального сигнала. (fs = 42*4)")
plt.xlabel("t, c.")
plt.ylabel("qwe")
plt.grid()
plt.legend()
plt.show()