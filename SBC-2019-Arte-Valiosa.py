from collections import defaultdict
import math

class Grafo: 
  
    def __init__(self): 
        self.lista = defaultdict(list)
        self.visitados = defaultdict(list)
  
    def addAresta(self,u,v): 
        self.lista[u].append(v)
        if(False not in self.visitados[u]):
            self.visitados[u].append(False)

    def getVisitado(self, u):
        return self.visitados[u]

    def setVisitado(self, u):
        self.visitados[u] = [True]
  
    def BFS(self, s):
        self.setVisitado(s)
        fila = []
        fila.append(s)

        while fila: 
            u = fila.pop(0)
            for i in self.lista[u]:
                if(self.visitados[i] == [False]):
                    if(s == 'esquerda' and i == 'baixo' or s == 'esquerda' and i == 'direita' or s == 'cima' and i == 'baixo' or s == 'cima' and i == 'direita'):
                        return False
                    self.setVisitado(i)
                    fila.append(i)
        return True


g = Grafo() 
m, n, k = list(map(int, input().split(" ")))
sensores = []
partidas = []

for i in range(k):
    x, y, raio = list(map(int, input().split(" ")))
    sensores.append([x, y, raio])

for i in range(0, k):
    if(i != k-1):
        for j in range(i+1, k):
            distancia = math.sqrt(((sensores[j][0]-sensores[i][0])**2) + ((sensores[j][1]-sensores[i][1])**2))
            if(distancia <= sensores[j][2]+sensores[i][2]):
                g.addAresta((sensores[j][0], sensores[j][1]), (sensores[i][0], sensores[i][1]))
                g.addAresta((sensores[i][0], sensores[i][1]), (sensores[j][0], sensores[j][1]))
        
    if(sensores[i][0]-sensores[i][2] <= 0):
        g.addAresta((sensores[i][0], sensores[i][1]), 'esquerda')
        g.addAresta('esquerda', (sensores[i][0], sensores[i][1]))
        partidas.append('esquerda')
    if(sensores[i][0]+sensores[i][2] >= m):
        g.addAresta((sensores[i][0], sensores[i][1]), 'direita')
        g.addAresta('direita', (sensores[i][0], sensores[i][1]))
        partidas.append('direita')
    if(sensores[i][1]-sensores[i][2] <= 0):
        g.addAresta((sensores[i][0], sensores[i][1]), 'baixo')
        g.addAresta('baixo', (sensores[i][0], sensores[i][1]))
        partidas.append('baixo')
    if(sensores[i][1]+sensores[i][2] >= n):
        g.addAresta((sensores[i][0], sensores[i][1]), 'cima')
        g.addAresta('cima', (sensores[i][0], sensores[i][1]))
        partidas.append('cima')

flag = True
flag2 = True
if('esquerda' in partidas):
    flag = g.BFS('esquerda')
if('cima' in partidas):
    flag2 = g.BFS('cima')

if(flag == False or flag2 == False):
    print("N")
else:
    print("S")
