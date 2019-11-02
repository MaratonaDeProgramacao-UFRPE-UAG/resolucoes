#By Kelwin Jonas e Luis Filipe

ent = input().split(" ")
c = int(ent[0])
N = int(ent[1])
f = c/N
menor = c
ind = -1
flag = 0
flag2 = 0
azeitonas = input().split(" ")

for i in range (N-1):
    if(abs(int(azeitonas[i+1])-int(azeitonas[i]) < menor)):
       menor = abs(int(azeitonas[i+1])-int(azeitonas[i]))
       azeitona1 = int(azeitonas[i])
       azeitona2 = int(azeitonas[i+1])
       ind = i+1
if(abs(int(azeitonas[0])+c-int(azeitonas[i+1]))<menor):
    menor = abs(int(azeitonas[0])+c-int(azeitonas[i+1]))
    azeitona1 = int(azeitonas[i])
    azeitona2 = int(azeitonas[i+1])
    ind = i+1
    
ind2 = ind
if(menor >= f):
    print("S")
else:    
    inicio = azeitona1+0.000001
    for k in range(ind, N):
        if not(int(azeitonas[k]) >= inicio and int(azeitonas[k]) <= (inicio+f)):
            flag = 1
            break
        inicio += f
    
    inicio = inicio-c
    if(flag == 0):
        for j in range(0, ind2):
            if not(int(azeitonas[j]) >= inicio and int(azeitonas[j]) <= (inicio+f)):
                flag = 1
                break
            inicio += f
            
            
    inicio = azeitona2-0.000001
    if(flag == 1):
        for k in range(ind, N):
            if not(int(azeitonas[k]) >= inicio and int(azeitonas[k]) <= (inicio+f)):
                flag2 = 1
                break
            inicio += f
    
    inicio = inicio-c
    if(flag == 1):
        for j in range(0, ind2):
            if not(int(azeitonas[j]) >= inicio and int(azeitonas[j]) <= (inicio+f)):
                flag2 = 1
                break
            inicio += f
            
    if(flag == 1 and flag2 == 1):
        print("N")
    else:
        print("S")
