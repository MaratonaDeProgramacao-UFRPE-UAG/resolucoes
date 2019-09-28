#include <iostream>
#include <map>
using namespace std;

typedef struct plano{
  int a, b, c, d;     			//coeficientes da equacao do plano
}plano;

int main(){
  int n_planos, n_planetas, maior, i, j, x, y, z;	//x y e z armazenam as coordenadas dos planetas
  string secao_atual;					//string para armazenar a secao do planeta atual
  map<string,int> secoes;				//criando um mapa de secoes onde a chave eh um numero binario que representa quais planos estao abaixo e acima da secao e o valor eh a quantidade de planetas nessa secao
  map<string,int>::iterator secao;
  plano planos[500];					//vetor dos planos
  cin >> n_planos >> n_planetas;
  for(i=0; i < n_planos; i++){
    cin >> planos[i].a >> planos[i].b >> planos[i].c >> planos[i].d;		//lendo os coeficientes dos planos e armazenando no vetor
  }
  maior = 1;				//como sabemos que há pelo menos um planeta, iniciamos o valor maximo de planetas em uma secao com 1
  for(i=0; i < n_planetas; i++){
    secao_atual = "";
    cin >> x >> y >> z;			//lendo coordenadas do planeta
    for(j=0; j < n_planos; j++){
      if((planos[j].a*x + planos[j].b*y + planos[j].c*z) > planos[j].d){	//se o planeta esta acima do plano atual
        secao_atual += '1';		//adicionar '1' à string da secao atual
      }
      else{
        secao_atual += '0';		//caso contrario adicionar '0' à string da secao atual
      }
    }
    secao = secoes.find(secao_atual);
    if(secao != secoes.end()){		//se a secao do planeta atual ja esta no vetor de secoes
      secao->second += 1;		//adicionar um planeta a ela
      if(secao->second > maior){	//se essa secao tem mais planetas que a secao com o maximo de planetas, esse eh o novo maximo
        maior = secao->second;
      }
    }
    else{
      secoes[secao_atual] = 1;		//caso a secao n esteja no vetor, colocar ela no vetor e inicializar com 1 planeta
    }
  }
  cout << maior << endl;
  return 0;
}
