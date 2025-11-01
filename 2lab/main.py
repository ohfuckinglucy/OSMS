import numpy as np
from matplotlib import pyplot as plt

# Исходные данные
P_BS = 46          # дБм
N_cells = 3        # число секторов
G_BS = 21          # дБи
NF_BS = 2.4        # дБ

P_UE = 24          # дБм
NF_UE = 6          # дБ

f = 1.8            # ГГц
BW_UL = 10 * 10**6 # Гц (10 МГц)
BW_DL = 20 * 10**6 # Гц (20 МГц)

SINR_DL = 2        # дБ
SINR_UL = 4        # дБ

M_pen = 15         # дБ
M_int = 1          # дБ

feeder_loss = 2 + 0.4 + 0.5
mimo_gain = 3

S = 96      # км**2
S_in = 4       # км**2


N_BS = -174 + 10 * np.log10(BW_UL) + NF_BS  # дБм
N_UE = -174 + 10 * np.log10(BW_DL) + NF_UE  # дБм

RxSens_BS = N_BS + SINR_UL  # дБм
RxSens_UE = N_UE + SINR_DL  # дБм

d = np.linspace(10, 5000, 5000)

# FSPM

c = 3e8

fspl = 20*np.log10((4*np.pi*d*f * 1e9)/c)

# UMINLOS

PL_UNI = []

for i in range(0, len(d)):
    pl = 26 * np.log10(f) + 22.7 + 36.7 * np.log10(d[i])
    PL_UNI.append(pl)

# COST231

N_BS_test = -174 + 10 * np.log10(BW_UL) + np.log10(203/290)  # дБм
N_UE_test = -174 + 10 * np.log10(BW_DL) + np.log10(203/290)  # дБм

RxSens_BS_test = N_BS_test + SINR_UL  # дБм
RxSens_UE_test = N_UE_test + SINR_DL  # дБм

MAPL_UL_test = P_UE - feeder_loss + mimo_gain - M_pen - M_int + G_BS - RxSens_BS_test
MAPL_DL_test = P_BS - feeder_loss + mimo_gain + G_BS - M_int - M_pen - RxSens_UE_test

PL_COST = []
A = 46.3
B = 33.9
hBS = 30
hms = 1.5
a = (1.1 * np.log10(f*10**3)) * hms - (1.56 * np.log10(f*10**3) - 0.8)
s = 44.9 - 6.55 * np.log10(hBS)
Lclutter = 0

T = 223

for i in range(0, len(d)):
    d_km = d[i] / 1000.0
    pl = A + B * np.log10(f*10**3) - 13.82 * np.log10(hBS) - a + s * np.log10(d_km) + Lclutter
    PL_COST.append(pl)

# Walfish-Ikegami

PL_WALF = []

w = 4 # средняя ширина улиц
h = 15 # средняя высота зданий (допустим 5ти-этажки)
b = 6 # среднее расстояние между зданиями
ka = 54
kd = 18
kf = -4 + -0.7*(((f*1000)/925) - 1)
phi = 45

# for i in range(0, len(d)):
#     d_km = d[i] / 1000.0
#     pl = 42.6 + 20 * np.log10(f*10**3) + 26 * np.log10(d_km)
#     PL_WALF.append(pl)

L2 = -16.9 - 10 * np.log10(w) + 10 * np.log10(f*1000) + 20 * np.log10(h - hms) + 2.5 + 0.075 * phi
L11 = -18 * np.log10(1+hBS-h)


for i in range(0, len(d)):
    d_km = d[i] / 1000.0
    L0 = 32.44 + 20* np.log10(f*1000) + 20 * np.log10(d_km)
    L1 = L11 + ka + kd*np.log10(d_km) + kf*np.log10(f*1000) - 9*np.log10(b)
    if (L1 + L2) > 0:
        L_NLOS = L0 + L1 + L2
    else:
        L_NLOS = L0
    PL_WALF.append(L_NLOS)

# 1 Выполните расчет бюджета восходящего канала, используя
# входные данные и определите уровень максимально допустимых потерь
# сигнала MAPL_UL.

MAPL_UL = P_UE - feeder_loss + mimo_gain - M_pen - M_int + G_BS - RxSens_BS # 126.6 Дб

# 2 Выполните расчет бюджета нисходящего канала, используя
# входные данные и определите уровень максимально допустимых потерь
# сигнала MAPL_DL.

MAPL_DL = P_BS - feeder_loss + mimo_gain + G_BS - M_int - M_pen - RxSens_UE # 144 Дб

# Построение графика
plt.figure(figsize=(8, 5))
plt.plot(d, PL_UNI, 'b', label='UMINLOS', linewidth=2)
plt.plot(d, PL_COST, 'r', label='COST231', linewidth=2)
plt.plot(d, PL_WALF, 'g', label='Walfish-Ikegami', linewidth=2)
plt.plot(d, fspl, color='orange', label='FSPL', linewidth=2)
plt.axhline(MAPL_UL, color='g', linestyle='--', label='MAPL_UL')
plt.axhline(MAPL_DL, color='m', linestyle='--', label='MAPL_DL')
plt.axhline(MAPL_DL_test, color='c', linestyle='--', label='MAPL_DL (-70 градусов)')
plt.axhline(MAPL_UL_test, color='y', linestyle='--', label='MAPL_UL (-70 градусов)')

plt.xlabel('расстояние, м')
plt.ylabel('потери PL, дБ')
plt.title('зависимость потерь от расстояния')
plt.grid()
plt.legend()
plt.show()

R_UMI = 441

R_COST = 574

R_WALFISH = 315

# Кол-во сайтов

S_site = (1.95 * (R_COST/1000)**2)

N_site = np.ceil(S/S_site)

S_site_in = (np.pi * (R_UMI/1000)**2)

N_site_in = np.ceil(S_in/S_site_in)

print(f'Количество макросайтов COST: {N_site}')
print(f'Количество фемтосот UMINLOS: {N_site_in}')