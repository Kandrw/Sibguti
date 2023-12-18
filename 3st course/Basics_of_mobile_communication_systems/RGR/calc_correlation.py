# -*- coding: utf-8 -*-
"""
Created on Sat Dec 16 19:10:32 2023

@author: Andrey
"""

import matplotlib.pyplot as plt
import random
import numpy as np

import sys
import math

def correlation(data, seq, step):
    sum_c = 0
    for i in range(len(seq)):
        sum_c += data[i + step] * seq[i]
    
    
    return sum_c
def correlation2(data, seq, step):
    sum_c = 0
    for i in range(len(seq)):
        sum_c += data[i + step] * seq[i]
    
    a = data[step : step + len(seq)]
    #return sum_c / math.sqrt( sum(seq) * sum(data[step : step + len(seq)]) )
    return sum_c / math.sqrt( sum(seq * seq) * sum(a * a ))
    
def cmp_sample(a, ort):
    if(a < 1 + ort and a > 1 - ort):
        return 1
    if(a < 0 + ort and a > 0 - ort):
        return 0

def cmp_sample_n1(a, ort, n, P):
    sum_a = sum(a)
    #sum_ort = sum(ort)
    if(sum_a > P - (ort * n)):
        return 1
    return 0
def cmp_sample_n2(a, ort, n, P):
    sum_c = 0
    asd = []
    for i in range(len(a)):
        if(a[i] > 0.1 - ort):
            sum_c += 1# - (i / 100)
        else:
            sum_c -= 1
    debug_str = str(a)
    file = open("deb.txt", "a"); file.write(debug_str); file.close()
    if(sum_c > P):
        return 1
    return 0
def cmp_sample_n(a, ort, n, P):
    sum_c = 0
    asd = ""
    for i in range(len(a)):
        if(a[i] > 0.1):
            sum_c += 1# - (i / 100)
            asd += "1"
        else:
            sum_c -= 1
            asd += "0"
    #debug_str = str()
    file = open("deb.txt", "a"); file.write(asd); file.close()
    if(sum_c > len(a) / 2 - 1):
        return 1
    return 0

def get_data_pos(data, seq):
    it = 0
    
    while(1):
        con = 1
        step = 0
        for i in range(it, len(seq)):
            step += 1
            if(seq[i] != data[i]):
                con = 0
        if(con == 1):
            break;
        
        it += 1
    #print("step = ",step)
    return it + step + 1
def get_data_end_pos(data, seq):
    it = len(seq)
    
    while(1):
        con = 1
        i2 = len(data) - 1
        for i in range(it-1, -1, -1):
            if(seq[i] != data[i2]):
                con = 0
            i2 -= 1
        
        if(con == 1):
            break;
        
        it -= 1
    return it
