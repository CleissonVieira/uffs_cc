#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio_ext.h>

int verificar = 0;

typedef struct _produto{
	int id;
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

TpLista *inicializa(){
	TpLista *cabeca = (TpLista*) malloc(sizeof(TpLista));
	cabeca->nItens = 0;
	cabeca->first = NULL;
	cabeca->last = NULL;
	return cabeca;
}

TpLista *push(TpLista *cabeca){
	int menu;
	TpNodo *atual = (TpNodo*)malloc(sizeof(TpNodo));
	printf("Código do Produto: ");
	scanf("%d", &atual->info.codigo);
	__fpurge(stdin);
	printf("Nome do produto: ");
	fgets(atual->info.nome, 20, stdin);
	printf("Preço do produto: ");
	scanf("%f", &atual->info.preco);
	atual->info.id = cabeca->nItens + 1;
	__fpurge(stdin);
	if(cabeca->nItens == 0){
		cabeca->first = atual;
		cabeca->last = atual;
		cabeca->nItens++;
		return cabeca;
	}
	system("clear");
	printf("Inserir elemento a partir do:\n");
	printf("1-Primeiro Cadastrado\n");
	printf("2-Ultimo Cadastrado\n");
	printf("0-Cancelar\n");
	scanf("%d", &menu);
	switch(menu){
		case 1:
			cabeca->nItens++;
			atual->prev = NULL;
			atual->next = cabeca->first;
			cabeca->first->prev = atual;
			cabeca->first = atual;
			return cabeca; break;
		case 2:
			cabeca->nItens++;
			atual->next = NULL;
			atual->prev = cabeca->last;
			cabeca->last->next = atual;
			cabeca->last = atual;
			return cabeca; break;
	}
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
			printf("ID: %d\n", imp->info.id);
			printf("Codigo: %d\n", imp->info.codigo);
			printf("Nome: %s", imp->info.nome);
			printf("Preço R$: %0.2f\n\n", imp->info.preco);
		}
	}
}

TpLista *selection(TpLista *cabeca){
	if(cabeca->first == NULL){
		printf("Nada adicionado\n");
		return cabeca;
	}
	printf("Entrou\n");
	TpNodo *aux, *aux1, *aux2, *aux3, *aux4, *aux5, *atual = cabeca->first, *imp = cabeca->first->next, *i = cabeca->first;
	for(; i != cabeca->last; atual = i = i->next){ //For para encontrar a Base
		aux = i;
		for(imp = i->next; imp != NULL; imp = imp->next){ //For para encontrar o Menor valor
			if(aux->info.codigo > imp->info.codigo){
				aux = imp;
			}
		}
		printf("Atual = %d\n", i->info.codigo);
		printf("Menor = %d\n", aux->info.codigo);
		if(i->info.codigo != aux->info.codigo){
			printf("caso\n");
			//Verificar se o menor não é o primeiro
			if(aux->info.codigo == cabeca->last->info.codigo && i->info.codigo == cabeca->first->info.codigo){
				aux3 = atual;
				atual->prev = aux->prev;
				aux->next = atual->next;
				atual->next->prev = aux;	//Caso de Base first e Menor last
				aux->prev->next = atual;	
				aux->prev = NULL;
				atual->next = NULL;
				cabeca->first = aux;
				cabeca->last = atual;
				printf("caso1\n");
				
			}else if(i->info.codigo == cabeca->first->info.codigo && aux->info.codigo != cabeca->last->info.codigo && aux->info.codigo != cabeca->first->next->info.codigo){
				aux1 = atual;			//Caso de Base first e Menor diferente do next da base e diferente do last
				aux2 = aux;
				aux3 = atual->next;			
				aux4 = aux->next;
				aux5 = aux->prev;
				aux4->prev = aux1;
				aux5->next = aux1;
				aux1->prev = aux5;
				aux1->next = aux4;
				aux3->prev = aux2;
				aux2->prev = NULL;
				aux2->next = aux3;
				cabeca->first = aux2;
				printf("caso2\n");
				
			}else if(aux->info.codigo == cabeca->last->info.codigo && i->info.codigo != cabeca->first->info.codigo && i->info.codigo != cabeca->last->prev->info.codigo){
				aux2 = aux;			//Caso da Base ser algum valor do meio da lista diferente de Menor->prev e Menor ser o last ARRUMAR
				aux3 = atual;	
				aux4 = aux->prev;
				aux3->prev->next = aux2;
				aux3->next->prev = aux2;
				aux2->prev = aux3->prev;
				aux2->next = aux3->next;
				aux3->prev = aux4;
				aux3->next = NULL;
				aux4->next = aux3;
				cabeca->last = aux3;
				printf("caso3\n");
				
			}else if(i->next->info.codigo == aux->info.codigo){	//Caso da Base estar ao lado do Menor
				if(i->info.codigo == cabeca->first->info.codigo){ //Base é first e Menor fica ao lado
					aux->next->prev = atual;
					cabeca->first = aux;
					atual->prev = cabeca->first;	
					atual->next = aux->next;
					aux->next = atual;
					aux->prev = NULL;
					printf("caso4\n");
					
				}else if(cabeca->last->info.codigo == aux->info.codigo){ //Menor é last e Base fica ao lado
					aux1 = atual->prev;
					aux1->next = aux;
					aux->prev = aux1;
					aux->next = atual;
					atual->prev = aux;
					cabeca->last = atual;
					atual->next = NULL;
					printf("caso5\n");
					return cabeca; //nao deletar essa

				}else{ //Casos do meio sem envolver first e last
					aux2 = aux;
					aux->next->prev = atual;
					atual->next = aux->next;
					aux->next = atual;				
					aux->prev = atual->prev;
					atual->prev->next = aux;
					atual->prev = aux;
					printf("caso6\n");
				}
			}else if(aux->info.codigo != atual->next->info.codigo && aux->info.codigo != cabeca->last->info.codigo){ 
				//Casos do meio, distantes por um nodo e diferentes de first e last
				aux1 = atual;
				aux2 = atual->next;
				aux3 = aux;
				aux1->prev->next = aux3;
				aux3->next->prev = aux1;
				aux2->prev = aux3;
				aux2->next = aux1;
				aux3->prev = aux1->prev;
				aux1->next = aux3->next;
				aux1->prev = aux2;
				aux3->next = aux2;
				printf("caso7\n");
				
			}
			i = aux;
		}
	}
	return cabeca;
}

