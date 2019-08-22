#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio_ext.h>
#define TAM 8

typedef struct valor{
	int id;
}TpValor;

typedef struct nodo{
	TpValor valor;
	struct nodo *next;
} TpNodo;

typedef struct _lista{
	TpNodo *first;
} TpLista;

void push(TpLista *hash[]){
	int mod;
	TpNodo *novo = (TpNodo*)malloc(sizeof(TpNodo));
	printf("Digite um valor: ");
	scanf("%d", &novo->valor.id);
	printf("\n");
	mod = novo->valor.id % TAM; //posição em que valor será inserido
	if(hash[mod]->first == NULL){ //verificar se é o primeiro elemento da posição
		hash[mod]->first = novo;
		printf("\n---------------------------------------------------------------\n");
		printf("%dº Posição | Conjunto:\n", mod+1);
		printf("{%d}-> ", hash[mod]->first->valor.id);
		printf("\n---------------------------------------------------------------\n");
		return;
	}
	for(TpNodo *imp = hash[mod]->first; imp != NULL; imp = imp->next){ //for para percorrer a lista da posição mod
		if(imp->next == NULL){ //condição para inserir o valor em um espaço ainda não alocado
			imp->next = novo;
			printf("\n---------------------------------------------------------------\n");
			printf("%dº Posição | Conjunto:\n", mod+1);
			for(TpNodo *J = hash[mod]->first; J != NULL; J = J->next){
				printf("{%d}-> ", J->valor.id);
			}
			printf("\n---------------------------------------------------------------\n");
			printf("\n");
			return;
		}
	}
}

void busca(TpLista *hash[]){
	int opcao, valor, i = 0, aux;
	printf("Posição em que o conjunto se encontra: ");
	scanf("%d", &opcao);
	opcao -= 1;
	if(opcao > 7){
		printf("Contem apenas 7 posições\n");
		return;
	}
	printf("Digite o Elemento desejado: ");
	scanf("%d", &valor);
	for(TpNodo *B = hash[opcao]->first; B != NULL; B = B->next){ //for para percorrer a lista e encontrar o elemento
		if(B->valor.id == valor){
			aux = opcao + 1;
			printf("\n---------------------------------------------------------------\n");
			printf("Valor se encontra no %dº conjunto / %dº Elemento\n", aux, ++i);
			printf("Conjunto de Elementos:\n");
			for(TpNodo *J = hash[opcao]->first; J != NULL; J = J->next){
				printf("{%d}-> ", J->valor.id);
			}
			printf("\n---------------------------------------------------------------\n");
			return;
		}
		i++;
	}
	printf("Valor não encontrado...\n");
}

void tudo(TpLista *hash[]){
	int j, posicao = 1;
	for(j = 0; j < TAM; j++){
		if(hash[j] != NULL){
			printf("\n---------------------------------------------------------------\n");
			printf("%dº Conjunto:\n", posicao++);
			for(TpNodo *i = hash[j]->first; i != NULL; i = i->next){
				printf("[%d]-> ", i->valor.id);
			}
			printf("\n---------------------------------------------------------------\n");
		}
	}
}

void inicializa(TpLista *hash[]){ //função para alocar memória mata todas as posições do vetor
	for(int i = 0; i != TAM; i++){
		hash[i] = (TpLista*)malloc(sizeof(TpLista));
	}
}

int main(){
	int menu;
	TpLista *hash[TAM];
	inicializa(hash);
	do{
		printf("Pressione enter para continuar...\n");
		__fpurge(stdin);
		getchar();
		system("clear");
		printf("1-Inserir elemento:\n");
		printf("2-Buscar elemento:\n");
		printf("3-Elementos cadastrados:\n");
		printf("0-Encerrar\n");
		scanf("%d", &menu);
		switch(menu){
			case 1: push(hash); break;
			case 2: busca(hash); break;
			case 3: tudo(hash); break;
		}
	}while(menu);
	for(menu = 0; menu < 8; menu++){
		free(hash[menu]);
	}
	return 0;
}