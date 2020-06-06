// Questao Resolvida por Kelwin Jonas


#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    long long int x, y;
    vector<pair<long long int, long long int> > pontos;

	cin >> n;

	for (int k = 0 ; k < n ; k++){
		cin >> x >> y;
		pontos.push_back(make_pair(x, y));
	}

	int cont = 0;
	sort(pontos.begin(), pontos.end());

	for (int k = 0 ; k < n ; k++){
	    long long int direita, esquerda;
	    direita = 100000001;
	    esquerda = -100000001;
		pair<long long int, long long int> &atual = pontos[k];

		for (int i = k+1; i < n ; i++){
			pair<long long int , long long int > &proximo = pontos[i];

			if (proximo.second > atual.second && proximo.second < direita){//se a coordenada y do ponto proximo for maior que a coordenada y do atual, talvez possa formar uma praça ali
				direita = proximo.second;                                   //a praça será formada se caso a coordenada y do ponto proximo for menor que aquela já formada anteriormente
				cont += 1;
			}
			else if (proximo.second < atual.second && proximo.second > esquerda){//se a coordenada y do ponto proximo for menor que a coordenada y do atual, e essa coordenada y for
				esquerda = proximo.second;                                      //maior que aquele já encontrada
				cont += 1;
			}//atualizando esquerda e direita, impedimos que praças com sejam formadas com postes dentro delas
		}
	}
	//Fiz em python mas deu time limit. Talvez a função sort de python seja muito lenta comparada ao sort de c++, mesmo a entrada máxima sendo
	//de 3000. Acho 3000 muito pouco ainda assim para dar time limit. Ninguém conseguiu passar com esta questão em python no ranking do URI
	cout << cont << endl;
}
