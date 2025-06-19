import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from scipy.stats import chi2

#presa dati
dati = np.loadtxt("dati.csv",delimiter=",",skiprows=1)
medie=dati[:,0]
err=dati[:,1]
var=dati[:,2]
err2=dati[:,3]
chi3=dati[:,4]

#media
plt.plot(range(0,100),[0]*100,color='r',label="Valore Atteso")
plt.errorbar(range(1,len(medie)+1),medie-0.5,color='b',yerr=err, label="Simulazione")
plt.xlabel("N")
plt.ylabel("<r>-1/2")
plt.grid()
plt.legend()
plt.title("Medie per D")
plt.savefig("Medie.png")
plt.close()

#varianza
plt.plot(range(0,100),[0]*100,color='r',label="Valore Atteso")
plt.errorbar(range(1,len(var)+1),var-1/12,color='b',yerr=err2,label="Simulazione")
plt.xlabel("N")
plt.ylabel("<(r-0.5)^2>-1/12")
plt.grid()
plt.legend()
plt.title("Varianze per N blocchi")
plt.savefig("Varianze.png")
plt.close()

#chiquadro
x=np.linspace(0,160,400)
pdf_chi2=chi2.pdf(x,100)
plt.hist(chi3,range=(0,160),color='blue',bins=40,label="Simulazione",density=True)
plt.plot(x,pdf_chi2,label="Teorica",color="red")
plt.xlabel("χ²")
plt.ylabel("Densità")
plt.grid()
plt.legend()
plt.savefig("ChiQuadro.png")
