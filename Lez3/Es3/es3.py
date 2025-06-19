import matplotlib.pyplot as plt
import numpy as np

dati=np.loadtxt("Output/dati.csv",delimiter=",")
Ccall=dati[:,0]
err=dati[:,1]
Cput=dati[:,2]
err2=dati[:,3]

datin=np.loadtxt("Output/ndati.csv",delimiter=",")
Ccalln=datin[:,0]
errn=datin[:,1]
Cputn=datin[:,2]
err2n=datin[:,3]

dati2=np.loadtxt("Output/input.dat",delimiter=",")
N=int(dati2[0]) #numero di blocchi 
C=dati2[1] #valore teorico di C
P=dati2[2] #valore teorico di P

#call con calcolo di S diretto
plt.errorbar(range(0,N),Ccall,yerr=err,label="Valore Sperimentale")
plt.plot(range(0,N),[C]*N,color="red",label="Valore Teorico")
plt.grid()
plt.legend()
plt.xlabel("N blocchi")
plt.ylabel("Valore Call")
plt.title("Call Option Diretto")
plt.savefig("Output/CallOption Diretto.png")
plt.close()

#call con calcolo discreto di S
plt.errorbar(range(0,N),Ccalln,yerr=errn,label="Valore Sperimentale")
plt.plot(range(0,N),[C]*N,color="red",label="Valore Teorico")
plt.grid()
plt.legend()
plt.xlabel("N blocchi")
plt.ylabel("Valore Call")
plt.title("Call Option Discreto")
plt.savefig("Output/CallOption Discreto.png")
plt.close()

#put con calcolo di S diretto
plt.errorbar(range(0,N),Cput,yerr=err2,label="Valore Sperimentale")
plt.plot(range(0,N),[P]*N,color="red",label="Valore Teorico")
plt.grid()
plt.title("Put Option Diretto")
plt.legend()
plt.xlabel("N blocchi")
plt.ylabel("Valore Put")
plt.savefig("Output/PutOption Diretto.png")
plt.close()

#put con calcolo discreto di S

plt.errorbar(range(0,N),Cputn,yerr=err2n,label="Valore Sperimentale")
plt.plot(range(0,N),[P]*N,color="red",label="Valore Teorico")
plt.grid()
plt.title("Put Option Discreto")
plt.legend()
plt.xlabel("N blocchi")
plt.ylabel("Valore Put")
plt.savefig("Output/PutOption Discreto.png")
plt.close()
