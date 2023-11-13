import numpy as np
import matplotlib.pyplot as plt
import math


Tx_Power_BS = 46
N = 3
Tx_Power_AT = 24
Ant_Gain_bs = 21
Penetrat_M = 15
IM = 1
f = 1.8  # Ghz

Bw_DL = 20 * 10**6
Bw_UL = 10 *10**6
Noise_Figure_Bs = 2.4
Noise_Figure_At = 6
SINR_DL = 2
SINR_UL = 4
MIMO_Gain = 3
Feeder_Loss = 2

Speed_light = 3 * 10**8 

Thermal_Noise_DL = -174 + 10*np.log10(Bw_DL)
Thermal_Noise_UL = -174 + 10*np.log10(Bw_UL)
Rx_Sens_BS = Thermal_Noise_DL + SINR_DL + Noise_Figure_Bs
Rx_Sens_AT = Thermal_Noise_UL + SINR_UL + Noise_Figure_At

ytik = np.arange(0,200)
#рассчет  уровень максимально допустимых потерь сигнала для DL and UL
MAPL_DL = Tx_Power_BS - Feeder_Loss + Ant_Gain_bs + MIMO_Gain - Penetrat_M - IM - Rx_Sens_AT

MAPL_UL = Tx_Power_AT - Feeder_Loss + Ant_Gain_bs + MIMO_Gain - Penetrat_M - IM - Rx_Sens_BS
m_to_km = 10**-3
def UMiNLOS():              # зависимость величины входных потерь радиосигнала от расстояния между приемником и передатчиком по UMiNLOS и FSPM
    d = np.arange(1,500)
    PLd = 26 * np.log10(f) + 22.7 + 36.7 * np.log10(d)

    FSPM = 20 * np.log10((4 * np.pi * f * 10**9 * d) / Speed_light )
    mapl_dl = [MAPL_DL] * len(d)
    mapl_ul = [MAPL_UL] * len(d)
    plt.figure(1)
    plt.ylabel("Потери сигнала, Дб")
    plt.xlabel("Расстояние между приемником и передатчиком, м")
    plt.plot(d,PLd)
    plt.plot(d,FSPM, "--")
    plt.plot(d, mapl_dl)
    plt.plot(d, mapl_ul, "--", "r")
    plt.yticks(np.arange(min(ytik), max(ytik)+1, 50))

    plt.legend(["UMiNLOS", "FSPM", "MAPL_DL", "MAPL_UL"], loc = 4)
    plt.grid(linewidth = 0.5)
    plt.show()

def Lclutter(key):           # Параметр для расчета модели cost231, пользователь выбирает местность
    if key == "DU":
        lutter = 3
    elif key == "U":
        lutter = 0
    elif key == "SU":
        lutter = - (2*(np.log10(f*10**3/28))**2 + 5.4)
    elif key == "RU":
        lutter = -(4.78 * (np.log10(f*10**3))**2 - 18.33 * np.log10(f*10**3) + 40.94)
    elif key == "ROAD":
        lutter = -(4.78 * (np.log10(f*10**3))**2 - 18.33 * np.log10(f*10**3) + 35.94)
    return lutter


def a(key):# Параметр для расчета модели cost231
    hms = 1
    if key == "DU":
        param_a = 3.2 *np.log10(11.75*hms)**2 - 4.97
    elif key == "SU":
        param_a = (1.1*np.log10(f*10**3) * hms - 1.56 * np.log10(f*10**3) - 0.8)
    return param_a


def s(d,hBS):        # составляющая для расчета модели cost231
    
    if d >= 1:
        param_s = 44.9 - 6.55 * np.log10(f*10**3)
    else:
        param_s =  (47.88 + 13.9 * np.log10(f*10**3) -13.9 * np.log10(hBS)) *  (1/np.log10(50))
    return param_s


def  COST_231():           # зависимость величины входных потерь радиосигнала от расстояния между приемником и передатчиком по UMiNLOS и COST_231
    d = np.arange(1,1000)
    mapl_dl = [MAPL_DL] * len(d)
    mapl_ul = [MAPL_UL] * len(d)
    A = 46.3
    B = 33.9 
    hBS = 50
    PLd = []
    for i in range(len(d)):
        PLd.append(A + B * np.log10(f*10**3) - 13.82 * np.log10(hBS) - a("DU") + s(d[i]*10**-3,hBS) * np.log10(d[i]*10**-3) + Lclutter("DU")) # urban

    FSPM = 20 * np.log10((4 * np.pi * f * 10**9 * d) / Speed_light )
    plt.figure(2)
    plt.ylabel("Потери сигнала, Дб")
    plt.xlabel("Расстояние между приемником и передатчиком, м")
    plt.plot(d,PLd)
    plt.plot(d,FSPM, "--")
    plt.plot(d, mapl_dl)
    plt.plot(d, mapl_ul, "--", "r")
    plt.yticks(np.arange(min(ytik), max(ytik)+1, 50))

    plt.legend(["COST_231", "FSPM", "MAPL_DL", "MAPL_UL"], loc = 4)
    plt.grid(linewidth = 0.5)
    plt.show()