TpLista *insertion(TpLista *cabeca){
	TpNodo *i = cabeca->first->next, *j, *aux, *aux1, *aux2, *aux3;
	if(cabeca->first == NULL){
		printf("Nada adicionado\n");
		return cabeca;
	}else if(i->next == NULL){
		aux = i->prev;	//Verificar se tem apenas 2 elementos na lista
		aux1 = i;
		if(aux1->info.codigo < aux->info.codigo){
			aux1->next = aux;	//Verificar se last é menor que first para trocar
			aux->prev = aux1;
			aux1->prev = NULL;
			aux->next = NULL;
			cabeca->first = aux1;
			cabeca->last = aux;
		}
	}else{
		for(; i != NULL; i = i->next){
			j = i->prev;
			for(; j != NULL; j = j->prev){
				aux = j;
				aux1 = i;
				if(aux1->info.codigo < aux->info.codigo && aux->info.codigo == cabeca->first->info.codigo){
					//Verificar se o numero maior (esquerda) a ser trocado é o first
					aux2 = i->next;
					aux->next = aux2;
					aux2->prev = aux;
					aux->prev = aux1;
					aux1->next = aux;
					aux1->prev = NULL;
					cabeca->first = aux1;
				}else if(aux1->info.codigo < aux->info.codigo && aux1->info.codigo == cabeca->last->info.codigo){
					//Verificar se o numero menor (direita) a ser trocado é o last
					aux2 = j->prev;
					aux2->next = aux1;
					aux1->prev = aux2;
					aux1->next = aux;
					aux->prev = aux1;
					aux->next = NULL;
					cabeca->last = aux;
				}else if(aux->info.codigo != cabeca->first->info.codigo && aux1->info.codigo != cabeca->last->info.codigo && aux1->info.codigo < aux->info.codigo){
					//Casos que não envolvam first e last (do meio)
					aux2 = i->next;
					aux3 = j->prev;
					aux3->next = aux1;
					aux->prev = aux1;
					aux->next = aux2;
					aux1->prev = aux3;
					aux1->next = aux;
					aux2->prev = aux;
				}
			}
		}
	}
	return cabeca;
}

void divide(TpLista *cabeca, TpLista *L, TpLista *R){
	int i, idmeio, idauxF = cabeca->first->info.id, idauxL = cabeca->last->info.id;
	TpNodo *nodomeio = cabeca->first;
	idmeio = ((idauxL - idauxF) / 2) + 1;
	for(i = 0; i <= idmeio-1; i++){
		nodomeio = nodomeio->next;
	}
	//preenchendo a lista a esquerda
	L->first = cabeca->first;
	L->last = nodomeio->prev,
	L->nItens = idmeio;
	//preenchendo a lista a direita
	R->first = nodomeio;
	R->last = cabeca->last;
	R->nItens = (idauxL - idauxF) - (idmeio - 1);
}

