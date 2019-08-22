#include <stdio.h>
#include <stdlib.h>
#define MAX 5

typedef struct __pilha{
  int info[MAX];
  int topo;
}tp_pilha;

int teste(tp_pilha *pilha){
	if(pilha->topo == MAX-1){
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
	}else{
		printf("\nHá %i espaço(s) vazio(s) do total de 5\n", (MAX-1-pilha->topo));
	}
}
void push(tp_pilha *pilha){
	int retorno = teste(pilha);
	if(retorno == 0){
		printarestado(retorno, pilha);
	}else{
		pilha->topo += 1;
		printf("Valor a ser inserido:\n");
		scanf("%d",  pilha->info+(pilha->topo));
	}
}
int pop(tp_pilha *pilha){
	int retorno = teste(pilha);
	if(retorno != -1){
		int extrair = *(pilha->info+(pilha->topo));
		pilha->topo -= 1;
		return extrair;
	}else{
		printarestado(retorno, pilha);
	}
}
void mostraValores(tp_pilha *pilha){
	int i;
	if(pilha->topo == -1){
		printf("Pilha vazia...\n");
	}else{
		printf("Valores da Pilha: ");
		for(i=0; i<pilha->topo+1; i++){
			printf("%d ", *(pilha->info+i));
		}printf("\n\n");
	}
}

int main(){
	int menu;
	tp_pilha *pilha = (tp_pilha*) malloc(sizeof(tp_pilha));
	pilha->topo = -1;	
	do{
		printf("1-Verificar Estado:\n");
		printf("2-Inserir elemento:\n");
		printf("3-Extrair ultimo elemento:\n");
		printf("4-Estado da pilha:\n");
		printf("5-Encerrar\n");
		scanf("%d", &menu);
		switch(menu){
			case 1: printarestado(teste(pilha), pilha); break;
			case 2: push(pilha); break;
			case 3: pop(pilha); break;
			case 4: mostraValores(pilha); break;
		}
	}while(menu<5);
	return 0;
}	