import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits.mplot3d import Axes3D
from scipy.optimize import curve_fit # Unica nuova importazione necessaria

#=======================================
# Grafico UNIFORME 3D
#=======================================
dati=np.loadtxt("Unif.csv",delimiter=",")
x=dati[:,0]
y=dati[:,1]
z=dati[:,2]

fig = plt.figure(figsize=(8, 8))
ax = fig.add_subplot(111, projection='3d')
ax.plot(x,y,z, label='Traiettoria Discreta')
ax.set_title("RW Discreto")
ax.set_xlabel("x")
ax.set_ylabel("y")
ax.set_zlabel("z")
plt.grid()
plt.legend()
plt.savefig("RW_Discreto_3D.png")
plt.close()

#=======================================
# Grafico ANGOLO SOLIDO 3D
#=======================================
dati2=np.loadtxt("Solid.csv",delimiter=",")
x2=dati2[:,0]
y2=dati2[:,1]
z2=dati2[:,2]

fig = plt.figure(figsize=(8, 8))
ax = fig.add_subplot(111, projection='3d')
ax.plot(x2,y2,z2, label='Traiettoria Continua', color='orangered')
ax.set_title("RW Continuo")
ax.set_xlabel("x")
ax.set_ylabel("y")
ax.set_zlabel("z")
plt.grid()
plt.legend()
plt.show()
plt.savefig("RW_Continuo_3D.png")
plt.close()

#=======================================
# Grafici delle distanze
#=======================================

def funzione_teorica(x, k):
    return k * np.sqrt(x)

dati3=np.loadtxt("distanze.csv",delimiter=",", skiprows=1)

steps = dati3[:,0]
r1    = dati3[:,1] # Distanza Reticolo
err1  = dati3[:,2] # Errore Reticolo
r2    = dati3[:,3] # Distanza Continuo
err2  = dati3[:,4] # Errore Continuo

# RW Discreto

# Calcolo il valore ottimale di k per i dati discreti

popt, pcov = curve_fit(funzione_teorica, steps[1:], r1[1:])
k_discreto = popt[0]


plt.errorbar(steps, r1, yerr=err1, fmt='o', markersize=4, label="Sperimentale", color="blue")


label_fit = f'Fit teorico ($y=k\sqrt{{N}}$)\nk = {k_discreto:.4f}'
plt.plot(steps, funzione_teorica(steps, k_discreto), label=label_fit, color="red")

plt.grid()
plt.legend()
plt.title("Distanza RW Discreto")
plt.xlabel("N passi")
plt.ylabel("Distanza $\sqrt{\langle |r|^2 \\rangle}$")
plt.savefig("DistRWDiscreto.png")
plt.close()

#RW Continuo

# Calcolo il valore ottimale di k per i dati continui
popt, pcov = curve_fit(funzione_teorica, steps[1:], r2[1:])
k_continuo = popt[0]


plt.errorbar(steps, r2, yerr=err2, fmt='o', markersize=4, label="Sperimentale", color="green")

#curva teorica con il nuovo k
label_fit_cont = f'Fit teorico ($y=k\sqrt{{N}}$)\nk = {k_continuo:.4f}'
plt.plot(steps, funzione_teorica(steps, k_continuo), label=label_fit_cont, color="red")

plt.grid()
plt.legend()
plt.title("Distanza RW Continuo")
plt.xlabel("N passi")
plt.ylabel("Distanza $\sqrt{\langle |r|^2 \\rangle}$")
plt.savefig("DistRWContinuo.png")
plt.show()
plt.close()

print(f"Costante k trovata per il RW Discreto: {k_discreto:.4f}")
print(f"Costante k trovata per il RW Continuo: {k_continuo:.4f}")