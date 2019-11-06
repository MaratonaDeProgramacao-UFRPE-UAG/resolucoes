#include<bits/stdc++.h> 
using namespace std; 

void addAresta(vector<pair<int,int>> adj[], int u, int v,int peso) 
{ 
    //Se fosse dirigido, só iria adicionar em um sentido
    adj[u].push_back(make_pair(v,peso));//lista de U
    adj[v].push_back(make_pair(u,peso)); //lista de V
} 
void printGrafo(vector<pair<int,int> > adj[], int V) 
{ 
    int v, w; 
    for (int u = 0; u < V; u++) 
    { 
        cout << "No " << u+1 << " tem aresta com \n"; 
        for (auto it = adj[u].begin(); it!=adj[u].end(); it++) 
        { 
            v = it->first; 
            w = it->second; 
            cout << "\tNo " << v+1 << " com peso ="
                 << w << "\n"; 
        } 
        cout << "\n"; 
    } 
}   

int Djikstra(vector<pair<int,int>> adj[],int origem, int destino,int N){
    vector<int> distancia(N,100000000);
    vector<int> visitados(N,false);
    priority_queue <pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> fila;

    distancia[origem] = 0;//distancia da origem pra ela mesma
    fila.push(make_pair(distancia[origem],origem));//insere na fila o par com a distancia e o vertice
    
    while(!fila.empty()){
        
        pair<int,int> topo = fila.top();
        int vertice = topo.second;
        fila.pop();

        if(visitados[vertice]==false){
            visitados[vertice] = true;

            //verifica os adjacentes
            for(auto cursor = adj[vertice].begin();cursor != adj[vertice].end();cursor++ ){
                int adjacente = cursor->first;
                int custo = cursor->second;

                if(distancia[adjacente] > (distancia[vertice] + custo)){//relaxamento
                    distancia[adjacente] = distancia[vertice] + custo;
                    fila.push(make_pair(distancia[adjacente],adjacente));
                }
            }
        }
    }
    return distancia[destino];
}

int main() 
{

    int c,v;
    cin >> c >> v;
    vector<bool> visitado;
    vector<pair<int,int>> adj[c];
    vector<pair<int,int>> grafo_par[c];

    for(int i = 0;i<v;i++){//num arestas
        int v,u,custo;

        cin >> v >> u >> custo;

        addAresta(adj,v-1,u-1,custo);//vertice 1 == int 0

    }
    
    //printGrafo(adj,v);
    vector<pair<int,int>>::iterator cursor;
    vector<pair<int,int>>::iterator cursor2;
    for(int i = 0; i < c; i++){    
        for(cursor = adj[i].begin(); cursor != adj[i].end();cursor++){//cada vertice adjacente ao vertice i
            int num_ver = cursor->first;
            int peso = cursor->second;
            
            for(cursor2 = adj[num_ver].begin();cursor2 != adj[num_ver].end();cursor2++){//adjacente do adjacente
                int num_ver2 = cursor2->first;
                int peso2 = cursor2->second;

                addAresta(grafo_par,i,num_ver2,peso + peso2);//adiciona so caminhos pares
            }    
        }
    }
  
    int custo_minimo_par = Djikstra(grafo_par,0,c-1,c);

    if(custo_minimo_par == 100000000){//nao achou caminho
        cout << -1 << endl;
    }else{
        cout << custo_minimo_par << endl;
    }
    
    
    return 0; 
} 