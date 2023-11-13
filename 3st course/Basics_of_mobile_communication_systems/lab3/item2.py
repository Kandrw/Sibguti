
import numpy as np
import matplotlib.pyplot as plt
import math

# Создание временной оси
t = np.arange(0, 100) / 100

# Заданные частоты
f1, f2, f3 = 9, 13, 19

# Формирование сигналов s1, s2 и s3
s1 = np.cos(2 * np.pi * f1 * t)
s2 = np.cos(2 * np.pi * f2 * t)
s3 = np.cos(2 * np.pi * f3 * t)

def correlation(a, b):
    sum_val = 0
    for i in range(len(a)):
        sum_val += a[i] * b[i]
    return sum_val

def normal_correlation(a, b):
    sum_norm = 0
    sumA_squared = 0
    sumB_squared = 0
    
    for i in range(len(a)):
        sum_norm += a[i] * b[i]
        sumA_squared += a[i] ** 2
        sumB_squared += b[i] ** 2
    
    normalization = math.sqrt(sumA_squared * sumB_squared)
    return sum_norm / normalization

# Формирование сигналов a и b
a = 4 * s1 + 3 * s2 + 2 * s3
b = s1 + s3

corr_s1_a = correlation(s1, a)
corr_s1_b = correlation(s1, b)

corr_s2_a = correlation(s2, a)
corr_s2_b = correlation(s2, b)

corr_s3_a = correlation(s3, a)
corr_s3_b = correlation(s3, b)

norm_corr_s1_a = normal_correlation(s1, a)
norm_corr_s1_b = normal_correlation(s1, b)

norm_corr_s2_a = normal_correlation(s2, a)
norm_corr_s2_b = normal_correlation(s2, b)

norm_corr_s3_a = normal_correlation(s3, a)
norm_corr_s3_b = normal_correlation(s3, b)

# Вывод результатов корреляции и нормализованной корреляции
print("Корреляция s1 и a:", corr_s1_a)
print("Нормализованная корреляция s1 и a:", norm_corr_s1_a)

print("Корреляция s1 и b:", corr_s1_b)
print("Нормализованная корреляция s1 и b:", norm_corr_s1_b)

print("Корреляция s2 и a:", corr_s2_a)
print("Нормализованная корреляция s2 и a:", norm_corr_s2_a)

print("Корреляция s2 и b:", corr_s2_b)
print("Нормализованная корреляция s2 и b:", norm_corr_s2_b)

print("Корреляция s3 и a:", corr_s3_a)
print("Нормализованная корреляция s3 и a:", norm_corr_s3_a)

print("Корреляция s3 и b:", corr_s3_b)
print("Нормализованная корреляция s3 и b:", norm_corr_s3_b)

a1 = np.array([0.3, 0.2, -0.1, 4.2, -2, 1.5, 0])
b1 = np.array([0.3, 4, -2.2, 1.6, 0.1, 0.1, 0.2])

# Вычисление взаимной корреляции
cross_correlation = correlation(a1, b1)
correlation_array = []
correlation_array.append(cross_correlation)
plt.figure(1, figsize=(10, 10))
# График массива a
plt.subplot(2, 2, 1)
plt.plot(a1)
plt.title("График массива a1")

# График массива b
plt.subplot(2, 2, 2)
plt.plot(b1, 'r')
plt.title("График массива b1")


# Найдем индекс максимального значения корреляции
max_corr_shift = np.argmax(cross_correlation) - len(a1) + 1
print("Максимальная корреляция достигается при сдвиге:", max_corr_shift)

# Сдвинем последовательность b1 на найденный сдвиг
shifted_b1 = b1
for i in range(len(b1)):
    shifted_b1 = np.roll(shifted_b1, max_corr_shift)
    cross_correlation = correlation(a1, shifted_b1)
    correlation_array.append(cross_correlation)

plt.subplot(2, 2, 3)
plt.plot(correlation_array, "g")
plt.title("Взаимная корреляция")
plt.xlabel("Сдвиг")

# График массива сдвинутой b1

plt.subplot(2, 2, 4)
plt.plot(shifted_b1, 'y')
plt.title("График массива сдвинутой b1")

plt.tight_layout()

plt.show()
