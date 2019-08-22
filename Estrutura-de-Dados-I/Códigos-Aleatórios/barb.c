/*************************
  UFFS CHAPECÓ
  github: barbs-pm
  Barbara Pegoraro Markus

  LISTA DUPLA ENCADEADA
       E ORDENADA
**************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio_ext.h>
#define TAM 100

typedef struct produto{ //struct para cada informação do nodo
	int codigo;
	char nome[TAM];
	float preco;
}tp_produto;

typedef struct nodo{ //struct para cada nodo da lista
	tp_produto produto;
	struct nodo *next;
	struct nodo *prev;
}tp_nodo;


typedef struct lista{  //struct da cabeça da lista
	int nItens;
	tp_nodo *first;
	tp_nodo *last;
}tp_lista; 

//função que adiciona um nodo e retorna a lista atualizada
void push(tp_lista *head){
	tp_nodo* novo = (tp_nodo*) malloc(sizeof(tp_nodo)); //aloca um novo nodo
	
	novo->next = NULL; //o próximo para que o nodo apontará será NULL
	novo->prev = head->last; //o anterior que o nodo vai apontar é o ultimo da cabeça da lista

	if(head->nItens == 0){
		head->first = novo; //se o nItens é 0 significa que o first da cabeça será esse nodo
		novo->prev = NULL;
	}
	
	else (novo->prev)->next = novo; //senão o nodo será o proximo da lista

	head->last = novo;	//o last da cabeça será esse nodo

	system("clear");  //adicionando as informações do nodo
	printf("\t___________~<>~___________\n");
	printf("\tCódigo do produto: ");
	scanf("%d", &novo->produto.codigo);
	printf("\tNome: ");
	getchar();
	fgets(novo->produto.nome, TAM, stdin);
	printf("\tPreço: ");
	scanf("%f", &novo->produto.preco);

	(head->nItens)++; //número de itens aumenta

}

/**********************
selo anti-plágio
code feito por Barbara
***********************/

void pop(tp_lista *head){
	int codiguinho, volta, cont=0;
	/* códiguinho = comparar o codigo do usuario e do nodo
	   volta = sair da função
	   cont = contador para verificar se existe algum produto
	*/
	tp_nodo *aux, *endereco; //endereco = receberá posição atual do p para poder apontar um a frente depois
	
	if(head->nItens == 0) { //se a lista tiver vazia imprime mensagem
		system("clear");
		printf("\t___________~<>~__________\n");
		printf("\tLista vazia.\n");
		printf("\tAperte 1 para voltar: ");
		scanf("%d", &volta);
	}

		
	else{
		system("clear");
		printf("\t___________________~<>~__________________\n");
		printf("\tCódigo do produto que deseja retirar: ");
		scanf("%i",&codiguinho);

		for(aux = head->first; aux != NULL; aux = aux->next){  // percorre todos os elementos da lista do primeiro ate
															   //o ultimo apontando sempre pro próximo do atual
			if((aux->produto).codigo == codiguinho){ //compara se o código do produto é igual ao digitado pelo usuario
				cont = 1; //cont recebe um caso ache um produto com o código
				if(aux == head->first){ //se o produto for o primeiro
					endereco = head->first; //endereço será igual o first da lista
					head->first = (head->first)->next; //o first vai apontar para o proximo, "excluindo" o anterior
					endereco->prev = NULL; //o anterior do first será NULL
					(head->nItens)--; //numero de itens diminui		
				}
				
				else if(aux == head->last){ //se o produto for o último
					endereco = head->last; //endereço será o last da lista
					head->last = (head->last)->prev; //o last será o seu anterior
					(head->last)->next = NULL; //o proximo do last apontará para NULL
					(head->nItens)--; //número de itens diminui
				}
				else{ //caso ele esteja no meio
					(aux->next)->prev = aux->prev;//o anterior do proximo será o anterior do nodo
					(aux->prev)->next = aux->next;//o proximo do anterior sera o proximo do nodo
					(head->nItens)--;////número de itens diminui		
				}
			}
		}

		if(cont == 0){//caso não tenha achado produto, o codigo não irá alterar o seu valor
			system("clear");
			printf("\t____________~<>~___________\n");
			printf("\tProduto não encontrado\n");
			printf("\tAperte 1 para voltar: ");
			scanf("%d", &volta);
		}
	}
}

/**********************
selo anti-plágio
code feito por Barbara
***********************/

void display(tp_lista *head){
	tp_nodo *aux; 
	int volta;
	
	system("clear");

	
	printf("\t___________~<>~__________\n");

	for(aux = head->first; aux != NULL; aux = aux->next){
		printf("\tCódigo do produto: %d\n", (aux->produto).codigo);
		printf("\tNome: %s", (aux->produto).nome);
		printf("\tPreço: %.2f", (aux->produto).preco);
		printf("\n\n");
	}
	printf("\t___________~<>~__________\n");

	if(head->nItens == 0) { //se a lista tiver vazia imprime mensagem
		system("clear");
		printf("\t___________~<>~__________\n");
		printf("\tLista vazia.\n");
	}
	printf("\tAperte 1 para voltar: ");
	scanf("%d", &volta);
}

