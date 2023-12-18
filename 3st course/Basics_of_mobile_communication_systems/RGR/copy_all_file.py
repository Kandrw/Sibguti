# -*- coding: utf-8 -*-
"""
Created on Mon Dec 18 21:04:07 2023

@author: Andrey
"""

import os


import shutil
import sys
 
if(len(sys.argv) > 3):
    src_dir = sys.argv[1]
    
    dest_dir = sys.argv[2]
     
    
    files = os.listdir(src_dir)
     
    shutil.copytree(src_dir, dest_dir)

