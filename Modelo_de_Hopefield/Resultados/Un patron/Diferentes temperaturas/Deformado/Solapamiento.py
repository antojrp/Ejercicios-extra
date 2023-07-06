import matplotlib.pyplot as plt
import numpy as np
 

y1= np.loadtxt('T=0.0001.dat', unpack=True)
y2= np.loadtxt('T=0.01.dat', unpack=True)
y3= np.loadtxt('T=0.015.dat', unpack=True)
y4= np.loadtxt('T=0.025.dat', unpack=True)
y5= np.loadtxt('T=0.03.dat', unpack=True)
y6= np.loadtxt('T=0.05.dat', unpack=True)

x=np.linspace(0,100,101)

plt.plot(x,y1,"-",label='T=0.0001')
plt.plot(x,y2,"-",label='T=0.01')
plt.plot(x,y3,"-",label='T=0.015')
plt.plot(x,y4,"-",label='T=0.025')
plt.plot(x,y5,"-",label='T=0.03')
plt.plot(x,y6,"-",label='T=0.05')
 
plt.xlabel('Pasos Monte Carlo')
plt.ylabel('Solapamiento')
plt.legend()
plt.show()