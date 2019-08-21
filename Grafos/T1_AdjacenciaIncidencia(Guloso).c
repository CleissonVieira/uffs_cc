#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//Adjacencia2
#define verticeA 7
#define arestaA 7
//Incidencia2
#define verticeI 7
#define arestaI 9
//Adjacencia1
#define verticeB 5
#define arestaB 5
//Incidencia1
#define verticeJ 5
#define arestaJ 8


int encontraMenor(int matrizAdjacencia1[verticeB][arestaB], int linha){
    int menorV = 0, menorP = -1, j;
    for(j = 0; j < arestaB; j++){
        if((menorV == 0 && matrizAdjacencia1[linha][j] > 0) || (matrizAdjacencia1[linha][j] > 0 && matrizAdjacencia1[linha][j] < menorV)){
            menorV = matrizAdjacencia1[linha][j];
            menorP = j;
        }
    }
    return menorP;
}

void limparColuna(int matrizAdjacencia1[verticeB][arestaB], int coluna){
    int i;
    for(i = 0; i < verticeB; i++){
        matrizAdjacencia1[i][coluna] = 0;
    }
}

void limparLinha(int matrizAdjacencia1[verticeB][arestaB], int linha){
    int j;
    printf("AAA1\n");
    for(j = 0; j < verticeB; j++){
        if(matrizAdjacencia1[linha][j]>0){
            printf("%d\n",matrizAdjacencia1[linha][j]);
            matrizAdjacencia1[linha][j] = 0;
            printf("%d\n",matrizAdjacencia1[linha][j]);
        
        }
    printf("AAA2\n");    
    }
    printf("AAA\n");
}

void adjacencia1(int matrizAdjacencia1[verticeB][arestaB]){
    int soma = 0, menorP = 0, linha = 0;
    do{
        menorP = encontraMenor(matrizAdjacencia1, linha);
        if(menorP != -1){
            printf("Linha: %d || Coluna: %d --> Valor: %d\n", linha+1, menorP+1, matrizAdjacencia1[linha][menorP]);
            soma += matrizAdjacencia1[linha][menorP];
            limparColuna(matrizAdjacencia1, menorP);
            linha = menorP;
        }

    } while (menorP != -1);
    printf("Total = %d\n", soma);
}

void Incidencia1(int matrizIncidencia1[verticeJ][arestaJ]){
    int soma = 0, menorP = 0, linha = 0, inverso = 0, i;
    do{
        menorP = encontraMenor(matrizIncidencia1, linha);
        if(menorP != -1){
            soma += matrizIncidencia1[linha][menorP];
            inverso = matrizIncidencia1[linha][menorP] * (-1);
            printf("Linha: %d || Coluna: %d --> Valor: %d\n", linha+1, menorP+1, matrizIncidencia1[linha][menorP]);
            limparLinha(matrizIncidencia1, linha);
            for(i = 0; i < verticeJ; i++){
                if(inverso == matrizIncidencia1[i][menorP]){
                    linha = i;
                    break;
                }
            }
        }
    } while (menorP != -1);
    printf("Total = %d\n", soma);
}

void adjacencia2(int matrizAdjacencia2[verticeA][arestaA]){
    int i = 0, j, menor[] = {0, 0};
    for(i = 0; i < verticeA; ){
        j = 0;
        menor[0] = matrizAdjacencia2[i][j];
        for(j = 1; j < arestaA; j++){
            if(j < arestaA){
                if(menor[0] > 0 && menor[0] > matrizAdjacencia2[i][j] && matrizAdjacencia2[i][j] != 0){
                    menor[0] = matrizAdjacencia2[i][j];
                    menor[1] = j;
                }else if(menor[0] == 0){
                    menor[0] = matrizAdjacencia2[i][j];
                    menor[1] = j;
                }
            }
        }
        if(i == 6 && menor[0] == 0){
            printf("Vertice: %d || Aresta: %d  <--- MENOR CAMINHO ENCONTRADO\n", (i+1), menor[0]);
            break;
        }
        printf("Vertice: %d || Aresta: %d\n", (i+1), menor[0]);
        i = menor[1];
    }
}

