import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '3'  # Riduci i messaggi di log
import matplotlib.pyplot as plt
import tensorflow as tf
import numpy as np
from tensorflow import keras
from tensorflow.keras.models import Sequential # type: ignore
from tensorflow.keras.layers import Dense # type: ignore
from sklearn.model_selection import train_test_split

i=1

def f(x,i):                                                      #Funzione da Approssimare
    if i==0:
        return 2*x+1
    else:
        return 4-3*x-2*x*x+3*x*x*x

N_dat=2000                                                     #Numero di dati per Train e Validation
N_epoche=30                                                    #Numero di epoche

x_train=[]    
y_train=[]
x_test=[]
y_test=[]

activations=['relu','tanh','sigmoid','selu','elu']              #Funzioni di attivazione
fig,axes=plt.subplots(1, len(activations), figsize=(5*len(activations), 5))
axes=axes.flatten()

for j, activation in enumerate(activations):

    model = Sequential([                                           #Creo una rete neurale formata da 1 neurone in input 
    Dense(20, activation=activation, input_shape=(1,)),            #3 hidden layer da 20 neuroni neuroni e uno finale in output
    Dense(20,activation=activation),
    Dense(20,activation=activation),
    Dense(1)                                                       
    ])

    model.compile(optimizer='sgd',loss='mse',metrics=['mse'])      #Setta le configurazioni del modello, algoritmo adam
                                                                   #con Loss e Metrica MeanSquareError

    for el in range(0,N_dat):                                      #Genero i dati per il Training tra (-1,1) 
        if el<0.8*N_dat:
            x=np.random.uniform(-1,1) 
            n=np.random.normal(0.,0.2,size=None)
            y=f(x,i)+n
            x_train.append(x)
            y_train.append(y)
        else:
            x=np.random.uniform(-1,1) 
            n=np.random.normal(0.,0.2,size=None)
            y=f(x,i)+n
            x_test.append(x)
            y_test.append(y)
                                                                #Suddivido N_dat in 80% train e 20% validation

        

    x_train=np.array(x_train).reshape(-1,1)                        #Trasformo le liste in Array se no model.fit 
    y_train=np.array(y_train).reshape(-1,1)                        #non funziona
    x_test=np.array(x_test).reshape(-1,1)
    y_test=np.array(y_test).reshape(-1,1)

    history=model.fit(x_train,y_train,epochs=N_epoche,batch_size=32,validation_split=0.2,shuffle=True)

                                                                #Allena il modello con i dati di train, usando 30
                                                                #epoche,suddivide N_dat in 32 gruppi,val_split
                                                                #serve a dire la % di N_dat usata per la validation,
                                                                #shuffle per riordinare i batches dopo ogni epoca

    model.get_weights()                                            #Calcolo i pesi w e i bias b del modello

    score=model.evaluate(x_test,y_test,batch_size=32,verbose=1)    #Performo il modello con i dati di test,verbose=1 è
                                                                #solo per ottenere i dettagli nel terminal durante
                                                                #il processo 


    axes[j].plot(history.history['loss'], label='Training')
    axes[j].plot(history.history['val_loss'], label='Validation')
    axes[j].set_title(f'{activation}')
    axes[j].set_xlabel('Epoche')
    axes[j].set_ylabel('Loss')
    axes[j].legend()
    axes[j].grid(True)


    x_predicted = np.random.uniform(-1, 1, 100).reshape(-1, 1)     #Uso il modello allenato con dei nuovi dati per fare
    x_predicted = np.sort(x_predicted, axis=0)
    y_predicted = model.predict(x_predicted)                       #le mie predizioni

    x_anormal=np.array([1.5,2,-1.5,1.3,1.7,-1.6]).reshape(-1,1)    #Test con dei dati fuori dal range di allenamento
    x_anormal=np.sort(x_anormal,axis=0)
    y_anormal=model.predict(x_anormal)

    plt.figure(figsize=(6,4))
    if i==0:
        plt.title("f(x)=2x+1"f'{activation}')
    else:
        plt.title("f(x)=4-3x-$2x^{2}$+$3x^{3}$"f'{activation}')

    plt.scatter(x_predicted, y_predicted, color='r', label='Predizioni Modello')
    plt.scatter(x_anormal, y_anormal, color='green', label='Dati Anormali')
    plt.plot(x_predicted, f(x_predicted,i), label='Funzione Vera')
    plt.title(f'Predizioni con attivazione: {activation}')
    plt.xlabel('x')
    plt.ylabel('y')
    plt.legend()
    plt.grid(True)
    if i==0:
        plt.savefig(f"GRAFICI/PredLin{activation}.png")
    else:
        plt.savefig(f"GRAFICI/PredPol{activation}.png")
    plt.close()
    
    x_train=[]
    y_train=[]
    x_test=[]
    y_test=[]

plt.tight_layout()
plt.savefig("GRAFICI/LossConfronto.png")
plt.show()
