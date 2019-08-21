#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _produto{
	int codigo;
	char nome[20];
	float preco;
} TpProduto;

typedef struct _nodo{
	TpProduto info;
	struct _nodo *next;
	struct _nodo *prev;
} TpNodo;

typedef struct _lista{
	int nItens;
	TpNodo *first;
	TpNodo *last;
} TpLista;

TpLista *push(TpLista *cabeca){
	int menu;
	TpNodo *atual = (TpNodo*)malloc(sizeof(TpNodo));
	if(cabeca->nItens == 0){
		printf("Código do Produto: ");
		scanf("%d", &atual->info.codigo);
		__fpurge(stdin);
		printf("Nome do produto: ");
		fgets(atual->info.nome, 20, stdin);
		printf("Preço do produto: ");
		scanf("%f", &atual->info.preco);
		__fpurge(stdin);
		cabeca->first = atual;
		cabeca->last = atual;
		cabeca->nItens++;
		return cabeca;
	}
	do{
		system("clear");
		printf("Inserir elemento a partir do:\n");
		printf("1-Primeiro Cadastrado\n");
		printf("2-Ultimo Cadastrado\n");
		printf("0-Cancelar\n");
		scanf("%d", &menu);
		switch(menu){
			case 1:
				printf("Código do Produto: ");
				scanf("%d", &atual->info.codigo);
				__fpurge(stdin);
				printf("Nome do produto: ");
				fgets(atual->info.nome, 20, stdin);
				printf("Preço do produto: ");
				scanf("%f", &atual->info.preco);
				__fpurge(stdin);
				cabeca->nItens++;
				atual->prev = NULL;
				atual->next = cabeca->first;
				cabeca->first->prev = atual;
				cabeca->first = atual;
				return cabeca; break;
			case 2:
				printf("Código do Produto: ");
				scanf("%d", &atual->info.codigo);
				__fpurge(stdin);
				printf("Nome do produto: ");
				fgets(atual->info.nome, 20, stdin);
				printf("Preço do produto: ");
				scanf("%f", &atual->info.preco);
				__fpurge(stdin);
				cabeca->nItens++;
				atual->next = NULL;
				atual->prev = cabeca->last;
				cabeca->last->next = atual;
				cabeca->last = atual;
				return cabeca; break;
		}
	}while(menu);
	return cabeca;
}

TpLista *pop(TpLista *cabeca){
	int cod;
	TpNodo *aux = cabeca->first, *aux2;
	printf("Digite o código do produto:\n");
	scanf("%d", &cod);
	if(cabeca->first == NULL){
		printf("Nenhum elemento cadastrado...\n");
		return cabeca;
	}else if(aux->prev == NULL && aux->next == NULL && aux->info.codigo == cod && cabeca->first == cabeca->last){
		cabeca->first = NULL;
		cabeca->last = NULL;
		cabeca->nItens = 0;
		return cabeca;
	}
	for( ; aux != NULL; aux = aux->next){
		if(aux->info.codigo == cod && aux->prev == NULL){
			cabeca->first = aux->next;
			cabeca->first->prev = aux->prev;
			return cabeca;
		}else if(aux->info.codigo == cod && aux->next == NULL){
			cabeca->last = aux->prev;
			cabeca->last->next = aux->next;
			return cabeca; 
		}else if(aux->info.codigo == cod){
			aux2 = aux->prev;
			aux2->next = aux->next;
			aux->next->prev = aux2;
			return cabeca;
		}
	}
	printf("Nenhum codigo encontrado...\n");
	return cabeca;
}

void mostraProdutos(TpLista *cabeca){
	int i=0;
	TpNodo *imp = cabeca->first;
	if(cabeca->first == NULL){
		printf("Não há produtos cadastrados...\n");
	}else{
		for(; imp != NULL; imp = imp->next, i++){
			printf("---------------------------------------------------------------\n");
			printf("|Dados do produto %d|\n", i+1);
			printf("Codigo: %d\n", imp->info.codigo);
			printf("Nome: %s", imp->info.nome);
			printf("Preço R$: %0.2f\n\n", imp->info.preco);
		}
	}
}

int main(){
	int menu;
	TpLista *cabeca = (TpLista*)malloc(sizeof(TpLista));
	cabeca->first = NULL;
	cabeca->last = NULL;
	cabeca->nItens = 0;
	int i = 0;
	do{
		printf("Pressione enter para continuar...\n");
		__fpurge(stdin);
		getchar();
		system("clear");
		printf("1-Inserir elemento:\n");
		printf("2-Extrair elemento:\n");
		printf("3-Elementos cadastrados:\n");
		printf("0-Encerrar\n");
		scanf("%d", &menu);
		switch(menu){
			case 1: cabeca = push(cabeca); break;
			case 2: cabeca = pop(cabeca); break;
			case 3: mostraProdutos(cabeca); break;
		}
	}while(menu);
	free(cabeca);
	return 0;
}