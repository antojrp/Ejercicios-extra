import matplotlib.pyplot as plt
import numpy as np
 

y1,z1,w1,x1= np.loadtxt('T=0.0001.dat', unpack=True)
y2,z2,w2,x2= np.loadtxt('T=0.01.dat', unpack=True)
y3,z3,w3,x3= np.loadtxt('T=0.025.dat', unpack=True)
y4,z4,w4,x4= np.loadtxt('T=0.035.dat', unpack=True)
y5,z5,w5,x5= np.loadtxt('T=0.04.dat', unpack=True)
y6,z6,w6,x6= np.loadtxt('T=0.05.dat', unpack=True)

x=np.linspace(0,100,101)



plt.figure()
plt.plot(x,y1,"-",label='T=0.0001')
plt.plot(x,y2,"-",label='T=0.01')
plt.plot(x,y3,"-",label='T=0.025')
plt.plot(x,y4,"-",label='T=0.035')
plt.plot(x,y5,"-",label='T=0.04')
plt.plot(x,y6,"-",label='T=0.05')
 
plt.xlabel('Pasos Monte Carlo')
plt.ylabel('Solapamiento')
plt.legend()
plt.show()

plt.figure()
plt.plot(x,z1,"-",label='T=0.0001')
plt.plot(x,z2,"-",label='T=0.01')
plt.plot(x,z3,"-",label='T=0.025')
plt.plot(x,z4,"-",label='T=0.035')
plt.plot(x,z5,"-",label='T=0.04')
plt.plot(x,z6,"-",label='T=0.05')
 
plt.xlabel('Pasos Monte Carlo')
plt.ylabel('Solapamiento')
plt.legend()
plt.show()

plt.figure()
plt.plot(x,w1,"-",label='T=0.0001')
plt.plot(x,w2,"-",label='T=0.01')
plt.plot(x,w3,"-",label='T=0.025')
plt.plot(x,w4,"-",label='T=0.035')
plt.plot(x,w5,"-",label='T=0.04')
plt.plot(x,w6,"-",label='T=0.05')
 
plt.xlabel('Pasos Monte Carlo')
plt.ylabel('Solapamiento')
plt.legend()
plt.show()

plt.figure()
plt.plot(x,x1,"-",label='T=0.0001')
plt.plot(x,x2,"-",label='T=0.01')
plt.plot(x,x3,"-",label='T=0.025')
plt.plot(x,x4,"-",label='T=0.035')
plt.plot(x,x5,"-",label='T=0.04')
plt.plot(x,x6,"-",label='T=0.05')
 
plt.xlabel('Pasos Monte Carlo')
plt.ylabel('Solapamiento')
plt.legend()
plt.show()

