# -*- coding: utf-8 -*-
"""
Created on Thu Oct 12 08:37:32 2023

@author: Andrey
"""

import numpy as np
import matplotlib.pyplot as plt
from scipy.fftpack import fft


f = 8
t = np.linspace(0, 1, 1000)  # Временной интервал от 0 до 1 секунды с 1000 точками
y = np.cos(2 * np.pi * f * t) + np.cos(8 * np.pi * f * t) 

Fs = 2 * f  # Минимальная необходимая частота дискретизации (согласно теореме Котельникова)
duration = 1  # Длительность сигнала в секундах
num_samples = int(Fs * duration)  # Число отсчетов
t2 = np.linspace(0, duration, num_samples)
y2 = np.cos(2 * np.pi * f * t2) + np.cos(8 * np.pi * f * t2)

def find_max_frequency(signal, sample_rate):
    signal_fft = np.fft.fft(signal)
    magnitude = np.abs(signal_fft)
    frequency = np.fft.fftfreq(len(signal), 1/sample_rate)
    max_frequency_index = np.argmax(magnitude)
    max_frequency = frequency[max_frequency_index]
    return max_frequency

print("TEST: max f = ", find_max_frequency(y, Fs))

#преобразование Фурье
fft_result = fft(y)


fft_freqs = np.fft.fftfreq(len(fft_result))
#fft_freqs = np.fft.fftfreq(

magnitude = np.abs(fft_result)

# Находим максимальную частоту
max_frequency_index = np.argmax(magnitude)
max_frequency = fft_result[max_frequency_index]
#print(min(fft_result))
#1
# Визуализируем сигнал
plt.figure(figsize=(8, 6))
plt.plot(t, y)
plt.title('График сигнала y(t) = 6*sin(2*pi*9*t + pi/5)')
plt.xlabel('Время (секунды)')
plt.ylabel('Амплитуда')
plt.grid(True)
plt.show()

#2
# Визуализируем амплитудный спектр
plt.figure(figsize=(8, 6))
plt.plot(fft_freqs, magnitude)
plt.title('Амплитудный спектр')
plt.xlabel('Частота (Гц)')
plt.ylabel('Амплитуда')
plt.grid(True)
plt.show()

print("Максимальная частота в спектре: {:.2f} Гц".format(np.abs(max_frequency)))

#3
Fmax = np.abs(max_frequency)  # Максимальная частота в спектре

# Минимальная необходимая частота дискретизации (теорема Котельникова)
Fs_min = 2 * Fmax

print("Минимальная необходимая частота дискретизации: {:.2f} Гц".format(Fs))

plt.plot(t2, y2)
plt.title('Оцифрованный сигнал')
plt.xlabel('Время (секунды)')
plt.ylabel('Амплитуда')
plt.grid(True)
plt.show()


digital_signal = y

dft_result = np.fft.fft(digital_signal)

# Оцениваем ширину спектра
Fs_min = 2 * np.abs(np.max(np.fft.fftfreq(len(dft_result))))
spectral_width = Fs_min

# Оцениваем объем памяти, требуемый для хранения массива
memory_size_bytes = dft_result.nbytes

print("Ширина спектра: {:.2f} Гц".format(spectral_width))
print("Объем памяти для хранения массива DFT: {} байт".format(memory_size_bytes))

t_interpolated = np.linspace(0, duration, 10 * num_samples)  # Увеличиваем количество точек для интерполяции
y_interpolated = np.interp(t_interpolated, t2, y2)
plt.figure(figsize=(12, 6))
plt.subplot(2, 1, 1)
plt.plot(t, y)
plt.title('Оригинальный сигнал')
plt.xlabel('Время (секунды)')
plt.ylabel('Амплитуда')
plt.grid(True)

plt.subplot(2, 1, 2)
plt.plot(t_interpolated, y_interpolated)
plt.title('Восстановленный сигнал после оцифровки')
plt.xlabel('Время (секунды)')
plt.ylabel('Амплитуда')
plt.grid(True)

plt.tight_layout()
plt.show()