#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MX 1000

void calculaDistancia(int tam, char vert[], char vAnt[]){
    int fim = 0;
    printf("\n\n| Menor  caminho |");
    for(int t = (tam - 1); ; ){
        for(int e = 0; e < tam; e++){
            if(vAnt[t] == vert[e]){
                printf(" %c  <- ", vert[t]);
                t = e;
            }else if(vAnt[t] == '/'){
                printf("%c |", vert[t]);
                fim = 1;
                break;
            }
        }
        if(fim == 1)
            break;
    }
}

void bfs(int matriz[21][21], char vert[], int dist[], char vAnt[], char cor[]){
    int atingido = 0, distancia = 1, fim = 0;
    for(int i = 0; i < 21; i++){
        cor[i] = 'p';
        for(int j = 0; j < 21; j++){
            if(matriz[i][j] == 1){
                if(atingido == 0 && i != 0){
                    vAnt[i] = vert[j];
                    atingido = 1;
                }if(cor[j] == 'b')
                    cor[j] = 'c';
                if(j != 0 && dist[j] == 0)
                    dist[j] = distancia;
            }
        }
        distancia ++;
        atingido = 0;
    }
    printf("\n\n| Vertice atual  | A | B | C | D | E | F | G | H | I | J | K | L | M | N | O | P | Q | R | S | T | Z |");
    printf("\n|   Distancia    |");
    for(int y = 0; y < 21; y ++){
            if(y < 12)
                printf(" %d |", dist[y]);
            else
                printf(" %d|", dist[y]);
    }
    printf("\n|Vertice anterior|");
    for(int l = 0; l < 21; l ++)
        printf(" %c |", vAnt[l]);
    printf("\n| Cor do vertice |");
    for(int x = 0; x < 21; x ++)
        printf(" %c |", cor[x]);
    calculaDistancia(21, vert, vAnt);
}

void dijkstra(int matriz[7][7], char Vert[], int Dist[], char vAnt[]){
    int menor;
    for(int i = 0; i < 7; i++){
        for(int j = 0; j < 7; j++){
            if(i == 0){ //Primeira parte para preencher os que A liga
                menor = matriz[i][j];
                if(menor < Dist[j] && menor != 0){
                    Dist[j] = menor;
                    vAnt[j] = Vert[i];
                }
            }else{
                for(int j = i; j < 7; j++){
                    menor = matriz[i][j];
                    if(menor != 0){
                        menor += Dist[i];
                        if(menor < Dist[j]){
                            Dist[j] = menor;
                            vAnt[j] = Vert[i];
                        }
                    }
                }
            }
        }
    }
    printf("\n\n|-Vertice atual--| A | B | C | D | E | F | G |");
    printf("\n|----Distancia---|");
    for(int x = 0; x < 7; x ++){
        if(Dist[x] < 10){
            printf(" %d |", Dist[x]);
        }else{
            printf(" %d|", Dist[x]);
        }
    }
    printf("\n|Vertice anterior|");
    for(int y = 0; y < 7; y ++){
        printf(" %c |", vAnt[y]);
    }
    printf("\n\n|   Comprimento  | %d |", Dist[6]);
    calculaDistancia(7, Vert, vAnt);
}

main(int argc, char const *argv[]){
    int matrizAdjacencia1[21][21] = {
    //   A B C D E F G H I J K L M N O P Q R S T Z
    /*A*/0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,
    /*B*/1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    /*C*/0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    /*D*/0,1,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,
    /*E*/0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    /*F*/0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,
    /*G*/0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,
    /*H*/0,0,0,0,0,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,
    /*I*/0,0,0,0,0,0,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,
    /*J*/0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1,
    /*K*/1,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,
    /*L*/0,0,0,1,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,
    /*M*/0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,
    /*N*/0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,
    /*O*/0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,0,1,0,0,0,
    /*P*/0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,
    /*Q*/0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,1,0,
    /*R*/0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,
    /*S*/0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,
    /*T*/0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,
    /*Z*/0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,1,0
    };
    char vert[21] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','Z'};
    int dist[21] =  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 };
    char vAnt[21] = {'/','/','/','/','/','/','/','/','/','/','/','/','/','/','/','/','/','/','/','/','/',};
    char cor[21] =  {'b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b'};
    int l , x;
    int matrizAdjacencia2[7][7] = {
        //    A B C D E F G
        /*A*/ 0,7,0,5,0,0,0,
        /*B*/ 7,0,8,9,7,0,0,
        /*C*/ 0,8,0,0,5,0,0,
        /*D*/ 5,9,0,0,15,6,0,
        /*E*/ 0,7,5,15,0,8,9,
        /*F*/ 0,0,0,6,8,0,11,
        /*G*/ 0,0,0,0,9,11,0
    };
    char vertice[7] =   {'A','B','C','D','E','F','G'};
    int distancia[7] =  { 0, MX, MX, MX, MX, MX, MX};
    char vAnterior[7] = {'/','0','0','0','0','0','0'};
    int menu;
	do{
		printf("\n\nPressione enter para continuar...\n");
		fflush(stdin);
		getchar();
		system("cls");
		printf("1 - Busca em largura (BFS):\n");
		printf("2 - Encontrar comprimento do caminha mais curto (Dijkstra):\n");
		printf("0 - Encerrar\n");
		printf("\n--->");
		scanf("%d", &menu);
		switch(menu){
			case 1: bfs(matrizAdjacencia1, vert, dist, vAnt, cor); break;
			case 2: dijkstra(matrizAdjacencia2, vertice, distancia, vAnterior); break;
		}
	}while(menu);
    return 0;
}