import matplotlib.pyplot as plt
import random
import numpy as np

import sys




if len(sys.argv) < 2:
    file = open("data/signal.txt", "r")
    
    data = file.read()
    adata = data
    abr = ""
    for i in range(0, len(adata), 30):
        abr += adata[i]
    data = np.array(list( map(int, list(data))))
    
    file.close()
    noise = np.random.normal(0.0, 0.2, len(data))
    data2 = data + noise
    file2 = open("data/signal_noise.txt", "w")
    dfg = list(data2)
    dfg2 = list(map(float, dfg))
    dfg2 = list(map(str, dfg))
    
    dfg3 = " ".join(dfg2)

    file2.write(dfg3)
    file2.close()
    plt.figure(1, figsize=(10,10))
    plt.title("Сигнал + шум")
    plt.plot(data2, "g")
    
    #plt.savefig(sys.argv[2])
elif (len(sys.argv) > 5):
    print("file data: ", sys.argv[1])
    file = open(sys.argv[1], "r")
    data = file.read()
    file.close()
    data = np.array(list( map(int, list(data))))
    
    noise = np.random.normal(float(sys.argv[2]), float(sys.argv[3]), len(data))
    data = data + noise
    
    file2 = open(sys.argv[4], "w")
    dfg = list(data)
    dfg2 = list(map(float, dfg))
    dfg2 = list(map(str, dfg))
    
    dfg3 = " ".join(dfg2)

    file2.write(dfg3)
    file2.close()
    
    plt.figure(1, figsize=(10,10))
    plt.title("Сигнал + шум")
    plt.plot(data, "g")
    
    plt.savefig(sys.argv[5])