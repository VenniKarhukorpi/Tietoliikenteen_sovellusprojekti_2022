import numpy as np

data = np.loadtxt('putty.log')
print(len(data))

datahyi = np.zeros((40,3),dtype=int)

datahyi[:,0] = data[0:-1:3]
datahyi[:,1] = data[1:-1:3]
datahyi[:,2] = data[2:len(data):3]

print(datahyi)

'''
foo = np.arange(data)
print(foo[0:-1:3])

datahyi = np.zeros((len,3))
'''


