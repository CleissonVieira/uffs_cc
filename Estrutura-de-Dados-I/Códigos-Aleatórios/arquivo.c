#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio_ext.h>

int i = 0;

typedef struct prod{
	int cod;
	char nome[50];
}produto;

typedef struct tfila{
	produto prod;
	struct tfila *prox;
}tp_fila;

tp_fila *push(tp_fila *fila){
	tp_fila *atual = (tp_fila*)malloc(sizeof(tp_fila));
	atual->prox = fila;
	i++;
	printf("Código do Produto: ");
	scanf("%d", &atual->prod.cod);
	__fpurge(stdin);
	printf("Nome do produto: ");
	fgets(atual->prod.nome, 50, stdin);
	return atual;
}

void printar(tp_fila *fila){
	if(fila == NULL){
		printf("pilha vazia...\n");
		return;
	}
	for( ; fila != NULL; fila = fila->prox){
		printf("CODIGO: ");
		printf("%d\n", fila->prod.cod);
		printf("NOME: ");
		printf("%s\n", fila->prod.nome);
	}
}

tp_fila *pop(tp_fila *fila){
	tp_fila *aux, *anterior = NULL;

	if(fila == NULL){
		printf("Pilha vazia..\n");
	}
	for( aux = fila ;aux != NULL; aux = aux->prox){
		if(i == 1){
			free(aux);
			i--;
			return anterior;
		}else if(aux->prox->prox == NULL){
			aux->prox = NULL;
			i--;
			return fila;
		}
	}
	return fila;
}

int main(){
	int menu;
	tp_fila *fila = NULL;
	do{
		printf("Pressione enter para continuar...\n");
		__fpurge(stdin);
		getchar();
		system("clear");
		printf("1-Inserir elemento:\n");
		printf("2-Extrair elemento:\n");
		printf("3-Estado da pilha:\n");
		printf("0-Encerrar\n");
		scanf("%d", &menu);
		switch(menu){
			case 1: fila = push(fila); break;
			case 2: fila = pop(fila); break;
			case 3: printar(fila); break;
		}
	}while(menu);
	free(fila);
	return 0;
}