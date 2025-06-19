import matplotlib.pyplot as plt
import numpy as np


dati=np.loadtxt("dati.csv",delimiter=",")
pi=dati[:,0]
err=dati[:,1]

N=100
plt.plot(range(0,N),[np.pi]*N,color="red",label="Valore Teorico")
plt.errorbar(range(0,N),pi,yerr=err,label="Valore Sperimentale")
plt.xlabel("N blocchi")
plt.ylim(3.05,3.35)
plt.title("Valore PiGreco")
plt.ylabel("Valore PiGreco")
plt.grid()
plt.legend()
plt.savefig("PiGreco.png")
plt.close()