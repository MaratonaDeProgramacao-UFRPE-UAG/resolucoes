#include<bits/stdc++.h>
using namespace std;
typedef long long int lli;
//https://www.geeksforgeeks.org/check-whether-a-given-point-lies-inside-a-triangle-or-not/
bool dentro(lli x1, lli y1, lli x2, lli y2, lli x3, lli y3, lli x, lli y){
  double area1, area2, area3, area4;
  area1 = abs((x1*(y2-y3) + x2*(y3-y1)+ x3*(y1-y2))/2.0); //calculando a area do triangulo maior, onde o ponto deve estar contido
	area2 = abs((x*(y2-y3) + x2*(y3-y)+ x3*(y-y2))/2.0); //calculando a area do triangulo formado por 2 pontos do triangulo maior e pelo ponto que estamos avaliando
	area3 = abs((x1*(y-y3) + x*(y3-y1)+ x3*(y1-y))/2.0); //calculando a area do triangulo formado por 2 pontos do triangulo maior e pelo ponto que estamos avaliando
	area4 = abs((x1*(y2-y) + x2*(y-y1)+ x*(y1-y2))/2.0); //calculando a area do triangulo formado por 2 pontos do triangulo maior e pelo ponto que estamos avaliando
	if(area1 == (area2+area3+area4)){ //se o ponto xy esta contido no triangulo formado pelos pontos x1,y1 x2,y2 e x3,y3
	  return true;
	}
	return false;
}
bool podeSerAdicionado(lli x1, lli x2, lli x3, lli y3, lli x4, lli y4){
	if(dentro(x1, 0, x2, 0, x3, y3, x4, y4) || dentro(x1, 0, x2, 0, x4, y4, x3, y3)){
		return true; //se o triangulo formado pela base e o ponto j atual e o triangulo formado pela base e o ponto i atual nao se interceptam
	}
	return false;
}
int main(){
  lli n, xa, xb, i, j, x, y, maior, max_qtdd;
  cin >> n >> xa >> xb;   //numero de pontos e coordenadas x da base dos triangulos
  set<lli> tri_dentro[n]; //array de conjuntos que guarda o conjunto de triangulos contido dentro do triangulo formado pela base e o i-esimo ponto
  multimap<lli, lli> pontos;  //mapa que guarda os pontos em formato (y,x)
  multimap<lli, lli>::iterator it;
  multimap<lli, lli>::reverse_iterator rit;
  for(i=0; i<n; i++){
    cin >> x >> y;
	  pontos.insert(make_pair(y, x)); //pontos guardados no formato (y,x) para o mapa deixa-los ordenados pelo valor de y
	}
	for(maior=0, i=0, it=pontos.begin(); it!=pontos.end(); it++, i++){  //percorrendo os pontos de 0 a n [i acompanha it]
	  rit=pontos.rbegin();
    advance(rit, pontos.size()-i-1);
	  for(max_qtdd=0, j=i; rit!=pontos.rend(); rit++, j--){    //percorrendo os pontos de i a 0 [j acompanha rit] //ja que o mapa eh ordenado por y, nao ha motivo para percorrer pontos acima do ponto i atual
	    if((dentro(xa, 0, xb, 0, (*it).second, (*it).first, (*rit).second, (*rit).first))){	//se o ponto j esta dentro do triangulo formado pela base e o ponto i
	      if(tri_dentro[j].size()+1 > max_qtdd) {
	      //se (quantidade de triangulos dentro de j)+1 é maior que a maior quantidade de triangulos que esta em i no momento
	      //a quantidade de triangulos em i se torma a (quantidade de triangulos em j) + (o proprio triangulo formado pelo ponto i)
	      //e essa se torna a maior quantidade de triangulos que esta em i no momento
          tri_dentro[i] = tri_dentro[j];  //colocando os pontos em j como pontos em i
          tri_dentro[i].insert(i);        //adicionando o ponto i
          max_qtdd = tri_dentro[i].size();//atualizando a maior quantidade de triangulos dentro de i
        }
		  }
	  }
	  if(tri_dentro[i].size() > maior){   //se a quantidade de triangulos dentro de i eh maior que a maior quantidade de triangulos dentro de outro triangulo ate agr
	    maior = tri_dentro[i].size();   //ela se torna a maior quantidade
		}
	}
	cout << maior << endl;
	return 0;
}
