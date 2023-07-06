import matplotlib.pyplot as plt
import numpy as np
 

y1,z1,w1,x1= np.loadtxt('Solapamiento1.dat', unpack=True)
y2,z2,w2,x2= np.loadtxt('Solapamiento2.dat', unpack=True)
y3,z3,w3,x3= np.loadtxt('Solapamiento3.dat', unpack=True)


x=np.linspace(0,100,101)



plt.figure()

plt.plot(x,y1,"-",label='imagen 1',color='#581845')
plt.plot(x,z1,"-",label='imagen 2',color='#c70039')
plt.plot(x,w1,"-",label='imagen 3',color='#ff5733')
plt.plot(x,x1,"-",label='imagen 4',color='#ffc30f')


 
plt.xlabel('Pasos Monte Carlo')
plt.ylabel('Solapamiento')
plt.legend()
plt.show()

plt.figure()
plt.plot(x,y2,"-",label='imagen 1',color='#581845')
plt.plot(x,z2,"-",label='imagen 2',color='#c70039')
plt.plot(x,w2,"-",label='imagen 3',color='#ff5733')
plt.plot(x,x2,"-",label='imagen 4',color='#ffc30f')

 
plt.xlabel('Pasos Monte Carlo')
plt.ylabel('Solapamiento')
plt.legend()
plt.show()

plt.figure()
plt.plot(x,y3,"-",label='imagen 1',color='#581845')
plt.plot(x,z3,"-",label='imagen 2',color='#c70039')
plt.plot(x,w3,"-",label='imagen 3',color='#ff5733')
plt.plot(x,x3,"-",label='imagen 4',color='#ffc30f')

 
plt.xlabel('Pasos Monte Carlo')
plt.ylabel('Solapamiento')
plt.legend()
plt.show()
