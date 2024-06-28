# Guinier analysis

import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

q,I,sigma = np.genfromtxt('SASDMF2.dat',skip_header=2,skip_footer=4,unpack=True)

q_squared_max = INSERT_VALUE
qmax = np.sqrt(q_squared_max)
idx_Guinier = np.where(q<=qmax)

q2 = q[idx_Guinier]**2
lnI = np.log(I[idx_Guinier])

def linear_fit(x,a,b):
    y = a*x + b
    return y

p_opt,p_cov = curve_fit(linear_fit,q2,lnI)
lnI_fit = linear_fit(q2,*p_opt)
slope,intersection = p_opt

I0 = np.exp(intersection)
Rg = np.sqrt(-3*slope)

qRg = qmax*Rg
plt.plot(q2,lnI,linestyle='none',marker='.',color='red',label='data')
plt.plot(q2,lnI_fit,color='black',label='Guinier fit, I(0)=%1.2f, Rg=%1.2f, qmaxRg =%1.2f' % (I0,Rg,qRg))
plt.xlabel('q$^2$ [$\AA^{-2}$]')
plt.ylabel('log(Intensity)')
plt.legend()
plt.show()

