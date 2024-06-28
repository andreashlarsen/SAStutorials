#
# Porod plot
#

import numpy as np
import matplotlib.pyplot as plt

q,I,sigma = np.genfromtxt('SASDMF2.dat',skip_header=2,skip_footer=4,unpack=True)

background = 1
plt.plot(q,q**4*(I+background),linestyle='none',marker='.',color='red')
plt.xlabel('q [$\AA^{-1}$]')
plt.ylabel('q$^4$ I')
plt.yscale('log')
plt.xscale('log')
plt.show()
