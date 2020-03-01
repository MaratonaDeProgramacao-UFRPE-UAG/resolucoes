#include<iostream>
using namespace std;
long long int mdc(long long int a, long long int b){	//funcao para calcular mdc entre 2 numeros
  if(a==0){
    return b;
  }
  return mdc(b%a, a);
}
long long int mmc(long long int a, long long int b){	//funcao para calcular mmc entre 2 numeros
  return (a*b)/mdc(a, b);
}
//calculo de mmc acima: https://www.geeksforgeeks.org/program-to-find-lcm-of-two-numbers/
int main(){
  long long int n, lim, i, mmc_tmp, aux, result, maior;
  cin >> n >> lim;
  long long int ciclo[n];
  for(mmc_tmp=1, i=0; i<n; i++){	//recebendo todos os ciclos das populacoes anteriores e calculando o mmc entre eles
    cin >> ciclo[i];
    mmc_tmp = mmc(mmc_tmp, ciclo[i]);
  }
  for(maior=mmc_tmp, result=1, i=2; i<=lim; i++){	//testando todos os ciclos de 2 a lim para encontrar o que maximiza o mmc entre ele e todas as populacoes anteriores
    aux = mmc(mmc_tmp, i);	//testamos o mmc entre o ciclo atual e o das populacoes anteriores
    if(aux > maior && aux <= lim){	//se este for o maior que obtivemos sem ultrapassar o limite
      maior = aux;	//ele se torna o novo maior
      result = i;	//e o ciclo atual se torna a melhor opcao
    }
  }
  cout << result << endl;
  return 0;
}
