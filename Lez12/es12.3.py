import numpy as np
import matplotlib.pyplot as plt
from keras.models import load_model
from PIL import Image
import glob

i=1  #0 rete DNN, 1 rete CNN

# Carica il modello già allenato
if i==1:
    model = load_model("mnist_cnn_model.h5")
    print("Modello caricato con successo!")
elif i==0:
    model = load_model("mnist_dnn_model.h5")
    print("Modello caricato con successo!")

# Percorso immagini
image_folder = "./Pictures/"
image_files = sorted(
    glob.glob(image_folder + "*.[pjP][pnN][gG]") + 
    glob.glob(image_folder + "*.[jJ][pP][gG]")
)
image_files = image_files[:10]


for img_path in image_files:
    print(f"Elaboro: {img_path}")

    # Carica, scala, normalizza, inverte
    img = Image.open(img_path).convert('L')
    img_resized = img.resize((28, 28))
    data = np.array(img_resized).astype('float32') / 255.0
    data = 1 - data  # inverti colori se necessario

    if i == 1:  # CNN
        input_data = data.reshape(1, 28, 28, 1)
    elif i == 0:  # DNN
        input_data = data.reshape(1, 784)

    # Predizione
    prediction = model.predict(input_data)
    predicted_class = np.argmax(prediction)

    # Visualizza risultato
    plt.imshow(data, cmap='gray')
    plt.title(f"Predicted: {predicted_class}")
    plt.axis('off')
    plt.show()

    print("Probabilità per ogni classe:", prediction)
    print("Classe predetta:", predicted_class)
    print()
