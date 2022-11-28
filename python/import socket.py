import socket
import sys
import pandas as pd

S =  socket.socket(socket.AF_INET, socket.SOCK_STREAM)
S.connect(('172.20.241.9', 20000))
S.sendall(b'85\n')

chunks = []
while True:
    data = S.recv(1024)
    if len(data) == 0:
        break
    chunks.append(data.decode('utf-8'))

for i in chunks:
    print(i, end = '')


with open('D:/School/tietoliikentee_sovellusprojekti_2022/Tietoliikenteen_sovellusprojekti_2022/Python/test3.csv', 'w') as f:
    for x in chunks:
        f.write(x)
S.close()

'''

df=pd.read_csv('D:/School/tietoliikentee_sovellusprojekti_2022/Tietoliikenteen_sovellusprojekti_2022/Python/test3.csv', sep=';')
print(df)
df.to_csv('D:/School/tietoliikentee_sovellusprojekti_2022/Tietoliikenteen_sovellusprojekti_2022/Python/test3.csv', sep = ';', index = False)

'''