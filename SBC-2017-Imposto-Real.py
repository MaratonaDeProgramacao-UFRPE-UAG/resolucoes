# Creditos para Kelwin Jonas

from collections import defaultdict

import sys 
sys.setrecursionlimit(10**6) 

km = 0

class Grafo: 
  
    def __init__(self): 
        self.lista = defaultdict(list)
        self.pesos = defaultdict(list)
  
    def addAresta(self, u, v, peso): 
        self.lista[u].append(v)
        self.pesos[u].append(peso)

    def DFS_Visit(self, v, visitados, pai, carruagem, ouro):
        global km
        visitados[v] = True
        
        for i in self.lista[v]: 
            if visitados[i] == False:
                ouro[v-1] += self.DFS_Visit(i, visitados, v, carruagem, ouro)#chamamos a própria função para ir mais fundo no grafo
                                                                             #visitando as cidades "filhas" que ainda têm ouro
        if(v != 1):                                                                                                                           
            indicePai = self.lista[v].index(pai)            #recuperamos o índice do vértice pai na lista de adjacência
            peso = self.pesos[v][indicePai]                 #recuperamos a distância entre os dois na lista de pesos
            viagens = ouro[v-1]//carruagem                  #de acordo com a capacidade da carruagem, calculamos quantas viagens 
            resto = ouro[v-1]%carruagem                     #serão necessárias para levar o ouro do vértice v até o seu pai
            if(resto > 0):
                viagens += 1
                
            viagens *= 2
            km += viagens*peso                              #armazenamos em km quantos kilometros são necessários para transportar
                                                            #todo ouro do vértice v até seu pai
            return ouro[v-1]                                #e então retornarmos todo ouro pra ser armazenado no cofre da cidade pai

    def DFS(self, s, carruagem, ouro): 
        visitados = [False] * (len(self.lista)+1)
        self.DFS_Visit(s, visitados, s, carruagem, ouro) 

if __name__ == "__main__":
    #O problema pode ser resolvido com uma busca em profundidade.
    #A cada nova cidade encontrada, se a mesma ainda tiver ouro, pegamos esse ouro e deixamos no cofre da cidade
    #que primeiro "encontrou" ela. Ou seja, vamos até os vértices folhas e vamos transportando esse ouro até chegar no vértice raiz.
    km = 0
    g = Grafo()
    n, c = list(map(int, input().split(" ")))
    ouro = list(map(int, input().split(" ")))
    for k in range(n-1):
        a, b, peso = list(map(int, input().split(" ")))
        g.addAresta(a, b, peso)
        g.addAresta(b, a, peso)
    g.DFS(1, c, ouro)
    print(km)
