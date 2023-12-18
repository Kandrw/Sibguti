
import matplotlib.pyplot as plt
import sys
from scipy.fft import fft


fname_inp = "data/signal.txt"
fname_out = "data/signal_noise.txt"



if(len(sys.argv) > 2):
    fanme_inp = sys.argv[1]
    fanme_out = sys.argv[2]


file = open(fname_inp, "r")
sig_inp = file.read()
sig_inp = list(sig_inp)
file.close()
file = open(fname_out, "r")
sig_out = file.read()
sig_out = sig_out.split(" ")
file.close()

sig_inp = list(map(float, sig_inp))   
sig_out = list(map(float, sig_out))   


data1 = fft(sig_inp)
data2 = fft(sig_out)
plt.figure(1, figsize=(20, 10))

plt.subplot(2, 1, 1)
plt.title("Спектр исходного сигнала")
plt.plot(data1.real)
plt.subplot(2, 1, 2)
plt.title("Спектр зашумленного сигнала")
plt.plot(data2.real, "r")
if(len(sys.argv) > 3):
    plt.savefig(sys.argv[3])


