import numpy as np

interfacePos=[]
temperature_data=[];

for i,numCell in enumerate([320,640,1280],start=0):
    interface_data = np.genfromtxt('stefanProblem_%d/postProcessing/surfaces/2000/gamma_L_interface.raw' % numCell, delimiter=' ')
    temperature_data += [np.genfromtxt('stefanProblem_%d/postProcessing/singleGraph/2000/line_T.xy' % numCell, delimiter=' ')]
    interfacePos += [np.mean(interface_data[:,0])]

error1 = np.repeat(temperature_data[-3][:,1],2)-temperature_data[-2][:,1]
error2 = np.repeat(temperature_data[-2][:,1],2)-temperature_data[-1][:,1]
mynorm1=sum(error1)
mynorm2=sum(error2)

print "Grid convergence using temperature field: ",np.log(2*mynorm1/mynorm2)/np.log(2)
print "Grid convergence using phase interface position: ", np.log(2*(interfacePos[-3]-interfacePos[-2])/(interfacePos[-2]-interfacePos[-1]))/np.log(2)