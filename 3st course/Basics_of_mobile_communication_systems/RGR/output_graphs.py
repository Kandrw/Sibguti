# -*- coding: utf-8 -*-
"""
Created on Sun Dec 17 16:25:01 2023

@author: Andrey
"""


import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import random
import numpy as np

import sys
import math
import os


dir1 = "img"
if(len(sys.argv) > 1):
    dir1 = sys.argv[1]
    
files = os.listdir(dir1)




for i in range(len(files)):
    img = mpimg.imread(dir1 + "/" + files[i])
    plt.figure(i + 1, figsize=(20, 20))
    plt.axis('off')
    plt.imshow(img)
    #plt.show()
plt.figure(i, figsize=(20, 20))
plt.axis('off')
img = mpimg.imread("spectre_3x.png")
plt.imshow(img)
plt.show()














