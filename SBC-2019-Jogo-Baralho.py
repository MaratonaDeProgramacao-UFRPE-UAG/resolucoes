# Resolucao escrita por Kelwin Jonas

def venceu(jogador):                                        #o jogador vencerá o jogo se tiver apenas 4 cartas em mãos, se ele não tiver com
    if(len(jogador[0]) == 4 and jogador[1][0] == False):    #curinga, e se todas as cartas forem iguais
        temp = jogador[0][:]
        temp.sort()
        if(temp[0] == temp[len(temp)-1]):
            return True
        return False
    return False

n, k = list(map(int, input().split(" ")))
jogadores = []
vencedor = False
indice = k-1

dicio = {'A':1, '2':2, '3': 3, '4':4, '5':5, '6':6, '7':7, '8':8, '9':9, 'D':10, 'Q':11, 'J':12, 'K':13}
#Dicionario pra atribuir um valor a cada carta do baralho

for i in range(n):                                          #Cada jogador terá suas cartas em mãos armazenadas numa lista
    entrada = input()                                       #também guardaremos um booleano para saber se o jogador está com o curinga
    player = []
    contadorCartas = [54] * 14                              #também guardaremos em um vetor a quantidade de cada tipo carta que
    for j in range(4):                                      #que o jogador possui
        valor = dicio.get(entrada[j])
        if(contadorCartas[valor] == 54):                    #54 será como nosso valor infinito, para facilitar a busca pela menor 
            contadorCartas[valor] = 1                       #quantidade de cartas em contadorCartas
        else:
            contadorCartas[valor] += 1
        player.append(valor)
    if(i+1 == k):
        jogadores.append([player, [True, 0], contadorCartas])
    else:
        jogadores.append([player, [False, 0], contadorCartas])

for i in range(0, n):                                       #antes de simularmos o jogo, verificamos se há alguém que já venceu o jogo
    if(i+1 != k):                                           #com as cartas que já recebeu. Lembrando que ele não pode ser o curinga
        if(venceu(jogadores[i])):                           #porque possui 5 cartas
            print(i+1)
            vencedor = True
            break

while(not vencedor):                                        #se não tivemos um ganhador antes do jogo realmente começar, então iniciamos 
    passouCoringa = False                                   #a simulação
    if(jogadores[indice][1][0] == True and jogadores[indice][1][1] > 0): #se o jogador atual for o curinga e ele não jogou nenhuma vez
        jogadores[indice][1][0] = False                                  #depois que foi declarado curinga, então ele deixa de ser o curinga 
        jogadores[indice][1][1] = 0                                      #o curinga então será o próximo jogador                

        if(indice == n-1):
            jogadores[0][1][0] = True
        else:
            jogadores[indice+1][1][0] = True

        if(venceu(jogadores[indice])):                                  #caso ele tenha os requisitos pra vencer após se livrar do curinga
            print(indice+1)                                             #então já temos nossa resposta
            break

        passouCoringa = True

    elif(jogadores[indice][1][0] == True):                              #se caso seja a primeira jogada dele com o curinga, entao ele tem que
        jogadores[indice][1][1] += 1                                    #continuar com a carta
    if(passouCoringa == False):                                         #se ele não descartou o curinga, então ele irá descartar uma carta
        qntCarta = min(jogadores[indice][2])                            #achamos qual a quantidade menor de cartas da mão
        indeceQntCarta = jogadores[indice][2].index(qntCarta)           #e então pegamos a menor carta da menor quantidade
        jogadores[indice][2][indeceQntCarta] -= 1                       #tiramos essa carta do vetor de quantidade
        jogadores[indice][0].remove(indeceQntCarta)                     #e removemos da mão do jogador

        if(jogadores[indice][2][indeceQntCarta] == 0):                  #se a carta era única, então voltamos com infinito
            jogadores[indice][2][indeceQntCarta] = 54

        if(venceu(jogadores[indice])):                                  #após o jogador fazer seu movimento, verificamos se ele ganhou o jogo
            print(indice+1)
            break

        if(indice == n-1):                                              #se ele não ganhou, a gente atualiza as cartas do próximo jogador que 
            jogadores[0][0].append(indeceQntCarta)                      #ficará com a carta descartada do jogador atual
            if(jogadores[0][2][indeceQntCarta] == 54):
                jogadores[0][2][indeceQntCarta] = 1
            else:
                jogadores[0][2][indeceQntCarta] += 1
        else:
            jogadores[indice+1][0].append(indeceQntCarta)
            if(jogadores[indice+1][2][indeceQntCarta] == 54):
                jogadores[indice+1][2][indeceQntCarta] = 1
            else:
                jogadores[indice+1][2][indeceQntCarta] += 1
    if(indice == n-1):
        indice = 0
    else:
        indice += 1

#todo o processo se repete até que haja um vencedor