if 1:
    N = 10
    
    fname = "data/signal_noise.txt"
    if(len(sys.argv) > 1):
        fname = sys.argv[1]
    file = open(fname, "r")
    data = file.read()
    file.close()
    data = data.split(" ")
    data = np.array(list( map(float, list(data))))
    
    fnseq = "data/seq_gold_start.txt"
    if(len(sys.argv) > 2):
        fnseq = sys.argv[2]
    file = open(fnseq, "r")
    seq = file.read()
    file.close()
    fnseq_e = "data/seq_gold_end.txt"
    if(len(sys.argv) > 3):
        fnseq_e = sys.argv[3]
    file = open(fnseq_e, "r")
    seq_end = file.read()
    file.close()
    seq_end_str = seq_end
    seq = list(seq)
    seq = list(map(float, seq))
    seq = np.array(seq)
    seq_or = seq
    seq2 = []
    N = 10
    if(len(sys.argv) > 4):
        N = int(sys.argv[4])
        
    print("N = ", N)
    for i in range(len(seq)):
        for i2 in range(N):
            
            seq2.append(seq[i])
    seq = np.array(seq2)
    
    seq_end = list(seq_end)
    seq_end = list(map(float, seq_end))
    seq_end = np.array(seq_end)
    seq_end_or = seq_end
    seq2 = []
    for i in range(len(seq_end)):
        for i2 in range(N):
            
            seq2.append(seq_end[i])
    seq_end = np.array(seq2)
    
    
    data2 = []
    data3 = []
    cor = 0
    index = -1
    index2 = -1
    std = correlation2(seq, seq, 0)
    for i in range(len(data)):
        if i >= len(data) - len(seq):
            break
        cor = correlation(data, seq, i)
        cor2 = correlation2(data, seq, i)
        
        if(cor >= 15  and index == -1):
            index = i
        if(cor2 >= 0.9  and index2 == -1):
            index2 = i
        data2.append(cor)
        data3.append(cor2)
    
    plt.figure(1, figsize=(20, 10))
    plt.suptitle("Синхро сигнал в начале")
    plt.subplot(2, 2, 1)
    plt.title("Корреляция")
    plt.plot(data2)
    plt.subplot(2, 2, 2)
    plt.title("Нормализованная корреляция")
    plt.plot(data3, "r")
    #if(len(sys.argv) > 5):
    #    plt.savefig(sys.argv[5])
    if(len(sys.argv) > 5):
        plt.savefig(sys.argv[5])
    index_end1 = -1
    index_end2 = -1
    data_end = []
    data_end_n = []
    for i in range(index2, len(data)):
        if i >= len(data) - len(seq_end):
            break
        cor = correlation(data, seq_end, i)
        cor2 = correlation2(data, seq_end, i)
        
        if(cor >= 25  and index_end1 == -1):
            index_end1 = i
        if(cor2 >= 0.9  and index_end2 == -1):
            index_end2 = i
        data_end.append(cor)
        data_end_n.append(cor2)
    
    
    plt.figure(2, figsize=(20, 10))
    plt.suptitle("Синхро сигнал в конце")
    plt.subplot(2, 2, 1)
    plt.title("Корреляция")
    plt.plot(data_end)
    plt.subplot(2, 2, 2)
    plt.title("Нормализованная корреляция")
    plt.plot(data_end_n, "r")
    if(len(sys.argv) > 6):
        plt.savefig(sys.argv[6])
        
    print(f"Позиция(приблизительно) сихро последовательности в начале {index2}, в конце {index_end2}")
    #sys.exit()
    P = N / 2
    
    
    
    decode_data = []
    sum_sample_n = []
    #for i in range(index2, index_end2, N):
    #for i in range(index2, len(data), 10):
    #    decode_data.append(cmp_sample(data[i], 0.1))
    
    for i in range(index2, index_end2, N):
    #for i in range(index2, len(data), N):
        AA = len(data[i:i+N])
        rt = cmp_sample_n(data[i:i+N], 0.01, N, P)
        file = open("deb.txt", "a"); file.write(" = " + str(rt) + "\n"); file.close()
        #print(rt)
        #if(i > index2 + 200):
            #sys.exit()
        decode_data.append(rt)
        sum_sample_n.append(sum(data[i:i+N]))
    
    plt.figure(3, figsize=(20, 20))
    plt.subplot(2, 2, 1)
    plt.title("Декодированные данные")
    plt.plot(decode_data, "y")
    if(len(sum_sample_n) > 0):
        plt.subplot(2, 2, 2)
        plt.title(f"Сумма по {N} отчетов")
        plt.plot(sum_sample_n, "r")
    #sys.exit()
    if(len(sys.argv) > 7):
        plt.savefig(sys.argv[7])
    pos_data = get_data_pos(decode_data, seq_or)
    pos_end_data = get_data_end_pos(decode_data, seq_or)
    
    print("Позиция начала данных:", pos_data)
    for i in range(pos_data, len(decode_data)):
        print(decode_data[i], end="")
    print()
    print("Позиция конца данных:", pos_end_data)
    fname = "data/recv_data_crc.txt"
    if(len(sys.argv) > 8):
        fname = sys.argv[8]
    decode_data = decode_data[pos_data:]
    decode_data = list(map(str, decode_data))
    
    dedata_str = "".join(decode_data)
    file = open(fname, "w")
    file.write(dedata_str)
    
    file.close()
    
    
    
    
    
    
    
    
    
    
    
    
    

