import numpy as np
from scipy.io import wavfile
from scipy.fft import fft, fftfreq
from matplotlib import pyplot as plt

## 9 - Считывание голоса

Fs, y = wavfile.read('vocal.wav') # fs - частота дискретизации, y - массив отсчетов

## 10 - Сравнение вычисленной и взятой из файла частоты дискретизации

N = len(y) # кол-во отсчетов
duration = N / Fs # длительность записи
Fs_calc = N / duration

print("Частота дискретизации из файла:", Fs)
print("Частота дискретизации вычисленная:", Fs_calc)

# 11 - Прореживание сигнала и сохранение его в файл

y1 = y[::10]  # срез с шагом 10
Fs1 = Fs // 10  # новая частота дискретизации

wavfile.write('vocal_downsampled.wav', Fs1, y1)

print(f'Новая частота дискретизаии {Fs1}')

# 12 ДПФ для оригинального и прореженного сигнала

# 12.1 для оригинального

y_fft = fft(y)
y_fft_freq = fftfreq(N, 1/Fs)
y_fft_half = y_fft[:N//2 + 1]
y_fft_freq_half = y_fft_freq[:N//2 + 1]

amp = np.abs(y_fft_half)

amp_db = 20 * np.log10(amp/amp.max())

freqs = y_fft_freq_half[-40 < amp_db]
bandwidth = freqs.max() - freqs.min()
print(f'Ширина {bandwidth:.1f} Гц.')

# 12.2 для прореженного

N1 = len(y1)

y_fft1 = fft(y1)
y_fft_freq1 = fftfreq(N1, 1/Fs1)
y_fft_half1 = y_fft1[:N1//2 + 1]
y_fft_freq_half1 = y_fft_freq1[:N1//2 + 1]

amp1 = np.abs(y_fft_half1)

amp_db1 = 20 * np.log10(amp1/amp1.max())

freqs1 = y_fft_freq_half1[-40 < amp_db1]
bandwidth1 = freqs1.max() - freqs1.min()
print(f'Ширина {bandwidth1:.1f} Гц.')


plt.figure(figsize=(12, 8))

# прореженный сигнал
plt.subplot(2, 1, 1)
plt.plot(y_fft_freq_half1, amp1, color='tab:orange', linewidth=1.5)
plt.title('Амплитудный спектр — прореженный сигнал', fontsize=14, fontweight='bold')
plt.xlabel('Частота (Гц)', fontsize=12)
plt.ylabel('Амплитуда', fontsize=12)
plt.grid(True, linestyle='--', alpha=0.6)
plt.xlim(0, Fs1/2)
# plt.ylim(-80, 0)

# оригинальный сигнал
plt.subplot(2, 1, 2)
plt.plot(y_fft_freq_half, amp, color='tab:blue', linewidth=1.5)
plt.title('Амплитудный спектр — оригинальный сигнал', fontsize=14, fontweight='bold')
plt.xlabel('Частота (Гц)', fontsize=12)
plt.ylabel('Амплитуда', fontsize=12)
plt.grid(True, linestyle='--', alpha=0.6)
plt.xlim(0, Fs1/2)
# plt.ylim(-80, 0)

plt.tight_layout()
plt.show()