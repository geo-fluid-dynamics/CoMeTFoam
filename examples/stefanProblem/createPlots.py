import numpy as np
import matplotlib.pyplot as plt

temperature_data=[]
temperature_data_analytical=[]

for i,numTime in enumerate([400,800,1200,1600,2000],start=0):
    temperature_data += [np.genfromtxt('stefanProblem_1280/postProcessing/singleGraph/%d/line_T.xy' % numTime, delimiter=' ')]
    plt.plot(temperature_data[i][:,0], temperature_data[i][:,1],label='%d seconds' % numTime)
    temperature_data_analytical += [np.genfromtxt('analyticalSolution/T_%d.dat' % numTime, delimiter=' ')]
    if numTime==2000:
    	plt.plot(temperature_data_analytical[i][:,0], temperature_data_analytical[i][:,1], 'ro',label='Analytical solutions')
    else:
    	plt.plot(temperature_data_analytical[i][:,0], temperature_data_analytical[i][:,1], 'ro')

plt.ylabel('Temperature [K]')
plt.xlabel('x [m]')
plt.axis([0, 0.025, 260, 295])
legend = plt.legend(loc='upper center', shadow=True)
plt.savefig('stefanProblemComparison.png', bbox_inches='tight')
#plt.show()