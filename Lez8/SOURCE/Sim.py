import matplotlib.pyplot as plt
import numpy as np
 
H=[]
Hb=[]

H=np.loadtxt("../OUTPUT/Risultati.dat",max_rows=6000)
err=np.loadtxt("../OUTPUT/Risultati.dat",skiprows=6000)

mu1=np.loadtxt("../OUTPUT/Mu.dat",max_rows=2000)
mu2=np.loadtxt("../OUTPUT/Mu.dat",skiprows=2000,max_rows=4000)
mu3=np.loadtxt("../OUTPUT/Mu.dat",skiprows=4000)

sigma1=np.loadtxt("../OUTPUT/Sigma.dat",max_rows=2000)
sigma2=np.loadtxt("../OUTPUT/Sigma.dat",skiprows=2000,max_rows=4000)
sigma3=np.loadtxt("../OUTPUT/Sigma.dat",skiprows=4000)

# Grafico H per step

x=np.linspace(0,6000,60)
plt.errorbar(range(0,6000),H,yerr=err,label="Valori Sperimentali")
plt.plot(x, [-0.46]*len(x), color="red", label="Valore Atteso")

plt.grid()
plt.title("<H> al variare di $\sigma$ e $\mu$")
plt.xlabel("Step")
plt.legend()
plt.ylabel("Energia")
plt.savefig("../OUTPUT/EnergyStep.png")
plt.close()

# Grafico andamento di mu e sigma 

plt.plot(mu1,sigma1,color="red",label="step<2000")
plt.plot(mu2,sigma2,color="green",label="2000<step<4000")
plt.plot(mu3,sigma3,color="blue",label="step>4000, max=6000")


plt.grid()
plt.title("Minimizzazione Mu e Sigma")
plt.xlabel("Mu")
plt.ylabel("Sigma")
plt.legend()
plt.savefig("../OUTPUT/MuSigma.png")
plt.close()

#Grafico H con mu e sigma best

dati2=np.loadtxt("../OUTPUT/BestH.dat",delimiter=",")
Hb=dati2[:,0]
err=dati2[:,1]
x=np.linspace(0,5000,60)
plt.errorbar(range(0,5000),Hb,yerr=err,label="Valori Sperimentali")
plt.grid()
plt.title("H con Mu e Sigma Perfetti")
plt.xlabel("Step")
plt.ylim(-0.41,-0.48)
plt.ylabel("Energia")
plt.savefig("../OUTPUT/BestEnergyStep.png")
plt.close()

# Distrib di Probabilità

psi2=np.loadtxt("../OUTPUT/ModuleSquare.dat")

x_min=-3.0
x_max=3.0
n_bins=len(psi2)
bin_width=(x_max-x_min)/n_bins

def Psi2Real(x,mu,sigma):
    term1=np.exp(-((x-mu)**2)/(2*sigma**2))
    term2=np.exp(-((x+mu)**2)/(2*sigma**2))
    psi=term1+term2
    return psi**2

x_dense = np.linspace(x_min, x_max, 1000)
psi2_th = Psi2Real(x_dense, mu3[-1], sigma3[-1])
psi2_th /= np.trapz(psi2_th, x_dense)  

x=np.linspace(x_min+bin_width/2,x_max-bin_width/2,n_bins)
psi2_density=psi2/(np.sum(psi2)*bin_width)
plt.bar(x, psi2_density, width=bin_width, align='center',label="Simulazione")
plt.plot(x_dense, psi2_th, 'r-', lw=2, label='Funzione teorica |ψ(x)|²')
plt.grid()
plt.title("Distribuzione di Probabilità di ψ con $\sigma$ e $\mu$ finali")
plt.xlabel("x")
plt.legend()
plt.ylim(0,0.6)
plt.ylabel(r"$|\psi(x)|^2$")
plt.xlim(-3, 3)
plt.savefig("../OUTPUT/ModuleSquare.png")
plt.close()

