#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 100

typedef struct produto{
	int codigo;
	char nome[TAM];
	float preco;
}tp_produto;

typedef struct nodo{
	tp_produto produto;
	struct nodo *prox;
}tp_nodo;

tp_nodo *push(tp_nodo *v){
	tp_nodo *u = (tp_nodo*)malloc(sizeof(tp_nodo));
	u->prox = v;
	printf("Código do Produto: ");
	scanf("%d", &u->produto.codigo);
	__fpurge(stdin);
	printf("Nome do produto: ");
	fgets(u->produto.nome, TAM, stdin);
	printf("Preço do produto: ");
	scanf("%f", &u->produto.preco);
	__fpurge(stdin);
	return u;
}

void mostraProdutos(tp_nodo *v){
	int i=0;
	if(v == NULL){
		printf("Não há produtos cadastrados...\n");
	}else{
		for(; v != NULL; v = v->prox, i++){
			printf("---------------------------------------------------------------\n");
			printf("|Dados do produto %d|\n", i+1);
			printf("Codigo: %d\n", v->produto.codigo);
			printf("Nome: %s", v->produto.nome);
			printf("Preço R$: %0.2f\n\n", v->produto.preco);
		}
	}
}

tp_nodo *pop(tp_nodo *u) {
	int cod, i;
	tp_nodo *v, *anterior;
	
	if(u == NULL){
		printf("Não há produtos cadastrados...\n");
		return v;
	}
	printf("Codigo do produto:\n");
	scanf("%d", &cod);
	for(v = u; v != NULL; v = v->prox){
		if(v->produto.codigo == cod){
			break;
		}
		anterior = v;
	}
	if(v == NULL){
		printf("Não encontrado\n");
	}
	else if(v == u){
		free(u);
		u = u->prox;
	}
	else{
		free(anterior->prox);
		anterior->prox = v->prox;
	}
	return u;
}

int main(){
	int menu;
	tp_nodo *v = NULL;
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
			case 1: v = push(v); break;
			case 2: v = pop(v); break;
			case 3: mostraProdutos(v); break;
		}
	}while(menu);
	free(v);
	return 0;
}