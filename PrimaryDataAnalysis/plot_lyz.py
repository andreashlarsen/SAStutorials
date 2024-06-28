# 
# impport and plot lysozyme data
#

import numpy as np
import matplotlib.pyplot as plt

q,I,sigma = np.genfromtxt('SASDMF2.dat',skip_header=2,skip_footer=4,unpack=True)

plt.errorbar(q,I,yerr=sigma,linestyle='none',marker='.',color='red')
plt.xlabel('q [$\AA^{-1}$]')
plt.ylabel('Intensity')
plt.yscale('log')
plt.show()
