import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

#data = np.loadtxt('putty.log')

df = pd.read_csv('test.csv', sep=';', usecols=[5,6,7])

datahyi = df.to_numpy()

#print(datahyi)

#datahyi = np.zeros((40,3),dtype=int)

#datahyi[:,0] = data[0:-1:3]
#datahyi[:,1] = data[1:-1:3]
#datahyi[:,2] = data[2:len(data):3]

NumberOfRows = datahyi.shape[0]

#randomCenterPoints = np.random.randint(np.min(datahyi),np.max(datahyi),size=(4,3))  # 4 random X,Y,Z points in the data range
randomCenterPoints = np.random.randint(200,450,size=(4,3))
#centerPointCumulativeSum = np.zeros((4,3),dtype=int)
#Counts = np.zeros((1,4),dtype=int)
#Distances = np.zeros((1,4),dtype=int)
#print(NumberOfRows)
#print(randomCenterPoints)

#print(datahyi)
print(np.min(datahyi))
print(np.max(datahyi))

numberOfIterations = 10
allCenterPoints = np.zeros((numberOfIterations,12))

for k in range(numberOfIterations):
 
    centerPointCumulativeSum = np.zeros((4,3),dtype=int)
    Counts = np.zeros((1,4),dtype=int)
    Distances = np.zeros((1,4),dtype=int)


    for i in range(NumberOfRows):
        for j in range(4):
            Distances[0][j] = np.linalg.norm(datahyi[i]-randomCenterPoints[j])
        Cluster = np.argmin(Distances)
        centerPointCumulativeSum[Cluster] += datahyi[i]
        Counts[0][Cluster] += 1


    for i in range(4):
        if Counts[0][i] == 0:
            #randomCenterPoints[i] = np.random.randint(np.min(datahyi),np.max(datahyi),size=(1,3))
            randomCenterPoints[i] = np.random.randint(200,450,size=(1,3))
        else:
            randomCenterPoints[i] = centerPointCumulativeSum[i]/Counts[0][i]

    allCenterPoints[k] = randomCenterPoints.reshape(1,12)


allCenterPoints = allCenterPoints.reshape(numberOfIterations*4,3)

print(centerPointCumulativeSum)
print(Counts)
print(allCenterPoints)

fig = plt.figure()
ax = fig.add_subplot(projection='3d')

ax.set_xlabel('x')
ax.set_ylabel('y')
ax.set_zlabel('z')

ax.scatter(datahyi[:,0],datahyi[:,1],datahyi[:,2],c='blue',marker='x')
ax.scatter(randomCenterPoints[:,0],randomCenterPoints[:,1],randomCenterPoints[:,2],c='red',marker='X',s=100)
ax.scatter(allCenterPoints[:,0],allCenterPoints[:,1],allCenterPoints[:,2],c='green',marker='^')

Start = 'int kp[4][3] = '
SendableData = '{\n{' + str(randomCenterPoints[0,:]) + '},\n{' + str(randomCenterPoints[1,:]) + '},\n{' + str(randomCenterPoints[2,:]) + '},\n{' + str(randomCenterPoints[3,:]) + '}};'

SendableData = SendableData.replace('[','')
SendableData = SendableData.replace(']','')
SendableData = SendableData.replace(' ',',')
SendableData = Start + SendableData
print(SendableData)

with open('centerpoints.h', 'w') as f:
    f.write(SendableData)

plt.show()

