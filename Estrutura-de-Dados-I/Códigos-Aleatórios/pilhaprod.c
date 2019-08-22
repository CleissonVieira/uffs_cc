#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio_ext.h>
#define TAM 50
int quant;

typedef struct _produto{
	int cod;
	char nome[TAM];
	float preco;
}tp_produto;

typedef struct _pilha{
	tp_produto *info;
	int topo;
}tp_pilha;

int teste(tp_pilha *pilha){
	if(pilha->topo == quant-1){
		return 0;
	}if(pilha->topo == -1){
		return -1;
	}
	return 1;
}
void printarestado(int retorno, tp_pilha *pilha){
	if(retorno == 0){
		printf("Pilha cheia...\n\n");
	}else if(retorno == -1){
		printf("Pilha vazia...\n\n");
	}
} 
void push(tp_pilha *pilha){
	int retorno = teste(pilha);
	if(retorno == 0){
		printarestado(retorno, pilha);
		return;
	}else{
		pilha->topo += 1;
		printf("Código do Produto: ");
		scanf("%d", &(pilha->info+(pilha->topo))->cod);
		__fpurge(stdin);
		printf("Nome do produto: ");
		fgets((pilha->info+(pilha->topo))->nome, 50, stdin);
		printf("Preço do produto: ");
		scanf("%f", &(pilha->info+(pilha->topo))->preco);
		__fpurge(stdin);
	}	
}
int pop(tp_pilha *pilha){
	int retorno = teste(pilha);
	if(retorno == -1){
		printf("Pilha vazia...\n");
		return;
	}
	pilha->topo -= 1;
	
}
void mostraProdutos(tp_pilha *pilha){
	int i;
	if(pilha->topo ==-1){
		printf("Pilha vazia...\n");
		return;
	}
	for(i=0; i<pilha->topo+1; i++){
		printf("---------------------------------------------------------------\n");
		printf("Dados do produto %d:\n\n", i+1);
		printf("Código: %d\n", (pilha->info+(i))->cod);
		printf("Nome: %s", (pilha->info+(i))->nome);
		printf("Preço: %.2f\n\n", (pilha->info+(i))->preco);
	}	
}

int main(){
	int menu;
	tp_pilha *pilha = (tp_pilha*)malloc(sizeof(tp_pilha));
	pilha->topo=-1;
	printf("Quantidade de produtos a ser inserido na pilha?\n");
	scanf("%d", &quant);
	__fpurge(stdin);
	pilha->info = (tp_produto*)malloc(quant*sizeof(tp_produto));
	do{
		printf("Pressione enter para continuar...\n");
		__fpurge(stdin);
		getchar();
		system("clear");
		printf("1-Inserir elemento:\n");
		printf("2-Extrair ultimo elemento:\n");
		printf("3-Estado da pilha:\n");
		printf("0-Encerrar\n");
		scanf("%d", &menu);
		switch(menu){
			case 1: push(pilha); break;
			case 2: pop(pilha); break;
			case 3: mostraProdutos(pilha); break;
		}
	}while(menu);
	return 0;
}