import matplotlib.pyplot as plt
import numpy as np

dati=np.loadtxt("../OUTPUT/AutoCorrMC.dat",max_rows=1000)
err=np.loadtxt("../OUTPUT/ErroriMC.dat")

datiAD=np.loadtxt("../OUTPUT/AutoCorrMD.dat",max_rows=1000)
errAD=np.loadtxt("../OUTPUT/ErroriMD.dat")
x=[]
for i in range (1,100):
    x.append(10*i)
"""
#autocorrelazione metropolis

plt.plot(range(1,1001),dati,color="blue")
plt.grid()
plt.title("Autocorrelazione U/N Metropolis")
plt.xlabel("N Step")
plt.ylabel("$\chi(N)$")
plt.savefig("../OUTPUT/GRAFICI/AutoCorrelation U MC.png")
plt.close()
"""
#autocorrelazione molecolar dynamics


plt.plot(range(1,1001),datiAD,color="blue")
plt.grid()
plt.title("Autocorrelazione U/N Molecolar Dynamics")
plt.xlabel("N Step")
plt.ylabel("$\chi(N)$")
plt.savefig("../OUTPUT/GRAFICI/AutoCorrelation U MD.png")
plt.close()

"""

#errore in funzione di L metropolis
L=[100,200,400,600,800,1000,1500,2000,2500,3000,3500,4000,4500,5000]
plt.plot(L,err,color="blue")
plt.grid()
plt.title("Errore U/N Metropolis")
plt.xlabel("L = M/N")
plt.ylabel("Errore")
plt.savefig("../OUTPUT/GRAFICI/Errore U MC.png")
plt.close()

"""
#errore in funzione di L molecolar dynamics
L=[100,200,400,600,800,1000,1500,2000,2500,3000,3500,4000,4500,5000]
plt.plot(L,errAD,color="blue")
plt.grid()
plt.title("Errore U/N Molecolar Dynamics")
plt.xlabel("L = M/N")
plt.ylabel("Errore")
plt.savefig("../OUTPUT/GRAFICI/Errore U MD.png")
plt.close()

"""
#gofr metropolis
dati=np.loadtxt("../OUTPUT/gofr.dat",skiprows=1)
r=dati[:,0]
gofr=dati[:,1]
errg=dati[:,2]
plt.errorbar(r,gofr,yerr=errg)
plt.grid()
plt.title("Probabilità di trovare due particelle a distanza $\Delta$r MC")
plt.xlabel("r")
plt.ylabel("g(r)")
plt.savefig("../OUTPUT/GRAFICI/gofrMC.png")
plt.close()

#pressure MC
dati2=np.loadtxt("../OUTPUT/pressure.dat",skiprows=1)
blk=dati2[:,0]
pres=dati2[:,2]
errp=dati2[:,3]

plt.errorbar(blk,pres,yerr=errp)
plt.grid()
plt.ylim(0.4,1.4)
plt.title("Pressure Gas Metropolis")
plt.xlabel("blk")
plt.ylabel("P")
plt.savefig("../OUTPUT/GRAFICI/pressureMC.png")
plt.close()

#energy MC

dati3=np.loadtxt("../OUTPUT/potential_energy.dat",skiprows=1)
blk=dati3[:,0]
uenergy=dati3[:,2]
erru=dati3[:,3]

plt.errorbar(blk,uenergy,yerr=erru)
plt.grid()
plt.title("U/N Gas Metropolis")
plt.xlabel("blk")
plt.ylabel("U/N")
plt.savefig("../OUTPUT/GRAFICI/UenergyMC.png")
plt.close()



#gofr molecolar dynamics
dati=np.loadtxt("../OUTPUT/gofr.dat",skiprows=1)
r=dati[:,0]
gofr=dati[:,1]
errg=dati[:,2]
plt.errorbar(r,gofr,yerr=errg)
plt.grid()
plt.title("Probabilità di trovare due particelle a distanza $\Delta$r MD")
plt.xlabel("r")
plt.ylabel("g(r)")
plt.savefig("../OUTPUT/GRAFICI/gofrMD.png")
plt.close()

#pressure MD
dati2=np.loadtxt("../OUTPUT/pressure.dat",skiprows=1)
blk=dati2[:,0]
pres=dati2[:,2]
errp=dati2[:,3]

plt.errorbar(blk,pres,yerr=errp)
plt.grid()
plt.title("Pressure Gas Molecolar Dynamics")
plt.xlabel("blk")
plt.ylabel("P")
plt.savefig("../OUTPUT/GRAFICI/pressureMD.png")
plt.close()

#energy MD

dati3=np.loadtxt("../OUTPUT/potential_energy.dat",skiprows=1)
blk=dati3[:,0]
uenergy=dati3[:,2]
erru=dati3[:,3]

plt.errorbar(blk,uenergy,yerr=erru)
plt.grid()
plt.title("U/N Gas Molecolar Dynamics")
plt.xlabel("blk")
plt.ylabel("U/N")
plt.savefig("../OUTPUT/GRAFICI/UenergyMD.png")
plt.close()"""