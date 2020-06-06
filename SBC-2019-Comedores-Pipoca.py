# Questao Submetida por Kelwin Jonas

n, c, t = list(map(int, input().split(" ")))
sacos = list(map(int, input().split(" ")))

l = 0
r = (10**9)+7 #valor arbitrariamente grande para fazermos a busca binária
minimo = (10**9)+7
c -= 1

while(l<=r):
    cTemp = c
    flag = False
    k = 0
    segundos = l+((r-l)//2)         #tempo arbitrário para verificar se é possível comer todas as pipocas
    maximoDePipocas = t*segundos    #valor máximo de pipocas que se pode comer para um competidor
    while(k < n):                   #laço para verificarmos se é possível comer todos os sacos de pipoca
        if(sacos[k] <= maximoDePipocas):       
            maximoDePipocas -= sacos[k]         #caso seja possível comer aquele saco de pipoca
            if(k == n-1):                       #se estivermos no ultimo saco de pipoca e for possivel comé-lo, significa que o tempo é suficiente
                flag = True
        elif(sacos[k] > maximoDePipocas and cTemp > 0): #caso não seja possível comer aquele saco de pipoca mas ainda houver competidores
            maximoDePipocas = t*segundos        #zeramos a quantidade de pipocas para o proximo comer
            cTemp -= 1                          #diminuímos a quantidade de competidores que já comeram o máximo que pudiam naquele tempo
            k -= 1                              #decrementamos a variavel para que a partir daquele saco haja uma nova verificação
        else:
            l = segundos + 1                    #caso não seja possível comer todas as pipocas naquele tempo, então precisamos de mais tempo
            break
        k += 1
    if(flag == True):                           #se o tempo foi determinado como suficiente, então podemos tentar um tempo inferior a esse
        r = segundos -1                         #para achar um tempo menor ainda
        minimo = min(minimo, segundos)          #o menor tempo será o menor valor de segundos

print(minimo)

#se caso tentassemos resolver o mesmo problema incrementando 1 à variavél segundos, teriamos um problema de tempo de execução
