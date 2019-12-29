#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int main(){
  long int n, i, j, k;
  int intervalo[7] = {2,4,5,7,9,11,12};
  bool valida = false;
  string nomes[12] = {"do", "do#", "re", "re#", "mi", "fa", "fa#", "sol", "sol#", "la", "la#", "si"};
  vector<int> notas_validas(7);
  cin >> n;
  int notas[n];
  for(i=0; i<n; i++){				//lendo as notas da musica
    cin >> notas[i];
    notas[i] = notas[i]%12;
  }
  for(k=1; k<=12 && !valida; k++){	//verificando para cada escala possivel
    notas_validas.clear();
    for(j=0; j<7; j++){				//preenchendo a nova colecao de notas validas para a escala atual
      notas_validas.push_back((k+intervalo[j])%12);
    }
    for(i=0; i<n; i++){				//verificando se a musica esta nessa escala
      if(find(notas_validas.begin(), notas_validas.end(), notas[i]) == notas_validas.end()){
        break;
      }
      else{
        if(i == n-1){
          valida = true;
        }
      }
    }
  }
  if(valida == true){
    cout << nomes[k-2] << endl;
  }
  else{
    cout << "desafinado" << endl;
  }
  return 0;
}
