import numpy as np
from sklearn.metrics import confusion_matrix

data1 = np.loadtxt('CMdata1.log')       #Data jossa pidin arduinoa annetussa asennossa koko ajan
data2 = np.loadtxt('CMdata2.log')       #Data jossa heiluttelin arduinoa samalla

dataTrue = data1[:,0]
dataPred = data1[:,1]
data2True = data2[:,0]
data2Pred = data2[:,1]

cm = confusion_matrix(dataTrue, dataPred) 
print("Oikea CM")
print(cm)

print("")

cm2 = confusion_matrix(data2True, data2Pred)
print("Heiluteltu arduino CM")
print(cm2)
