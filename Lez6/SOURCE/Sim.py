import matplotlib.pyplot as plt
import numpy as np
from itertools import islice

start = 0  
stop  = 16 

with open("../OUTPUT/Risultati.dat", 'r') as f:
    dati = np.loadtxt(islice(f,start,stop), delimiter=",")
T_=dati[:,0]
U_=dati[:,1]
errU=dati[:,2]
Cv_=dati[:,5]
errCv=dati[:,6]
X_=dati[:,7]
errX=dati[:,8]

start = 16   
stop= 32
with open("../OUTPUT/Risultati.dat", 'r') as f:
    dati2 = np.loadtxt(islice(f, start,stop), delimiter=",")
T_g=dati2[:,0]
U_g=dati2[:,1]
errUg=dati2[:,2]
Cv_g=dati2[:,5]
errCvg=dati2[:,6]
X_g=dati2[:,7]
errXg=dati2[:,8]

start = 32   
stop= 48
with open("../OUTPUT/Risultati.dat", 'r') as f:
    dati2 = np.loadtxt(islice(f, start,stop), delimiter=",")

M_=dati2[:,3]
errM=dati2[:,4]

start = 48  
stop=65
with open("../OUTPUT/Risultati.dat", 'r') as f:
    dati2 = np.loadtxt(islice(f, start,stop), delimiter=",")

M_g=dati2[:,3]
errMg=dati2[:,4]


points=100
T = np.linspace(0.2,3.0,num=points)
beta = 1/T
J = 1.0
Ns = 50
th = np.tanh(J/T)
thN= th**Ns
ch = 1/th
e = -J*( th + ch*thN )/( 1 + thN )

#/////////////////////////////////////////////////////      Energia Interna

plt.plot(T, e,label="Curva Teorica",color="red")
plt.errorbar(T_,U_,yerr=errU,label="Valori Sperimentali",color="blue",fmt='o',capsize=5,markersize=4)
plt.title('Internal Energy Metropolis')
plt.xlabel('T')
plt.ylabel('U/N')
plt.legend()
plt.grid()
plt.savefig("../OUTPUT/GRAFICI/Internal Energy Metro.png")
plt.close()

plt.plot(T, e,label="Curva Teorica",color="red")
plt.errorbar(T_g,U_g,yerr=errUg,label="Valori Sperimentali",color="blue",fmt='o',capsize=5,markersize=4)
plt.title('Internal Energy Gibbs')
plt.xlabel('T')
plt.ylabel('U/N')
plt.legend()
plt.grid()
plt.savefig("../OUTPUT/GRAFICI/Internal Energy Gibbs.png")
plt.close()

#/////////////////////////////////////////////#           Calore Specifico

heat=((beta*J)**2)*(((1+thN+(Ns-1)*(th**2)+(Ns-1)*(ch**2)*thN)/(1+thN))-Ns*((th+ch*thN)/(1+thN))**2)
plt.plot(T, heat,label="Curva Teorica",color="red")
plt.errorbar(T_,Cv_,yerr=errCv,label="Valori Sperimentali",color="blue",fmt='o',capsize=5,markersize=4)
plt.title('Heat capacity Metropolis')
plt.xlabel('T')
plt.ylabel('C')
plt.legend()
plt.grid()
plt.savefig("../OUTPUT/GRAFICI/Heat Capacity Metro.png")
plt.close()

plt.plot(T, heat,label="Curva Teorica",color="red")
plt.errorbar(T_g,Cv_g,yerr=errCvg,label="Valori Sperimentali",color="blue",fmt='o',capsize=5,markersize=4)
plt.title('Heat Capacity Gibbs')
plt.xlabel('T')
plt.ylabel('C')
plt.legend()
plt.grid()
plt.savefig("../OUTPUT/GRAFICI/Heat Capacity Gibbs.png")
plt.close()

#////////////////////////////////////////////////////////     Magnetizzazione

h=0.02 #external field
b = 1/T

l1 = np.exp(b*J)*np.cosh(b*h)+np.sqrt(np.exp(2*b*J)*np.cosh(b*h)*np.cosh(b*h)-2*np.sinh(2*b*J))
l2 = np.exp(b*J)*np.cosh(b*h)-np.sqrt(np.exp(2*b*J)*np.cosh(b*h)*np.cosh(b*h)-2*np.sinh(2*b*J))
Z = l1**Ns + l2**Ns
M = (np.exp(b*J)*np.sinh(b*h)*((l1**(Ns-1))*(1+np.exp(b*J)*np.cosh(b*h)/np.sqrt(np.exp(2*b*J)*np.cosh(b*h)*np.cosh(b*h)-2*np.sinh(2*b*J))) 
        + (l2**(Ns-1))*(1-np.exp(b*J)*np.cosh(b*h)/np.sqrt(np.exp(2*b*J)*np.cosh(b*h)*np.cosh(b*h)-2*np.sinh(2*b*J)))))/(Z)
plt.plot(T, M,label="Curva Teorica",color="red")
plt.errorbar(T_, M_,yerr=errM,label="Valori Sperimentali",color="blue",fmt='o',capsize=5,markersize=4)
plt.title('Magnetization M with h = 0.02 Metropolis')
plt.xlabel('T')
plt.grid()
plt.legend()
plt.ylabel('$M$')
plt.savefig("../OUTPUT/GRAFICI/Magnetization Metro.png")
plt.close()

plt.plot(T, M,label="Curva Teorica",color="red")
plt.errorbar(T_g, M_g,yerr=errMg,label="Valori Sperimentali",color="blue",fmt='o',capsize=5,markersize=4)
plt.title('Magnetization M with h = 0.02 Gibbs')
plt.xlabel('T')
plt.grid()
plt.legend()
plt.ylabel('$M$')
plt.savefig("../OUTPUT/GRAFICI/Magnetization Gibbs.png")
plt.close()

#//////////////////////////////////////////////////////////////       Suscettibilità

X = beta*np.exp(2*beta*J)*(1-thN)/(1+thN)
plt.plot(T, X,label="Curva Teorica",color="red")
plt.errorbar(T_, X_,yerr=errX,label="Valori Sperimentali",color="blue",fmt='o',capsize=5,markersize=4)
plt.title('Susceptibility Metropolis')
plt.xlabel('T')
plt.legend()
plt.grid()
plt.ylabel('$\chi$')
plt.savefig("../OUTPUT/GRAFICI/Susceptibility Metro.png")
plt.close()

plt.plot(T, X,label="Curva Teorica",color="red")
plt.errorbar(T_g, X_g,yerr=errXg,label="Valori Sperimentali",color="blue",fmt='o',capsize=5,markersize=4)
plt.title('Susceptibility Gibbs')
plt.xlabel('T')
plt.legend()
plt.grid()
plt.ylabel('$\chi$')
plt.savefig("../OUTPUT/GRAFICI/Susceptibility Gibbs.png")
plt.close()