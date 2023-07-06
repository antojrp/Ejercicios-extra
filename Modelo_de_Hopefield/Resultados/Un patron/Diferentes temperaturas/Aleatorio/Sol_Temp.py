import matplotlib.pyplot as plt
import numpy as np
 

x, y= np.loadtxt('Solapamiento.dat', unpack=True)


plt.plot(x,y,"-",color='#d668b5')
plt.plot(x,y,"+",color='#581845')
 
plt.xlabel('Temperatura')
plt.ylabel('Solapamiento')
plt.show()