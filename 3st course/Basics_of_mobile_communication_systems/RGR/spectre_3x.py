# -*- coding: utf-8 -*-
"""
Created on Mon Dec 18 21:34:25 2023

@author: Andrey
"""


import matplotlib.pyplot as plt
import sys
from scipy.fft import fft



file_inp = ["data_N/signal.txt", "data_Nd2/signal.txt", "data_Nx2/signal.txt"]
file_out = ["data_N/signal_noise.txt", "data_Nd2/signal_noise.txt", "data_Nx2/signal_noise.txt"]
N = 10

if(len(sys.argv) > 7):
    fanme_inp = [ sys.argv[1], sys.argv[2], sys.argv[3] ]
    fanme_out = [ sys.argv[4], sys.argv[5], sys.argv[6] ]
    N = int(sys.argv[7])

N_arrs = [ N, N/2, N * 2]

datas = []

for i in range(len(file_inp)):
    file = open(file_inp[i], "r")
    datas.append(file.read())
    file.close()
for i in range(len(datas)):
    datas[i] = list(datas[i])
for i in range(len(file_out)):
    file = open(file_out[i], "r")
    datas.append(file.read().split(" "))
    file.close()

for i in range(len(datas)):
    datas[i] = list(map(float, datas[i]))  
    datas[i] = fft(datas[i])


plt.figure(1, figsize=(20, 10))
plt.subplot(2, 2, 1)
plt.title("Спектр исходного сигнала")
for i in range(3):
    
    plt.plot(datas[i].real, label = str(N_arrs[i]))
plt.legend()
plt.subplot(2, 2, 2)
plt.title("Спектр зашумленного сигнала")
for i in range(3, 6):
    
    plt.plot(datas[i].real, label = str(N_arrs[i - 3]))
plt.legend()

if(len(sys.argv) > 8):
    plt.savefig(sys.argv[8])

