# -*- coding: utf-8 -*-
"""
Created on Sun Dec 17 00:16:39 2023

@author: Andrey
"""


import matplotlib.pyplot as plt
import random
import numpy as np

import sys
import math



if 1:
    fname = "data/recv_data_crc.txt"
    if(len(sys.argv) > 1):
        fname = sys.argv[1]
    file = open(fname, "r")
    
    data = file.read()
    file.close()
    op = len(data) / 8

    bytes_data = []
    for i in range(0, len(data), 8):
        
        data1 = data[i:i + 8]
    
        symbol = chr(int(data1, 2))
        bytes_data.append(symbol)
    fname = "data/recv_data_crc.bin"
    if(len(sys.argv) > 2):
        fname = sys.argv[2]
    file = open(fname, "w",  encoding="utf-8")
    str_w = "".join(bytes_data)
    file.write(str_w)
    file.close()




