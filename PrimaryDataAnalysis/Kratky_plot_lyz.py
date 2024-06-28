#
# Kratky plot
#

import numpy as np
import matplotlib.pyplot as plt

q,I,sigma = np.genfromtxt('SASDMF2.dat',skip_header=2,skip_footer=4,unpack=True)

background = 0.0
plt.plot(q,q**2*(I-background),linestyle='none',marker='.',color='red')
plt.xlabel('q [$\AA^{-1}$]')
plt.ylabel('q$^2$ I')
plt.show()
