import matplotlib.pyplot as plt
import numpy as np
from PIL import Image


i=2
if i==0:
    dati=np.loadtxt("../OUTPUT/Circle.dat",delimiter=",")
    path=np.loadtxt("../OUTPUT/CirclePath.dat")
    x=dati[:,0]
    y=dati[:,1]
    xp=[]
    yp=[]
    for el in path:
        xp.append(x[int(el-1)])
        yp.append(y[int(el-1)])
    xp.append(xp[0])
    yp.append(yp[0])
    plt.scatter(x,y,color="red")
    plt.plot(xp,yp,color="black")

    for i, el in enumerate(path):
        plt.text(xp[i] + 0.03, yp[i] + 0.02, str(int(el)), fontsize=8, color="black")

    plt.xlim(-1.5,1.5)
    plt.ylim(-1.2,1.2)
    plt.grid()
    plt.xlabel("X")
    plt.ylabel("Y")
    plt.title("Best Path Circle")
    plt.savefig("../OUTPUT/Circle.png")
    plt.close()

    data=np.loadtxt("../OUTPUT/CircleLoss.dat",delimiter=",")
    loss=data[:,0]
    avgloss=data[:,1]

    plt.plot(range(0,2000),loss)
    plt.title("LossFunction Circle Path")
    plt.xlabel("N generation")
    plt.ylabel("L")
    plt.grid()
    plt.savefig("../OUTPUT/LossCircle.png")
    plt.close()

    plt.plot(range(0,2000),avgloss)
    plt.title("LossFunction Circle Path")
    plt.xlabel("N generation")
    plt.ylabel("L")
    plt.grid()
    plt.savefig("../OUTPUT/AvgLossCircle.png")
    plt.close()


if i==1:
    dati=np.loadtxt("../OUTPUT/Square.dat",delimiter=",")
    path=np.loadtxt("../OUTPUT/SquarePath.dat")

    x=dati[:,0]
    y=dati[:,1]
    xp=[]
    yp=[]
    for el in path:
        xp.append(x[int(el-1)])
        yp.append(y[int(el-1)])
    xp.append(xp[0])
    yp.append(yp[0])
    plt.scatter(x,y,color="red")
    plt.plot(xp,yp,color="black")
    for i, el in enumerate(path):
        plt.text(xp[i] + 0.03, yp[i] + 0.02, str(int(el)), fontsize=8, color="black")

    plt.xlim(-0.2,1.2)
    plt.ylim(-0.3,1.3)
    plt.grid()
    plt.title("Best Path Random Square")
    plt.xlabel("X")
    plt.ylabel("Y")
    plt.savefig("../OUTPUT/Square.png")
    plt.close()

    data=np.loadtxt("../OUTPUT/SquareLoss.dat",delimiter=",")
    loss=data[:,0]
    avgloss=data[:,1]

    plt.plot(range(0,2000),loss)
    plt.title("LossFunction Random Square Path")
    plt.xlabel("N generation")
    plt.ylabel("L")
    plt.grid()
    plt.savefig("../OUTPUT/LossSquare.png")
    plt.close()

    plt.plot(range(0,2000),avgloss)
    plt.title("Average LossFunction Random Square Path")
    plt.xlabel("N generation")
    plt.ylabel("L")
    plt.grid()
    plt.savefig("../OUTPUT/AvgLossSquare.png")
    plt.close()

if i==2:

    img_path = '../INPUT/europa.jpg'  # Cambia se il file è in un'altra cartella
    img = Image.open(img_path)
    width, height = img.size
    dati=np.loadtxt("../INPUT/europa.dat",delimiter=" ")
    path=np.loadtxt("../OUTPUT/EuropePath.dat")
    x=dati[:,0]
    y=dati[:,1]
    xp=[]
    yp=[]
    for el in path:
        xp.append(x[int(el-1)])
        yp.append(y[int(el-1)])
    xp.append(xp[0])
    yp.append(yp[0])

    # Crea la figura
    plt.figure(figsize=(10, 8))
    img = img.transpose(method=Image.FLIP_TOP_BOTTOM)
    plt.imshow(img)
    plt.plot(xp,yp,color="black")
    plt.xlim(0,800)
    plt.ylim(0,700)
    plt.grid()
    plt.title("Best Path Europe Capital")
    plt.xlabel("X")
    plt.ylabel("Y")
    plt.savefig("../OUTPUT/Europe.png")
    plt.close()

    plt.savefig("Europa.png")
