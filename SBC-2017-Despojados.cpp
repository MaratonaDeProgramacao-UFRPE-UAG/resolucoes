#include<iostream>
#include<math.h>
#include<set>
using namespace std;
int main(){ 
  unsigned long long int N, i, j, despojados, raiz, aux;
  set<unsigned long long int> divisores;
  set<unsigned long long int>::iterator divisor;
  bool despojado, primo;
  cin >> N;
  raiz = (unsigned long long int)sqrt(N);
  bool primos[raiz+1];
  fill(primos, primos+raiz+1, true);	//preenchendo o vetor com true
  for(i=4; i<=raiz; i+=2){	//usando o crivo de erastotenes para "cortar" os numeros pares
    primos[i] = false;			
  }
  for(i=3; i<=raiz; i+=2){	//usando o crivo de erastotenes para "cortar" o restante dos multiplos de primos menores que raiz de N
    if(primos[i] == true){
      for(j=i*i; j<raiz+2; j+=i){
        primos[j] = false;
      }
    }
  }
  divisores.insert(N);		//adicionando N aos divisores de N
  for(i=2; i<=raiz; i++){	//procurando todos os outros divisores de N e adicionando ao conj. de divisores (exceto o numero 1)
    if(N%i == 0){
      divisores.insert(i);
      divisores.insert(N/i);
    }
  }
  despojados = 0;		//contador do numero de divisores despojados de N
  for(divisor = divisores.begin(); divisor != divisores.end(); divisor++){	//percorrendo o conjunto de divisores de N
    aux = *divisor;		//aux recebe o valor do divisor atual de N
    despojado = true;		//variavel que indica se o divisor atual eh despojado
    primo = true;		//variavel que indica se o divisor atual eh primo
    if(aux != 2 && aux%2 == 0){	//verificando se o divisor de N atual eh divisivel por 2 ou eh igual a 2
      primo = false;		//se o divisor atual eh divisivel por 2 e nao eh 2, ele nao eh primo
      aux = aux/2;	
      if(aux%2 == 0){		//se o divisor atual eh divisivel por 2 mais de uma vez, ele nao eh despojado
        despojado = false;	
      }
    }
    for(j=3; j <= (unsigned long long int)sqrt(aux) && aux>1 && despojado; j+=2){	//verificando se o divisor de N atual eh divisivel por algum impar
      if(primos[j] == true){	//se o impar atual eh primo
        if(aux != j && aux%j == 0){	//se o divisor atual eh divisivel pelo impar atual e nao eh o impar atual, ele nao eh primo
          primo = false;
          aux = aux/j;
          if(aux%j == 0){	//se o divisor atual eh divisivel pelo impar atual mais de uma vez, ele nao eh despojado
            despojado = false;		
            break;		//pulamos para o proximo divisor do conjunto
          }
        }
      }
    }
    if(divisores.size() != 1){	//se N tem mais de um divisor (nao contamos o numero 1, logo, se N tem apenas um divisor ele eh primo)
      if(despojado && !primo){	//e o divisor atual nao eh divisivel mais de uma vez pelo mesmo primo e nao eh primo
        despojados++;
      }
    }
  }
  cout << despojados << endl;
  return 0;
}
