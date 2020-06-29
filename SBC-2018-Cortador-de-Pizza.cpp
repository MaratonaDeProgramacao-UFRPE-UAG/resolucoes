#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
#define par pair<lli, lli>
bool ordenar(par a, par b){
    if(a.first < b.first){
        return true;
    }
    if(a.first == b.first){
        if(a.second < b.second){
            return true;
        }
    }
    return false;
}
//https://www.geeksforgeeks.org/counting-inversions/
//funcao que faz o merge de dois arrays ordenados e retorna a qtdd de inversoes neles
lli merge(par arr[], par temp[], lli esq, lli meio, lli dir){
    lli i, j, k;
    lli inversoes = 0;
    i = esq;    //indice para o subarray esquerdo
    j = meio;   //indice para o subarray direito
    k = esq;    //indice para o subarray resultante
    while((i <= meio - 1) && (j <= dir)){
        if(arr[i].second <= arr[j].second){
            temp[k++].second = arr[i++].second;
        }
        else{
            temp[k++].second = arr[j++].second;
            inversoes = inversoes + (meio - i);
        }
    }
    while(i <= meio-1){  //copiar os elementos restantes do subarray esquerdo p/ temp
        temp[k++].second = arr[i++].second;
    }
    while(j <= dir){   //copiar os elementos restantes do subarray direito p/ temp
        temp[k++].second = arr[j++].second;
    }
    for(i = esq; i <= dir; i++){   //copiar os elementos apos o merge de volta p/ o array original
        arr[i].second = temp[i].second;
    }
    return inversoes;
}
//funcao auxiliar recursiva p/ ordenar o array e retornar o numero de inversoes nele
lli _mergeSort(par arr[], par temp[], lli esq, lli dir){
    lli meio, inversoes;
    inversoes = 0;
    if(dir > esq){ //dividir o array em 2 partes e  chamar _mergeSort() p/ as duas
        meio = (dir + esq)/2;
        inversoes += _mergeSort(arr, temp, esq, meio);  //a qtdd de inversoes eh a soma das inversoes do lado direito, do lado esquerdo e as inversoes obtidas ao juntar as partes
        inversoes += _mergeSort(arr, temp, meio + 1, dir);
        inversoes += merge(arr, temp, esq, meio + 1, dir);  //juntar as 2 partes
    }
    return inversoes;
}
//funcao que ordena o array e retorna o numero de inversoes nele
lli mergeSort(par arr[], lli tam){
    par temp[tam];
    return _mergeSort(arr, temp, 0, tam-1);
}
int main(){
    lli x, y, h, v, i, j, a, b, total;
    cin >> x >> y;
    cin >> h >> v;
    par horizontais[h];
    par verticais[v];
    for(i=0; i<h; i++){ //lendo os cortes horizontais e guardando como pares de pontos (apenas o valor y)
        cin >> a >> b;
        horizontais[i] = make_pair(a,b);
    }
    for(i=0; i<v; i++){ //lendo os cortes verticais e guardando como pares de pontos (apenas o valor x)
        cin >> a >> b;
        verticais[i] = make_pair(a,b);
    }
    sort(horizontais, horizontais+h, ordenar);  //ordenando os pares de pontos pelo valor de y do primeiro (e se forem iguais, pelo do segundo)
    sort(verticais, verticais+v, ordenar);      //ordenando os pares de pontos pelo valor de x do primeiro (e se forem iguais, pelo do segundo)
    //como o array de cortes horizontais esta ordenado pela altura inicial do corte, basta verificar se a altura final do corte atual
    //eh menor que a altura final do corte anterior, se sim, eles se interceptam
    //fazemos essa conta usando um mergeSort para contar as inversoes nos pontos finais (dos cortes verticais e horizontais)
    //2 elementos a[i] e a[j] formam uma inversao se a[i] > a[j] e i < j
    //adicionamos 2 ao total pq o primeiro corte gera 2 fatias e adicionamos v*h ao total pq cada corte vertical intercepta todos os horizontais
    total = 2 + mergeSort(horizontais, h);      //usando mergeSort para contar quantas intersecoes ha entre os cortes horizontais (inversoes)
    total += (v*h) + mergeSort(verticais, v);   //usando mergeSort para contar quantas intersecoes ha entre os cortes verticais (inversoes)
    //a adicao abaixo ocorre por uma propriedade que diz que ao adicionar uma nova linha num plano o numero de cortes que ela adiciona ao plano eh
    //(numero de intersecoes)+1 (https://www.cut-the-knot.org/proofs/LinesDividePlane.shtml)
    total += h+v-1; //adicionando "1" para cada corte feito (exceto o primeiro porque ja adicionamos o "2" dele antes)
    cout << total << endl;
    return 0;
}
