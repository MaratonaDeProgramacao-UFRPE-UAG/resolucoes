#include<bits/stdc++.h>
using namespace std;
long long int maxSomaSubArray(long long int a[], long long int tam, long long int custo){
  long long int maior, maior_atual, fim, i, lucro;
	for(i=0, fim=0, maior_atual=0, maior=0, lucro=0; i<tam; i++){ //procurando a maior soma de um subarray de b
		maior_atual += a[i];
		if(maior < maior_atual){ //se a soma atual eh a maior encontrada ate agora
			maior = maior_atual; //ela se torna a maior
			fim = i;
		}
		if(maior<custo && maior_atual<0){	//se nao encontramos nenhum valor util ainda e o valor atual eh negativo
			maior_atual = maior = 0;
		}
		if(custo+(maior_atual-maior)<=0 || i==tam-1){ //se nesse dia a sequencia de queda eh maior que o custo de comprar novamente ou chegamos ao fim
			if(maior>custo){ //e se a maior soma encontrado ate agora eh maior que o custo de compra
				lucro += (maior-custo); //adicionamos a maior soma encontrada ao lucro (removendo o custo de compra)
				i = fim; //começamos novamente a partir do dia seguinte
			}
			maior_atual = maior = 0;
		}
	}
  return lucro;
}
int main(){
	long long int n, c, i, ant, atual;
	cin >> n >> c;
	long long int cot[n];
	for(i=0; i<n; i++){
		cin >> atual;
		if(i>=1){
			cot[i-1] = atual-ant; //criando um array b com as diferenças de cotações entre os dias
		}
		ant = atual;
	}
	cout << maxSomaSubArray(cot, n-1, c) << endl;
	return 0;
}
