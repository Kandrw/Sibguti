# -*- coding: utf-8 -*-
"""
Created on Sun Dec 17 15:34:07 2023

@author: Andrey
"""

import matplotlib.pyplot as plt
import random
import numpy as np

import sys
import math

if 1:
    fname_send = "data/data_crc.txt"
    fname_recv = "data/recv_data_crc.txt"
    if(len(sys.argv) > 2):
        fname_recv = sys.argv[1]
        fname_send = sys.argv[2]
    
    file = open(fname_send, "r")
    sdata = file.read()
    file.close()
    file = open(fname_recv, "r")
    rdata = file.read()
    file.close()
    con = 1
    if(len(sys.argv) > 3):
        if(sys.argv[3] == "no_show"):
            con = 0
        else:
            con = 1
    err = 0
    if(len(sdata) != len(rdata)):
        print(f"Длинны отправленных{len(sdata)} и полученных{len(rdata)} данных не совпадают, разница:",len(sdata) - len(rdata))
        sys.exit()
    for i in range(len(sdata)):
        if(sdata[i] != rdata[i]):
            err += 1
            if con:
                print(f"{sdata[i]} - {rdata[i]} - error")
        else:
            if con:
                print(f"{sdata[i]} - {rdata[i]}")
            
    print("Количество ошибок:",err )






















