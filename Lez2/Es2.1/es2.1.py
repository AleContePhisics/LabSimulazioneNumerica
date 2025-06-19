import matplotlib.pyplot as plt
import numpy as np

dati=np.loadtxt("dati.csv",delimiter=",")

Int=dati[:,0]
err=dati[:,1]
Int2=dati[:,2]
err2=dati[:,3]
N=100
#metodo media
x=range(0,N)
plt.plot(x,Int,color="blue",label="Metodo Media")
plt.errorbar(range(0,N),Int,yerr=err)
plt.title("Integrale p(x) Uniforme")
plt.xlabel("N Blocchi")
plt.ylabel("Valore Integrale")
plt.ylim(0.87,1.12)
plt.grid()
plt.plot(x,[1]*len(x),color="red",label="Valore Atteso")
plt.legend()
plt.savefig("p(x) Uniforme.png")
plt.close()

#metodo importance sampling
x=range(0,N)
plt.plot(x,Int2,color="blue",label="Metodo Rejecting")
plt.errorbar(range(0,N),Int2,yerr=err2)
plt.plot(x,[1]*len(x),color="red",label="Valore Atteso")
plt.title("Integrale p(x) Sampling")
plt.xlabel("N Blocchi")
plt.ylabel("Valore Integrale")
#plt.ylim(0.87,1.12)
plt.grid()
plt.legend()
plt.savefig("p(x) ImpSampling.png")