void incidencia2(int matrizIncidencia2[verticeI][arestaI]){
    int i, j, k, q, menor[] = {0, 0};
    for(i = 0; i < verticeI; ){
        j = 0;
        menor[0] = matrizIncidencia2[i][j];
        for(j = 1; j < arestaI; j++){
            if(j < arestaI){
                if(menor[0] <= 0){
                    menor[0] = matrizIncidencia2[i][j];
                    menor[1] = i;
                }else if(menor[0] > 0 && menor[0] > matrizIncidencia2[i][j] && matrizIncidencia2[i][j] != 0){
                    menor[0] = matrizIncidencia2[i][j];
                    menor[1] = i;
                }
            }
        }
        for(k = 0; k < verticeI; k++){
            for(q = 0; q < arestaI; q++){
                if(menor[0] * -1 == matrizIncidencia2[k][q] && menor[0] >= 0){
                    printf("Vertice: %d || Aresta: %d\n", (i+1), menor[0]);
                    i = k;
                }
            }
        }
        if(menor[0] <= 0){
            printf("Vertice: %d || Aresta: %d  <--- MENOR CAMINHO ENCONTRADO\n", (i+1), menor[0]);
            break;
        }
    }
}

int main(){
    //Caminho mais curto para percorrer todos os vértices
    int matrizAdjacencia1[5][5]={
        //    a1  b2  c3  d4  e5 (aresta)
        /*1*/ 0,  30,-15, 0,  20,
        /*2*/-30, 0, -10, 50, 0,
        /*3*/ 15, 10, 0,  5, -10,
        /*4*/ 0,  50,-5,  0, -30,
        /*5*/-20, 0,  10, 30, 0
        //(vértice)
    };
    //Caminho mais curto para percorrer todos os vértices
    int matrizIncidencia1[5][9]={
        //    a1  b2  c3  d4  e5  f6  g7  h8  i9 (aresta)
        /*1*/ 20,-15, 30, 0,  0,  0,  0,  0,
        /*2*/ 0,  0, -30, 0, -10, 0,  0,  50,
        /*3*/ 0,  15, 0, -10, 10, 0,  5,  0,
        /*4*/ 0,  0,  0,  0,  0, -30,-5,  50 ,
        /*5*/-20, 0,  0,  10, 0,  30, 0,  0
        //(vértice)
    };

    //Caminho mais curto de x até y
    int matrizAdjacencia2[7][7]={
        //   a1 b2 c3 d4 e5 f6 g7 (aresta)
        /*1*/0, 2, 0, 6, 12,0, 0,
        /*2*/0, 0, 7, 0, 0, 5, 0,
        /*3*/0, 0, 0, 0, 0, 0, 40,
        /*4*/0, 0, 0, 0, 0, 8, 0,
        /*5*/0, 0, 0, 0, 0, 0, 30,
        /*6*/0, 0, 0, 0, 0, 0, 8,
        /*7*/0, 0, 0, 0, 0, 0, 0
        //(vértice)
    };
    //Caminho mais curto de x até y
    int matrizIncidencia2[7][9]={
        //    a1  b2  c3  d4  e5  f6  g7  h8  i9(aresta)
        /*1*/ 2,  6,  12, 0,  0,  0,  0,  0,  0,
        /*2*/-2,  0,  0,  7,  5,  0,  0,  0,  0,
        /*3*/ 0,  0,  0, -7,  0,  40, 0,  0,  0,
        /*4*/ 0, -6,  0,  0,  0,  0,  4,  0,  0,
        /*5*/ 0,  0, -12, 0,  0,  0,  0,  30, 0,
        /*6*/ 0,  0,  0,  0, -5,  0, -4,  0,  8,
        /*7*/ 0,  0,  0,  0,  0, -40, 0, -30,-8
        //(vértice)
    };

    int menu;
	do{
		printf("Pressione enter para continuar...\n");
		fflush(stdin);
		getchar();
		system("cls");
		printf("1 - Adjacencia (caminho mais curto de x ate y):\n");
		printf("2 - Incidencia (caminho mais curto de x ate y):\n");
		printf("3 - Adjacencia (caminho mais curto percorrendo todos os vertices):\n");
		printf("4 - Incidencia (caminho mais curto percorrendo todos os vertices):\n");
		printf("0 - Encerrar\n");
		printf("\n--->");
		scanf("%d", &menu);
		switch(menu){
			case 1: adjacencia2(matrizAdjacencia2); break;
			case 2: incidencia2(matrizIncidencia2); break;
			case 3: adjacencia1(matrizAdjacencia1); break;
			case 4: Incidencia1(matrizIncidencia1); break;
		}
	}while(menu);
    return 0;
}
