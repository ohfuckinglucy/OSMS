import matplotlib.pyplot as plt
import numpy as np

## 13 Оцените влияние разрядности АЦП на спектр сигнала.

def MSEcalc(signal, signal_quant):
    total = 0
    for i in range(0, len(signal)):
        total = total + np.abs(signal[i] - signal_quant[i])

    return (1/len(signal))*total

def sround(signal, bits):
    signal = np.clip(signal, -1, 1)
    levels = 2**bits-1
    signal_quant_lev = np.zeros(len(signal))
    signal_quant_amp = np.zeros(len(signal))
    norm = np.zeros(len(signal))

    min = signal.min()
    max = signal.max()

    norm = (signal - min) / (max - min)

    signal_quant_lev = np.round(norm * levels)

    signal_quant_amp = ((signal_quant_lev / levels) * (max - min)) + min

    mse = MSEcalc(signal, signal_quant_amp)


    print(f'Ошибка квантования при {bits} битах: {mse}')


    return signal_quant_lev

f = 7
t = np.linspace(0, 1, 1000)

s_t = np.cos(4*np.pi * f * t) + np.cos(6*np.pi*f*t)

plt.plot(t, s_t)
plt.title("исходные сигнал")
plt.xlabel("Время")
plt.ylabel("Амплитуда")

plt.tight_layout()
plt.show()

s_t_quant6 = sround(s_t, 6)
plt.subplot(4, 2, 1)
plt.plot(t, s_t_quant6)
plt.title("Квантованный сигнал (6 бит)")
plt.xlabel("Время")
plt.ylabel("Уровние квантования")

s_t_quant5 = sround(s_t, 5)
plt.subplot(4, 2, 2)
plt.plot(t, s_t_quant5)
plt.title("Квантованный сигнал (5 бит)")
plt.xlabel("Время")
plt.ylabel("Уровние квантования")

s_t_quant4 = sround(s_t, 4)
plt.subplot(4, 2, 3)
plt.plot(t, s_t_quant4)
plt.title("Квантованный сигнал (4 бит)")
plt.xlabel("Время")
plt.ylabel("Уровние квантования")

s_t_quant3 = sround(s_t, 3)
plt.subplot(4, 2, 4)
plt.plot(t, s_t_quant3)
plt.title("Квантованный сигнал (3 бит)")
plt.xlabel("Время")
plt.ylabel("Уровние квантования")


plt.tight_layout()
plt.show()