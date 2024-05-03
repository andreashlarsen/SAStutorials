#
# Guinier plot
#

import numpy as np
import matplotlib.pyplot as plt

q,I,sigma = np.genfromtxt('SASDMF2.dat',skip_header=2,skip_footer=4,unpack=True)

plt.plot(q**2,np.log(I),linestyle='none',marker='.',color='red')
plt.xlabel('q$^2$ [$\AA^{-2}$]')
plt.ylabel('log(Intensity)')
plt.show()
