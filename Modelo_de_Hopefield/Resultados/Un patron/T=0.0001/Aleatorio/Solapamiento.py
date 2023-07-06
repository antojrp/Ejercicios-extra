import matplotlib.pyplot as plt
import numpy as np
 

y1= np.loadtxt('Solapamiento1.dat', unpack=True)
y2= np.loadtxt('Solapamiento2.dat', unpack=True)
y3= np.loadtxt('Solapamiento3.dat', unpack=True)


x=np.linspace(0,100,101)



plt.figure()
plt.plot(x,y1,"-", color='#581845', label='Prueba 1')
plt.plot(x,y2,"-", color='#c70039', label='Prueba 2')
plt.plot(x,y3,"-", color='#ff5733', label='Prueba 3')



 
plt.xlabel('Pasos Monte Carlo')
plt.ylabel('Solapamiento')
plt.legend()
plt.show()
