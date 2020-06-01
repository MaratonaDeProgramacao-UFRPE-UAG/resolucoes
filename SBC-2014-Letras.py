# Questao submetida por Kelwin Jonas
# https://github.com/KelwinJonas

from collections import defaultdict

class Grafo: 
  
    def __init__(self): 
  
        self.grafo = defaultdict(list) 
  
    def addAresta(self,u,v): 
        self.grafo[u].append(v) 
  
    def BFS(self, s, matriz, distancia, bitMask, n):
        indice = letras.index(matriz[s-1].lower())  #recuperamos o indice correspondente da letra s no vetor de letras
        letra = matriz[s-1]                         #e também o caractere
        if(letra == letra.lower()):
            minusculo = True                        #caso a letra seja minúscula levantamos essa flag
        else:
            minusculo = False
        if((minusculo == True and bitMask[indice] == 1)or(minusculo == False and bitMask[indice] == 0)):
            return 10003
        #se a letra for minuscula ou maiuscula e o caminho não permitir, não há necessidades de ir adiante com esse tipo de caminho
        else:
            #a seguir segue a implementação da busca em largura
            visitados = [False] * (len(self.grafo))
            visitados[s-1] = True
            fila = []
            fila.append(s)

            while fila: 
                s = fila.pop(0)
                for i in self.grafo[s]:
                    indice = letras.index(matriz[i-1].lower())
                    letra = matriz[i-1]
                    if(letra == letra.lower()):
                        minusculo = True
                    else:
                        minusculo = False
                    if(visitados[i-1] == False):
                        if((minusculo == True and bitMask[indice] == 0) or (minusculo == False and bitMask[indice] == 1)):
                            #caso a letra seja minuscula ou maiuscula e o tipo de caminho permitir, a distancia desse vertice será a
                            #distancia do seu "pai" + 1
                            distancia[i-1] = distancia[s-1]+1
                            visitados[i-1] = True
                            fila.append(i)
            return distancia[(n*n)-1]
            #retornamos a distancia de 1 até NxN

g = Grafo() 
n = int(input())
cont = 0
matriz = []
distancia = []
letras = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j']


for k in range(n):
    linha = input()
    linha = list(linha)
    for i in range(1, n+1):             #laço para adicionar todas as arestas onde haja adjacencia na matriz
        if((i+cont)%n != 0):
            g.addAresta(i+cont, i+1+cont)
        if(i+cont != 1 and (i+cont-1)%n != 0):
            g.addAresta(i+cont, i-1+cont)
        if(k!=0):
            g.addAresta(i+cont, i+cont-n)
        if(k!= n-1):
            g.addAresta(i+cont, i+cont+n)
    for j in range(n):
        matriz.append(linha[j])         #preenchemos o vetor da matriz de entrada com as letras do input
        distancia.append(10003)         #preenchemos tambem o vetor de distancias para cada célula
                                        #da matriz, sendo cada uma a máxima possível (poderia ser infinito)
    cont += n

r = 10003                               #variavel de resposta
distancia[0] = 1                        #distancia da primeira célula(vértice) é de 1
for j in range(1025):                   #iteramos sob todos os tipos de caminhos possíveis 
    binario = list(str(bin(j)))         #cada tipo de caminho será representado como uma máscara de bits, onde 1 representa letra maiuscula,
    binario = binario[2:]               #e 0 minuscula. Como são 10 letras, o loop vai de 0 a 2^10
    while(len(binario) < 10):           #garantimos que a máscara terá os 10 bits necessarias
        binario.insert(0, 0)
    binario = list(map(int, binario))
    r = min(r, g.BFS(1, matriz, distancia, binario, n))         #chamamos a função busca em largura pra calcular a distancia ate a celula NxN
if(r != 10003):                                                 #se r for igual 10003 significa que não há caminho válido até NxN
    print(r)
else:
    print(-1)
