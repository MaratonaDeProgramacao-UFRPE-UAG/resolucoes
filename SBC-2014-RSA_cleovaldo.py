import math

#Este método usa do algoritmo euclidiano para calcular o Maior Divisor Comum entre 2 números
def mdc(a, b):
    while (a != 0):
        (a, b) = [b % a, a]
    return b


"""
#Este método é a versão extendida do MDC de euclides, computando o Mdc de A e B e além disso 
retornando U e V | mdc(A,B)= UA+VB, o que permite calcular (a/b)%p.

Neste método, replica-se A e B em C e D que vão ser representados como uma combinação linear de A e B.

A implementação desse método eu peguei a partir do livro "Cryptography Engineering" do autor Niels Ferguson.
"""
def mdc_estendido(a, b):
    if (a >= 0 and b >= 0):
        (c, d) = (a, b)
        (uc, vc, ud, vd) = (1, 0, 0, 1)
        while c != 0:
            q = math.floor((d / c))
            (c, d) = (d - (q * c), c)
            (uc, vc, ud, vd) = (ud - (q * uc), vd - (q * vc), uc, vc)
        return ud


"""
Este método calcula os fatores primos de um semi primo (número que vem do produto de primos)
Já que a questão precisa fatorar semiprimos até 10^9, esse cálculo precisa ser muito rápido

Peguei a ideia desse calculo no artigo "A New Factorization Method to Factorize RSA Public Key
Encryption" dos autores B. R. Ambedkar e S. S. Bedi

No mais esse método adapta a ideia de fatorização de Pollard Rho
"""
def fatoracao_large_semiprime(n):
    s1 = n
    s2 = math.sqrt(s1)
    s3 = math.ceil(s2)
    s4 = s3 - 1
    p = 0
    q = 0
    while s4 > 1:
        s4 = s3 - 1
        s5 = mdc(s3, s1)
        if (s5 > 1):
            p = s5
            q = int(s1 / p)
            break
        else:
            s3 += 1
    return p, q


"""
Este método faz o calculo (p**q)%m
Já que nos meus testes efetuar (p**q)%m não é eficiente, pelo menos em python.

O método usa a ideia da exponenciação direita pra esquerda binária

Converte q para binário então p**q pode ser descrito como p**(bin(q)) que pode ser descrito como o produtório
de (p**2i)**ai já que q é igual o somátório de cada indice do bin(q) multiplicado por 2 elevado ao indice.
Então temos (*p**2i)**ai)%m onde i é o indice de cada digito do bin(q).
"""
def exponenciacao_modular(p, q, m):
    r = 1
    while (q > 0):
        if (q & 1):
            r = (r * p) % m
        q = q >> 1
        p = (p * p) % m
    return r

def totient(n, e):
    p, q = fatoracao_large_semiprime(n) #Fatora-se N em P e Q, que são os fatores primos de N
    t = ((p-1)*(q-1))/mdc((p-1),(q-1)) #Esse é o calculo da função totiente de euler φ(N)
    u = mdc_estendido(e, t) #Esta e a linha seguinte calculam o inverso multiplicativo de e%t
    d = u % t
    return d

n, e, c = list(map(int, input().split()))
d = int(totient(n, e)) #D recebe o inverso multiplicativo de E e φ(N)
print(exponenciacao_modular(c,d,n)) #É calculado (c**d)%n

