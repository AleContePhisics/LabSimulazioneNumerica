import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import maxwell
import os

dati = np.loadtxt("../OUTPUT/pofv.dat", skiprows=1)
vel = dati[:,0]
pofv = dati[:,1]
err = dati[:,2]

n_bins = 30
n_blocchi = len(vel) // n_bins  
blocchi_per_fig = int(n_blocchi/4)
blocchi_per_subplot = int(blocchi_per_fig/5)
subplots_per_fig = blocchi_per_fig // blocchi_per_subplot

v_theory = np.linspace(min(vel), max(vel), 1000)
mb_dist = maxwell.pdf(v_theory, scale=np.sqrt(1.3))

for fig_num in range(4):  
    fig, axs = plt.subplots(subplots_per_fig, 1, figsize=(6, 4 * subplots_per_fig))

    for subplot_num in range(subplots_per_fig):
        start_block = fig_num * blocchi_per_fig + subplot_num * blocchi_per_subplot
        end_block = start_block + blocchi_per_subplot

        if start_block >= n_blocchi:
            continue

        v_medio = np.zeros(n_bins)
        p_medio = np.zeros(n_bins)
        e_medio = np.zeros(n_bins)

        valid_blocks = 0

        for b in range(start_block, min(end_block, n_blocchi)):
            idx = b * n_bins
            v_medio += vel[idx:idx + n_bins]
            p_medio += pofv[idx:idx + n_bins]
            e_medio += err[idx:idx + n_bins] ** 2  

            valid_blocks += 1

        v_medio /= valid_blocks
        p_medio /= valid_blocks
        e_medio = np.sqrt(e_medio) / valid_blocks

        # Normalizzazione
        delta_v = np.mean(np.diff(v_medio))
        norm_factor = np.sum(p_medio * delta_v)
        if norm_factor > 0:
            p_medio /= norm_factor

        # Plot
        ax = axs[subplot_num]
        ax.errorbar(v_medio, p_medio, yerr=e_medio, fmt='o-', markersize=4,
                    label='Valori Sperimentali')
        ax.plot(v_theory, mb_dist, 'r-', lw=2, label='MaxBoltzmann Teorica')
        ax.set_title(f'Blocchi {start_block}-{end_block}')
        ax.set_xlabel('Velocità')
        ax.set_ylabel(r'$\rho(v)$')
        ax.legend(fontsize='small')
        ax.grid()

    plt.tight_layout()
    plt.savefig(f"../OUTPUT/GRAFICI/Boltzmann{fig_num + 1}.png")
    plt.close()

dati2=np.loadtxt("../OUTPUT/temperature.dat",skiprows=1)

T=dati2[:,2]
errT=dati2[:,3]

plt.errorbar(range(n_blocchi),T,yerr=errT,fmt="o-", markersize=3)
plt.grid()
plt.title("Temperatura Sistema Normale")
plt.xlabel("N blocchi")
plt.ylabel("T")
plt.savefig("../OUTPUT/GRAFICI/Temperatura.png")
plt.close()

dati3=np.loadtxt("../OUTPUT/potential_energy.dat",skiprows=1)

U=dati3[:,2]
errU=dati3[:,3]

plt.errorbar(range(n_blocchi),U,yerr=errU)
plt.grid()
plt.title("Energia Potenziale Sistema Normale")
plt.xlabel("N blocchi")
plt.ylabel("U")
plt.savefig("../OUTPUT/GRAFICI/Potenziale.png")
plt.close()

