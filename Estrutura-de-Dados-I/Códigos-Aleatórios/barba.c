#include <stdio.h>
#include<stdlib.h>
 
#define MAX 8
 
typedef struct info{ //struct para a informação do nó
      int valor;
}info;
 
typedef struct nodo{ //struct para o nó
      info elemento;
      struct nodo *next;
}nodo;

 
int resto(int num){ //essa função vai calcular em qual linha da tabela hash ficará o novo elemento
    return (num % MAX);
}

int procura(int num, nodo *hash_table[]){
    int h;
    nodo *aux;
    h = resto(num); //calcula em qual linha da tabela está o elemento

    aux = hash_table[h]; //auxiliar recebe essa linha da tabela

    while(aux != NULL){
        if(aux->elemento.valor == num) //se o num que o usuario digitou for igual a algum valor da linha
            return h;             //retorna o valor da linha

        aux = aux->next; //senão vai pro proximo até achar algum
    }

    return -1; //caso não ache nenhum retorna -1
}

void push(info nozinho, nodo *hash_table[]){
    int num, h, volta;
    nodo *novo;
    num = nozinho.valor;

    if(procura(num, hash_table) != -1){ //se retornou a linha da tabela significa que esse elemento ja existe
        printf("_____________~<>~____________\n");
        printf("Já existe esse número!\n");
        printf("Digite 1 para voltar\n");
        scanf("%d", &volta);
        return;
    }

    h = resto(num); //h será a posição na tabela 
    novo = malloc(sizeof(struct nodo)); //aloca espaço pro novo nodo
    novo->elemento = nozinho;  //o novo nó receberá a info do nozinho
    novo->next = hash_table[h]; //o proximo do novo nodo será a linha da tabela
    hash_table[h] = novo; //essa linha da tabela irá receber o novo nó
}

void displayLinha(int i, nodo *hash_table[]){
    int volta;
    nodo *aux;
        
    system("clear");

    if(i != -1){ //se a função procura retornou algum valor de linha significa que ele está nessa linha
        printf("_______________~<>~______________\n");
        printf("Elemento encontrado na linha: %d\n", i);
        printf("\n[%d] ", i);
        aux = hash_table[i];
        
        while(aux != NULL){
            printf("%d -> ", aux->elemento.valor);
            aux = aux->next;
        }

        printf("NULL");
        printf("\n_______________~<>~______________\n");
        printf("Digite 1 para voltar: ");
        scanf("%d", &volta);
    }

    else{ //senão ele retornou -1, ou seja, não se encontra na tabela
        printf("_______________~<>~______________\n");
        printf("Elemento não encontrado\n");
        printf("Digite 1 para voltar: ");
        scanf("%d", &volta);
    }
}
 
void display(nodo *hash_table[]){
    int i, volta;
    nodo *aux;

    system("clear");
    printf("_____________~<>~____________\n");

    for(i = 0; i < MAX; i++){ //imprimo a posição da linha
        printf("\n[%d] ", i);
        if(hash_table[i] != NULL){ //caso essa linha não for nula aux recebe essa linha
            aux = hash_table[i];

            while(aux != NULL){ //vou imprimindo os valores até aux ser nulo
                printf("%d -> ", aux->elemento.valor);
                aux = aux->next; 
            }
            
            printf("NULL");
        }   

    }

    printf("\n_____________~<>~____________\n");
    printf("Digite 1 para voltar: ");
    scanf("%d", &volta);
}

int main(void){
    nodo *hash_table[MAX];  //declaro uma tabela hash com 8 nodos
    info nozinho; //declaro uma variavel nozinho para receber a struct info
    int i, num, option; 

    /********************************************************************************
    i = é para a função receber nulo em todas as suas posições
    num = é para o usuário digitar um valor para comparar com algum elemento da tabela
    option = é para escolher uma opção no menu
    *********************************************************************************/

    for(i = 0; i <= MAX - 1; i++) //deixando todas as linhas da tabela = NULL
        hash_table[i] = NULL;

    while(1){
        system("clear");
        printf("_________________~<>~________________\n");
        printf("             TABELA HASH\n\n");   
        printf("(1) Inserir um elemento na tabela\n");
        printf("(2) Procurar um elemento\n");
        printf("(3) Mostrar a tabela hash\n");
        printf("(4) Sair\n");
        printf("_________________~<>~________________\n");
        printf("Digite sua opção: ");
        scanf("%d",&option);
        
        switch(option){
            case 1: 
                system("clear");
                printf("_____________~<>~____________\n");
                printf("Digite o valor: ");
                scanf("%d", &nozinho.valor);
                push(nozinho, hash_table);
                break;
           
            case 2: 
                system("clear");
                printf("_____________~<>~____________\n");
                printf("Deseja buscar qual elemento? ");
                scanf("%d", &num);
                i = procura(num, hash_table);
                displayLinha(i, hash_table); 
                break;

            case 3: 
                display(hash_table);
                break;

            case 4:
                exit(1);
        }
    } 
    return 0;
}