#include <bits/stdc++.h>
#include <stdio.h> 
#include <limits.h> 
#include <stdbool.h>

/*KRUSKAL***********************************************************************************************************/
using namespace std;

typedef  pair<int, int> iPar;

struct Grafo  {
    int V1, V2;
    vector< pair<int, iPar> > arestas; //cria vetor de arestas
    Grafo(int V1, int V2){ //grafo com os vértices e menor custo
        this->V1 = V1;
        this->V2 = V2;
    }
    void addAresta(int v1, int v2, int a){
        arestas.push_back({a, {v1, v2}});
    }
    int kruskal();
};

struct conjuntosSep {
    int *pai, *rank;
    int n;
    conjuntosSep(int n){
        this->n = n;
        pai = new int[n+1];
        rank = new int[n+1];
        for (int i = 0; i <= n; i++){ //iniciar vértices que estão em sets diferentes e rank = 0
            rank[i] = 0;
            pai[i] = i;
        }
    }
    int encontra(int u){    // Encontre o pai de um nó 'u'
        if(u != pai[u]){
            pai[u] = encontra(pai[u]);
        }
        return pai[u];
    }
    void unirR(int x, int y){
        x = encontra(x), y = encontra(y);
        if(rank[x] > rank[y]){
            pai[y] = x;
        }else{ // se rank[x] <= rank[y]
            pai[x] = y;
        }if(rank[x] == rank[y]){
            rank[y]++;
        }
    }
};

int Grafo::kruskal(){
    int custo = 0;
    sort(arestas.begin(), arestas.end()); //Ordenar as arestas do vetor arestas[]
    conjuntosSep conjP(V1); // Cria conjuntos próprios
    vector< pair<int, iPar> >::iterator i; 
    for (i = arestas.begin(); i != arestas.end(); i++){ //pescorre todas as arestas do vetor arestas[]
        int u = i->second.first;
        int v = i->second.second;
        int set_u = conjP.encontra(u);
        int set_v = conjP.encontra(v);
        if (set_u != set_v){    //verificar se Vértices estão em árvores diferentes para não ocorrer ciclos
            cout << "(" << u << "," << v << ") "; //aresta atual será menor então imprime J
            custo += i->first; //Atualiza peso total
            conjP.unirR(set_u, set_v); //Junta u e v
        }
    }
    return custo;
}

void KRUSKAL(){
    int V1 = 8, V2 = 8;
    Grafo G(V1, V2);
    G.addAresta(0, 1, 3);
    G.addAresta(0, 3, 3);
    G.addAresta(0, 2, 4);
    G.addAresta(1, 0, 3);
    G.addAresta(2, 0, 4);
    G.addAresta(2, 4, 8);
    G.addAresta(3, 0, 3);
    G.addAresta(3, 5, 8);
    G.addAresta(4, 2, 8);
    G.addAresta(4, 6, 7);
    G.addAresta(4, 7, 7);
    G.addAresta(5, 3, 8);
    G.addAresta(5, 2, 8);
    G.addAresta(5, 7, 7);
    G.addAresta(5, 6, 4);
    G.addAresta(6, 4, 7);
    G.addAresta(6, 5, 4);
    G.addAresta(6, 7, 2);
    G.addAresta(7, 4, 7);
    G.addAresta(7, 5, 7);
    G.addAresta(7, 6, 2);
    cout << "\nArvore Geradora Minima: ";
    int CustoTotal = G.kruskal();
    cout << "\n\nCusto Total: " << CustoTotal;
}

/*PRIM***********************************************************************************************************/

int menor(int dist[], bool visitados[]){ 
    int min = INT_MAX, min_index; //Inicia como o minimo valor
    for (int v = 0; v < 8; v++){
        if (visitados[v] == false && dist[v] < min){
            min = dist[v], min_index = v;
        } 
    }
    return min_index; 
} 

int print(int vAnt[], int n, int grafo[8][8]){ 
    cout << "Ant|V|Peso\n"; 
    for (int i = 1; i < 8; i++) 
        printf("%d - %d \t%d \n", vAnt[i], i, grafo[i][vAnt[i]]); 
} 

void PRIM(int grafo[8][8]){
	int vAnt[8]; 
    int dist[8];   
    bool visitados[8]; 
    int i, count;
    for (i = 0; i < 8; i++){ // distância infinita
        dist[i] = INT_MAX, visitados[i] = false; 
    }
    dist[0] = 0;     
    vAnt[0] = -1;
    for (count = 0; count < 7; count++){ 
        int w = menor(dist, visitados); //Menor distância entre vértices
        visitados[w] = true;    
        for (int j = 0; j < 8; j++){
            if (grafo[w][j] && visitados[j] == false && grafo[w][j] < dist[j]){
                vAnt[j] = w, dist[j] = grafo[w][j];
            }  
        }      
    } 
    cout << "\nVert | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |";
	cout << "\nDist |";
    count = 0;
	for(int i = 0; i < 8; i++){
		printf(" %d |", dist[i]);
        count += dist[i];
	}
	cout << "\nAnt |";
	for(int i = 0; i < 8; i++){
		printf(" %d |", vAnt[i]);
	}
    cout << "\n\nCusto Total: " << count;
}

int main(){
    int matrizAdjacenciaB[8][8] = {
        //      0 1 2 3 4 5 6 7
        /*0*/   0,2,0,6,5,0,0,0,
        /*1*/   2,0,7,7,0,0,0,0,
        /*2*/   0,7,0,0,6,2,0,0,
        /*3*/   6,7,0,0,0,0,0,0,
        /*4*/   5,0,6,0,0,0,4,5,
        /*5*/   0,0,2,0,0,0,4,6,
        /*6*/   0,0,0,0,4,4,0,1,
        /*7*/   0,0,0,0,5,6,1,0
    };
    int menu;
    do{
		cout << "\n\nPressione enter para continuar...\n";
		fflush(stdin);
		getchar();
		system("cls");
		cout << "1 - PRIM:\n";
		cout << "2 - KRUSKAL:\n";
		cout << "0 - Encerrar\n";
		cout << "\n--->";
		scanf("%d", &menu);
		switch(menu){
			case 1: PRIM(matrizAdjacenciaB); break;
			case 2: KRUSKAL(); break;
		}
	}while(menu);
    return 0;
}