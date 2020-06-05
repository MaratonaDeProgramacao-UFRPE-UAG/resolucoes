#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ulli;
typedef long long int lli;
//https://www.geeksforgeeks.org/modular-exponentiation-power-in-modular-arithmetic/
ulli expModular(ulli x, ulli y, ulli p){	//calculando x^y (mod p)
	ulli res = 1;
	x = x%p;	//reduzindo x se possivel
	if(x==0){	//se x eh multiplo de p, x^y (mod p) = 0
		return 0;
	}
	while(y>0){
		if(y%2==1){
			res = (res*x)%p;
		}
		y = y/2;
		x = (x*x)%p;
	}
	return res;
}
//https://www.geeksforgeeks.org/multiplicative-inverse-under-modulo-m/
//ja que d e e são primos entre si, podemos usar o algoritmo extendido de euclides para encontrar d e f tais que
//d*e + n*f = mdc(d, n) que, como mdc(d,n) = 1 [e e n sao primos entre si], temos que  d*e - 1 = n*f, ou seja,
// d*e tem resto 1 na divisao por n, logo, e*d = 1 (mod n)
lli invModular(ulli e, ulli n){
	lli aux, q, t, d, f;	//long long porque f e d podem ser negativos
	aux = n;
	f = 0;
	d = 1;
  if(n == 1){
  	return 0;
	}
  while(e>1){
  	q = e/n;
    t = n;
		n = e%n;
		e = t;
    t = f;
    f = d - q*f;
    d = t;
  }
  if(d<0){	//se o numero encontrado eh negativo podemos soma-lo ao n inicial para torna-lo positivo sem perder a congruencia
  	d += aux;
	}
  return d;
}
ulli buscarDivisor(ulli n){
  ulli i, j;
  bool primo[(ulli)ceil(sqrt(n))];	//criando um array com raiz(n) elementos
  fill(primo, (primo + (ulli)ceil(sqrt(n))), true);	//inicializando todo o array como true
  for(j=3; j<(ulli)sqrt(n); j+=2){	//valores pares nunca sao visitados
    if(primo[j-1] == true){	//se o valor atual eh primo
      if(n%j == 0){	//e divide n
        return j;
      }
      if(j%3 != 0 && j%5 != 0){	//multiplos de 3 e 5 nunca são visitados para melhorar a eficiencia
        for(i=j+j; i <= (ulli)ceil(sqrt(n)); i+=j){
				//usando o crivo de erastotenes para reduzir a quantidade de tentativas, todos os multiplos do primo atual ate raiz(n) sao marcados como compostos
          primo[i-1] = false;
        }
      }
    }
  }
}
int main(){
  ulli n, e, c, d, m, p, q, totiente;
  cin >> n >> e >> c;	//os valores de n, e e c sao dados
  p = buscarDivisor(n);	//descoberto o valor de p
  q = n/p;	//descoberto o valor de q	[n = pq]
  totiente = ((p-1)*(q-1));	//descoberto o valor de phi(n)	[phi(n) = (p-1)(q-1)]
  d = invModular(e, totiente);	//descoberto o valor de d	[de = 1 (mod phi(n))]
  m = expModular(c, d, n);	//descoberta a mensagem	[m = c^d (mod n)]
  cout << m%n << endl;	//mensagem descriptografada
  return 0;
}
