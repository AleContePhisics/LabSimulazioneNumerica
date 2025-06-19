import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '3'  # Riduci i messaggi di log
import matplotlib.pyplot as plt
import tensorflow as tf
import numpy as np
from tensorflow import keras
from tensorflow.keras.models import Sequential # type: ignore
from tensorflow.keras.layers import Dense # type: ignore
from sklearn.model_selection import train_test_split
from mpl_toolkits.mplot3d import Axes3D



def f(x,y):                                                      #Funzione da Approssimare
    return np.sin(x*x+y*y)

N_dat=2000                                                     #Numero di dati per Train e Validation

model = Sequential([                                           #Creo una rete neurale formata da 1 neurone in input 
    Dense(20, activation='relu', input_shape=(2,)),            #3 hidden layer da 20 neuroni neuroni e uno finale in output
    Dense(20,activation="relu"),
    Dense(20,activation="relu"),
    Dense(1)                                                   
])

model.compile(optimizer='sgd',loss='mse',metrics=['mse'])     #Setta le configurazioni del modello, algoritmo adam
                                                               #con Loss e Metrica MeanSquareError

x_train=[]    
y_train=[]
x_test=[]
y_test=[]

for el in range(0,N_dat):                                      #Genero i dati per il Training tra (-3/2,3/2)
    if el<0.8*N_dat:                                           #Suddivido N_dat in 80% train e 20% validation
        x1=np.random.uniform(-3/2,3/2)
        x2=np.random.uniform(-3/2,3/2) 
        n=np.random.normal(0.,0.2,size=None)
        y=f(x1,x2)+n
        x_train.append([x1,x2])
        y_train.append(y)
    else:
        x1=np.random.uniform(-3/2,3/2)
        x2=np.random.uniform(-3/2,3/2) 
        n=np.random.normal(0.,0.2,size=None)
        y=f(x1,x2)+n
        x_test.append([x1,x2])
        y_test.append(y)

x_train=np.array(x_train)                                      #Trasformo le liste in Array se no model.fit non funziona
y_train=np.array(y_train).reshape(-1,1)                        
x_test=np.array(x_test)
y_test=np.array(y_test).reshape(-1,1)

history=model.fit(x_train,y_train,epochs=50,batch_size=32,validation_split=0.2,shuffle=True)

                                                               #Allena il modello con i dati di train, usando 30
                                                               #epoche,suddivide N_dat in 32 gruppi,val_split
                                                               #serve a dire la % di N_dat usata per la validation,
                                                               #shuffle per riordinare i batches dopo ogni epoca

model.get_weights()                                            #Calcolo i pesi w e i bias b del modello

score=model.evaluate(x_test,y_test,batch_size=32,verbose=1)    #Performo il modello con i dati di test,verbose=1 è
                                                               #solo per ottenere i dettagli nel terminal durante
                                                               #il processo 


plt.plot(history.history['loss'], label='Training')            #Loss durante il training


plt.plot(history.history['val_loss'], label='Validation')      #Loss durante la validazione

plt.xlabel('N Epoche')
plt.ylabel('Loss')
plt.title('Loss di Allenamento e Validazione')
plt.legend()
plt.grid(True)
plt.show()
plt.savefig("LossSin.png")
plt.close()

x_lin = np.linspace(-1.5, 1.5, 100)
y_lin = np.linspace(-1.5, 1.5, 100)
X, Y = np.meshgrid(x_lin, y_lin)
Z = f(X, Y)

                                                                
x_predicted = np.random.uniform(-1.5, 1.5, size=(100, 2))       # Predizione modello
x_predicted_sorted = x_predicted[np.lexsort((x_predicted[:, 1], x_predicted[:, 0]))]
y_predicted = model.predict(x_predicted_sorted)


x_anormal = np.array([[-2, 2], [-1.6, -1.8], [1.6, 1.8]])       # Dati anomali
y_anormal = model.predict(x_anormal)

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.plot_surface(X, Y, Z, cmap='viridis', alpha=0.5, edgecolor='none', label='Superficie Vera')  # f(x,y)
ax.scatter(x_predicted_sorted[:, 0], x_predicted_sorted[:, 1], y_predicted.flatten(), c='r', label="Modello")
ax.scatter(x_anormal[:, 0], x_anormal[:, 1], y_anormal.flatten(), c="green", label="Valori Anomali")

ax.set_xlabel("x")
ax.set_ylabel("y")
ax.set_zlabel("f(x,y)")
ax.set_title("Predizione Modello vs Funzione Vera")
plt.savefig("RegressioneSin.png")
plt.show()
