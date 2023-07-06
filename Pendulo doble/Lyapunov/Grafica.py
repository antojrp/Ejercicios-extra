import matplotlib.pyplot as plt
import numpy as np
 

y1= np.loadtxt('E=1.dat', unpack=True)
y2= np.loadtxt('E=3.dat', unpack=True)
y3= np.loadtxt('E=5.dat', unpack=True)
y4= np.loadtxt('E=10.dat', unpack=True)
y5= np.loadtxt('E=15.dat', unpack=True)
y6= np.loadtxt('E=50.dat', unpack=True)


x = np.linspace(0,1499,1499)

plt.plot(x,y1, label='E=1')
plt.plot(x,y2, label='E=3')
plt.plot(x,y3, label='E=5')
plt.plot(x,y4, label='E=10')
plt.plot(x,y5, label='E=15')
plt.plot(x,y6, label='E=50')
 

plt.xlabel('Paso')
plt.ylabel('$\lambda_L$')
plt.legend()
plt.show()