def calc_WallFish(d):
    hBS = 50
    hBuild = 30
    pl_wf = []
    f = 1.8
    L1 = []
    for i in range(1,len(d)+1):    
        path_long=i
        L0=32.44+20*math.log10(1.9)+20*math.log10(i)    
        if ((f <35)&(f>0)):
            qoef=-10+0.354*f    
        elif ((f <55)&(f>=35)):
            qoef=2.5 + 0.075 * f    
        elif ((f <90) & (f>=55)):
            qoef=4.0 - 0.114 * f
        L2=-16.9-10 * math.log10(20)+10*math.log10(1.9)+20*math.log10(hBuild-3)+qoef    
        if (hBS > hBuild):
            L1_1=-18 * math.log10(1+hBS-hBuild)        
            kD=18
        elif (hBS <= hBuild):        
            L1_1=0
            kD=18-15*((hBS-hBuild)/hBuild)    
        if ((hBS <= hBuild) & (path_long>500)):
            kA=54-0.8*(hBS-hBuild)
        elif ((hBS <= hBuild) & (path_long<=500)):        
            kA=54-0.8*(hBS-hBuild) * path_long/0.5
        elif (hBS>hBuild):        
            kA=54
            kF=-4+0.7*(1.9/925 - 1)    
            L1=L1_1+kA+kD*math.log10(path_long)+kF*math.log10(1.9)-9*math.log10(20)
        if(L1+L2>0):        
            Llnos=L0+L1+L2
        elif(L1+L2<=0):        
            Llnos=L0
        pl_wf.append(Llnos)
    return pl_wf

# зависимость величины входных потерь радиосигнала от расстояния между приемником и передатчиком по UMiNLOS и FSPM и Walfish
def COST_231_UMiNLOS_Walfish():
    d = np.arange(1,7000)
    PLd_u = 26 * np.log10(f) + 22.7 + 36.7 * np.log10(d)
    PLd_w = calc_WallFish(d)
    A = 46.3
    B = 33.9 
    hBS = 50
    PLd_c = []
    stem_radius = [0]*len(d)
    for i in range(len(d)):
        PLd_c.append(A + B * np.log10(f*10**3) - 13.82 * np.log10(hBS) - a("SU") + \
                     s(d[i]*10**-3,hBS) * np.log10(d[i]*10**-3) + Lclutter("DU")) # ROAD
    for i in range(1,len(d)-1):
        if PLd_c[i-1] < MAPL_UL and PLd_c[i+1] > MAPL_UL :
            stem_radius[i] = MAPL_UL 
            R_c = i*m_to_km
        if PLd_u[i-1] < MAPL_UL and PLd_u[i+1]>MAPL_UL:
            stem_radius[i] = MAPL_UL
            R_u = i*m_to_km
        if PLd_w[i-1] < MAPL_UL and PLd_w[i+1]>MAPL_UL:
            stem_radius[i] = MAPL_UL
            R_w = i*m_to_km
           
    plt.figure(1)
    plt.ylabel("Потери сигнала, Дб")
    plt.xlabel("Расстояние между приемником и передатчиком, м")
    #plt.stem(d, stem_radius, 'red')
    plt.plot(d,PLd_c, 'purple')
    plt.plot(d,PLd_u, "green")
    plt.plot(d,PLd_w, "orange")
    plt.axhline (y=MAPL_DL, color='blue', linestyle='--')
    plt.axhline (y=MAPL_UL, color='black', linestyle='--')
    plt.legend(["COST_231", "UMiNLOS", "Walfish-Ikegami" ,"MAPL_DL", "MAPL_UL"], bbox_to_anchor =(1.5,0 ),loc = 4)
    plt.grid(linewidth = 0.5)
    plt.show()
    return [R_c, R_u, R_w]


#UMiNLOS()
#COST_231()

Radius = COST_231_UMiNLOS_Walfish()
S_big = 1.95 * Radius[0]**2
S_small = 1.95 * Radius[1]**2
S_w = 1.95 * Radius[2]**2
print("Уровень максимально допустимых потерь сигнала MAPL_UL = ", MAPL_UL, "dB")
print("Уровень максимально допустимых потерь сигнала MAPL_DL = ", MAPL_DL, "dB")
print("Радиус Базовой станции для модели UMiNLOS = ",Radius[1], "км" )
print("Радиус Базовой станции для модели COST_231 = ",Radius[0], "км" )

#print("Радиус Базовой станции для модели Walfish-Ikegami = ",Radius[2], "км" )

print("Площадь одной базовой станции для модели UMiNLOS = ", S_small, "км кв" )

print("Площадь одной базовой станции для модели COST_231 = ", S_big, "км кв" )

#print("Площадь одной базовой станции для модели Walfish-Ikegami = ", S_w, "км кв" )
S_usl_1 = 100
S_usl_2 = 4
S_usl_3 = 50
count_sait_U= S_usl_2/S_small
count_sait_cost= S_usl_1/S_big
count_sait_w= S_usl_3/S_w

print("Необходимое количество базовых станций для модели UMiNLOS:", math.ceil(count_sait_U) )
print("Необходимое количество базовых станций для модели COST_231:", math.ceil(count_sait_cost) )
print("Необходимое количество базовых станций для модели Walfish-Ikegami:", math.ceil(count_sait_w) )



