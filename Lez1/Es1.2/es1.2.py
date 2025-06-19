import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import norm, cauchy

# Caricamento dati
dati = np.loadtxt("dati2.csv", delimiter=",")
S1exp, S2exp, S10exp, S100exp = dati[:,0], dati[:,1], dati[:,2], dati[:,3]
S1unf, S2unf, S10unf, S100unf = dati[:,4], dati[:,5], dati[:,6], dati[:,7]
S1ltz, S2ltz, S10ltz, S100ltz = dati[:,8], dati[:,9], dati[:,10], dati[:,11]

def plot_distribuzione_2x2(dati_array, bins, range_, titolo_base, gauss_params=None, lorentzian=False):
    fig, axs = plt.subplots(2, 2, figsize=(12, 10))  # 2 righe x 2 colonne
    Ns = [1, 2, 10, 100]

    for i, ax in enumerate(axs.flat):
        ax.hist(dati_array[i], bins=bins, density=True, range=range_, stacked=True)
        ax.grid(True)
        ax.set_xlabel("Numeri Casuali")
        ax.set_ylabel("Prob. di Generazione")
        ax.set_title(f"{titolo_base} N={Ns[i]}")

        if Ns[i] == 100:
            if gauss_params is not None:
                x_gauss, y_gauss = gauss_params
                ax.plot(x_gauss, y_gauss, color="red", label="Gaussiana teorica")
                ax.legend()
            elif lorentzian:
                x_lorentz = np.linspace(range_[0], range_[1], 6000)
                y_lorentz = cauchy.pdf(x_lorentz, 0, 1)
                ax.plot(x_lorentz, y_lorentz, color="red", label="Lorentziana teorica")
                ax.legend()

    plt.tight_layout()
    return fig

# --- Distribuzione Esponenziale ---
exp_data = [S1exp, S2exp, S10exp, S100exp]
x_exp = np.linspace(0., 2., 400)
gauss_exp = norm.pdf(x_exp, 1, 0.1)
fig_exp = plot_distribuzione_2x2(exp_data, bins=60, range_=None, titolo_base="Esponenziale", gauss_params=(x_exp, gauss_exp))
fig_exp.savefig("Grafici/Esponenziale.png")
plt.close(fig_exp)

# --- Distribuzione Uniforme ---
unf_data = [S1unf, S2unf, S10unf, S100unf]
x_unf = np.linspace(0., 1., 400)
gauss_unf = norm.pdf(x_unf, 0.5, 0.03)
fig_unf = plot_distribuzione_2x2(unf_data, bins=60, range_=(0,1), titolo_base="Uniforme", gauss_params=(x_unf, gauss_unf))
fig_unf.savefig("Grafici/Uniforme.png")
plt.close(fig_unf)

# --- Distribuzione Lorentziana ---
ltz_data = [S1ltz, S2ltz, S10ltz, S100ltz]
fig_ltz = plot_distribuzione_2x2(ltz_data, bins=60, range_=(-6,6), titolo_base="Lorentziana", lorentzian=True)
fig_ltz.savefig("Grafici/Lorentz.png")
plt.close(fig_ltz)
