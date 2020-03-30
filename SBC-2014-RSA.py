import math

#Calculo do MDC
def gcd(a, b):
    while (a != 0):
        (a, b) = [b % a, a]
    return b

#Calcula o MDC de forma extendida, onde retorna o MDC e os fatores
def extended_gcd(a, b):
    if (a >= 0 and b >= 0):
        (c, d) = (a, b)
        (uc, vc, ud, vd) = (1, 0, 0, 1)
        while c != 0:
            q = math.floor((d / c))
            (c, d) = (d - (q * c), c)
            (uc, vc, ud, vd) = (ud - (q * uc), vd - (q * vc), uc, vc)
        return ud

#Calcula o totiente e retorna o D | D e N compõem a chave privada e D satisfaz DE = 1 mod (t), onde t é o totiente de n
def totient(n, e):
    s1 = n
    s2 = math.sqrt(s1)
    s3 = math.ceil(s2)
    s4 = s3-1
    p = 0
    q = 0
    while s4 > 1:
        s4 = s3-1
        s5 = gcd(s3,s1)
        if(s5 > 1):
            p = s5
            q = int(s1/p)
            break
        else:
            s3 +=1
    t = ((p-1)*(q-1))/gcd((p-1),(q-1))
    u = extended_gcd(e, t)
    d = u % t
    return d

#Calcula (x**y)%k de forma rápida
def modular_exp(p, q, m):
    r = 1
    while (q > 0):
        if (q & 1):
            r = (r * p) % m
        q = q >> 1
        p = (p * p) % m
    return r

n, e, c = list(map(int, input().split())) #Recebe os 3 valores da entrada
d = int(totient(n, e)) #Calcula d
print(modular_exp(c,d,n)) #printa (c**d)%n