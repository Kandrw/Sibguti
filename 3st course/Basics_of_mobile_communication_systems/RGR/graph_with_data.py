import matplotlib.pyplot as plt

import sys

def char_to_bit(char):
    return ''.join(format(ord(i), '08b') for i in char)



if(len(sys.argv) > 2):

    print("file data: ", sys.argv[1])
    file = open(sys.argv[1], "r")

    data = file.read()
    file.close()
    print(type(data))

    print(data)
    data = list(data)
    data = list(map(int, data))
    plt.figure(1, figsize=(10,10))
    if(len(sys.argv) > 3):
        plt.title(sys.argv[3])
    plt.plot(data)
    plt.savefig(sys.argv[2])


