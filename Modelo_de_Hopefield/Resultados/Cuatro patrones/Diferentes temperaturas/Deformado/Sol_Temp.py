import matplotlib.pyplot as plt
import numpy as np
 

x,y,w,z,k= np.loadtxt('Solapamiento.dat', unpack=True)


plt.plot(x,y,"-",color='#581845')
plt.plot(x,y,"+",color='#581845',label='Imagen 1')

plt.plot(x,z,"-",color='#c70039')
plt.plot(x,z,"+",color='#c70039',label='Imagen 2') 

plt.plot(x,w,"-",color='#ff5733')
plt.plot(x,w,"+",color='#ff5733',label='Imagen 3')

plt.plot(x,k,"-",color='#ffc30f')
plt.plot(x,k,"+",color='#ffc30f',label='Imagen 4')

plt.xlabel('Temperatura')
plt.ylabel('Solapamiento')
plt.legend()
plt.show()