TpLista *juntar(TpLista *L, TpLista *R){
	TpNodo *aux;
	printf("Entrou juntar\n");
	//CASO TENHA APENAS UM ELEMENTO NA LEFT E UM NA RIGHT
	if(L->nItens == 1 && R->nItens == 1){
		printf("LEFT=RIGHT=1\n");
		//Se L for maior que R
		if(L->first->info.codigo > R->first->info.codigo){
			printf("L>R\n");
			L->first->prev = R->first;
			R->first->next = L->first;
			L->first = R->first;
			L->first->prev = NULL;
			L->last->next = NULL;
			return;
		//Se R for maior que L
		}else{
			printf("R>L\n");
			L->first->next = R->first;
			R->first->prev = L->first;
			L->last = R->first;
			return;
		}
	}

	//CASO LEFT TENHA MAIS QUE UM ELEMENTO E RIGHT APENAS UM
	else if(L->nItens > 1 && R->nItens == 1){
		printf("LEFT>1\n");
		//Se R for maior que todos no L
		if(R->first->info.codigo > L->last->info.codigo){
			printf("R>que todosL\n");
			L->last->next = R->first;
			R->first->prev = L->last;
			L->last = R->first;
			return;
		//Se R for menor que todos no L
		}else if(R->first->info.codigo < L->first->info.codigo){
			printf("R<que todosL\n");
			R->first->next = L->first;
			L->first->prev = R->first;
			L->first = R->first;
			return;
		}
		//Se R for um valor que se encaixa no meio de L
		else{ 
			printf("Rvalor do meioL\n");
			for(TpNodo *i = L->first; i != NULL; i = i->next){
				if(R->first->info.codigo < i->info.codigo){
					aux = i->prev;
					i->prev = R->first;
					R->first->next = i;
					R->first->prev = aux;
					aux->next = R->first;
					return;
				}
			}
		}
	}

	//CASO LEFT E RIGHT TENHAM MAIS QUE UM ELEMENTO
	else if(L->nItens > 1 && R->nItens > 1){
		printf("LEFT=RIGHT>1\n");
		for(TpNodo *right = R->last; right != NULL; ){
			for(TpNodo *left = L->first; left != NULL; left = left->next){
				if(right == NULL){
					break;
				}
				//Um qualquer de R com o first de L
				if(right->info.codigo < left->info.codigo && left == L->first){
					aux = right->next;
					left->prev = right;
					right->next = left;
					right->prev = NULL;
					L->first = right;
					right = aux;
				}
				//Um qualquer de R com last de L
				else if(right->info.codigo > left->info.codigo && left == L->last){
					aux = right->next;
					left->next = right;
					right->prev = left;
					right->next = NULL;
					L->last = right;
					right = aux;
				}
				//Se R for um aleatório no meio e L também
				else if(left != L->first && left != L->last){
					if(right->info.codigo < left->info.codigo){
						aux = left->prev;
						left->prev = right;
						aux->next = right;
						right->prev = aux;
						right->next = left;
					}
				}
			}
		}
		return L;
	}
}

TpLista *MergeSort(TpLista *cabeca, int idf, int idl){
	TpLista *R = inicializa();//Divisão Direita
	TpLista *L = inicializa();//Divisão Esquerda
	printf("cabeca = %d\n", cabeca->nItens);

		printf("cabeca first%d\n", cabeca->first->info.codigo);
		printf("cabeca last%d\n", cabeca->last->info.codigo);

	//DIVIDE
	if(idl - idf > 0){

		printf("Divide\n");
		divide(cabeca, L, R);

		printf("L = %d\n", L->nItens);
		printf("R = %d\n", R->nItens);
		
		printf("MergeL\n");
		MergeSort(L, L->first->info.id, L->last->info.id);//Recursão para a lista da esquerda
		
		printf("MergeR\n");
		MergeSort(R, R->first->info.id, R->last->info.id);//Recursão para a lista da direita
		
		printf("LF = %d LL = %d\n", L->first->info.codigo, L->last->info.codigo);
		printf("RLF = %d\n", R->first->info.codigo);

		printf("Juntar\n");
		juntar(L, R);
		return L;
	}
}


int main(){
	int menu;
	TpLista *cabeca = inicializa();
	do{
		printf("Pressione enter para continuar...\n");
		__fpurge(stdin);
		getchar();
		system("clear");
		printf("1-Inserir elemento:\n");
		printf("2-Extrair elemento:\n");
		printf("3-Elementos cadastrados:\n");
		printf("4-Ordenar via Insertion Sort:\n");
		printf("5-Ordenar via Selection Sort:\n");
		printf("6-Ordenar via Merge Sort:\n");
		printf("0-Encerrar\n");
		scanf("%d", &menu);
		switch(menu){
			case 1: cabeca = push(cabeca); break;
			case 2: cabeca = pop(cabeca); break;
			case 3: mostraProdutos(cabeca); break;
			case 4: cabeca = insertion(cabeca); break;
			case 5: cabeca = selection(cabeca); break;
			case 6: cabeca = MergeSort(cabeca, cabeca->first->info.id, cabeca->last->info.id); break;
		}
	}while(menu);
	free(cabeca);
	return 0;
}