/****************
ORDENAÇÃO DO TIPO
 INSERTION SORT
****************/

void Insertion(tp_lista *head){
	tp_nodo *a=head->first, *b;

	for(a = a->next; a != NULL; a = a->next){ //for que percorre a lista
		for(b = a->prev; b != NULL; b = b->prev){ //for que percorre a lista a partir do anterior do first
			if(a->produto.codigo < b->produto.codigo){ //compara se o codigo é maior
				if(b->prev == NULL){ //caso seja o primeiro trocando
					a->next->prev = b;
					b->next = a->next;

					a->prev = NULL;
					a->next = b;

					b->prev = a;

					head->first = a;
				}
				
				else if(a->next == NULL){ //caso seja o ultimo trocando
					b->next = NULL;
					a->prev = b->prev;

					a->next = b;
					b->prev->next = a;
					
					b->prev = a;

					head->last = b;
				}

				else{ //caso seja o do meio trocando
					a->next->prev=b;
					b->next=a->next;

					a->prev=b->prev;
					a->next=b;

					b->prev->next=a;
					b->prev=a;
				}
			}		
		}
	}
}

/****************
ORDENAÇÃO DO TIPO
 SELECTION SORT
****************/

void Selection(tp_lista *head){
	tp_nodo *a = head->first, *b, *j, *i, *ant, *prox, *ant2, *prox2;

	for(i = head->first; i != head->last; a = i = i->next){ //for que percorre a lista
		b = i;
		for(j = a->next; j != NULL; j = j->next){ //for que percorre a lista a partir do next do first
       		if(j->produto.codigo < b->produto.codigo){
       			b = j;
       		}
		}
		if(a->produto.codigo != b->produto.codigo){
	       		ant = a->prev; //variaveis auxiliares para facilitar o aponteiramento
	        	prox = a->next;
	        	ant2 = b->prev;
				prox2 = b->next;

				if(a == head->first && a->produto.codigo > b->produto.codigo){ //caso trocar o first com algum elemento
					if(b == prox){ //caso for o prox do first
						a->next = prox2;
						a->prev = b;

						prox2->prev = a;
						b->next = a;
						b->prev = NULL;

						head->first = b;
						i = b;
					}

					else if(b != prox && b != head->last){ //caso não for o proximo do first
						a->next = prox2;
						prox2->prev = a;
						a->prev = ant2;
						ant2->next = a;

						b->next = prox;
						prox->prev = b;
						b->prev = ant;
						head->first = b;
						i = b;
					}

					else if(b == head->last){ //caso troque com o último
						a->next = prox2;
						a->prev = ant2;
						ant2->next = a;

						b->next = prox;
						prox->prev = b;
						b->prev = ant;

						head->first = b;
						head->last = a;
						i = b;
					}
				}
				else if(b == head->last){ //caso troque o ultimo
					if(a == b->prev){ //ultimo com o penultimo
						a->next = NULL;
						a->prev = b;

						b->next = a;
						b->prev = ant;
						ant->next = b;

						head->last = a;
						return;
					}

					else if(a != head->first && a != b->prev){ //caso for o ultimo com um do meio
						a->next = prox2;
						a->prev = ant2;
						ant2->next = a;

						b->next = prox;
						prox->prev = b;
						b->prev = ant;
						ant->next = b;

						head->last = a;
						i = b;
					}
				}
				
				else{ //caso seja um do meio trocando
					if(b == a->next){ //caso estejam um do lado do outro
						a->next = prox2;
						a->prev = b;
						prox2->prev = a;
						b->prev = a;

						b->next = a;
						b->prev = ant;
						ant->next = b;
						i = b;
					}
					
					else if(a != head->first && b != a->next && b != head->last){ //se estiverem separados
						a->next = prox2;
						prox2->prev = a;
						a->prev = ant2;
						ant2->next = a;
						b->next = prox;

						prox->prev = b;
						b->prev = ant;
						ant->next = b;
						i = b;
					}
				}
			}
	}
}

int main(void){
	int op;

	tp_nodo *l = NULL; //cria uma lista vazia
	tp_lista *head = malloc(sizeof(head));

	head->last = NULL;
	head->first = NULL;
	head->nItens = 0;
	
	do{
		system("clear");
		printf("\t___________~<>~__________\n");
		printf("\t|0| Sair\n");
		printf("\t|1| Inserir produto\n");
		printf("\t|2| Excluir produto\n");
		printf("\t|3| Exibir lista\n");
		printf("\t|4| Ordenar- Insertion\n");
		printf("\t|5| Ordenar- Selection\n");
		printf("\t|6| Ordenar- Merge\n");
		printf("\t___________~<>~__________\n");
		printf("\tEscolha sua opção: ");
		scanf("%d", &op);

		switch(op){
			case 1: push(head); break;
			case 2: pop(head); break;
			case 3: display(head); break;
			case 4: Insertion(head); break;
			case 5: Selection(head); break;
			//case 6: Merge(head); break;
		}
	
	} while(op != 0);

	free(l);
	free(head);

	return 0;
}