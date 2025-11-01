import numpy as np
from scipy.io import wavfile
from matplotlib import pyplot as plt

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

    return signal_quant_amp

Fs = 44100
tau1 = 0.5
tau2 = 1
tau3 = 2

t1 = np.linspace(0, tau1, int(Fs*tau1))
t2 = np.linspace(0, tau2, int(Fs*tau2))
t3 = np.linspace(0, tau3, int(Fs*tau3))


G5 = np.sin(2*np.pi*783.991*t2)
Gb5 = np.sin(2*np.pi*739.989*t1)
Gb5l = np.sin(2*np.pi*739.989*t2)

E5 = np.sin(2*np.pi*659.255*t1)
E5l = np.sin(2*np.pi*659.255*t2)

D5 = np.sin(2*np.pi*587.33*t1)
C5 = np.sin(2*np.pi*523.251*t2)
C5s = np.sin(2*np.pi*523.251*t1)
B4 = np.sin(2*np.pi*493.883*t1)
B4ll = np.sin(2*np.pi*493.883*t3)


A4 = np.sin(2*np.pi*440*t2)
A4s = np.sin(2*np.pi*440*t1)

Eb5 = np.sin(2*np.pi*622.254*t2)
G4 = np.sin(2*np.pi*391.995*t3)

notes = [G5, Gb5, E5, D5, C5, B4, D5 , E5, Gb5l, E5, D5, C5s, B4ll, E5l, D5, C5s, B4, A4, B4, C5s, E5, Eb5, C5s, B4, A4s, G4]

for i in range(0, len(notes)):
    notes[i] = sround(notes[i] * 3, 1)
    notes[i] = notes[i] / 10


melody = np.concatenate(notes)

notes_int16 = (melody * 32767).astype(np.int16)
wavfile.write('melody.wav', Fs, notes_int16)