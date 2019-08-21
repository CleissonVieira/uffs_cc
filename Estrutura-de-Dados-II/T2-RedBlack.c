#include <stdio.h>
#include <stdlib.h>
#include <stdio_ext.h>

int global = 0, first = 0, nivel = -1;

typedef struct nodo{
    int chave;
    char color;
    struct nodo *father;
    struct nodo *left;
    struct nodo *right;
} TpNodo;

typedef struct nodo *treeRaiz;

void pause(){
    printf("Press enter for next...\n");
    __fpurge(stdin);
    getchar();
}

//-----------------------------------INICIALIZA-------------------------------------//
treeRaiz *inicializa(){ //raiz
    treeRaiz *raiz = (treeRaiz *)malloc(sizeof(treeRaiz));
    (*raiz) = NULL;
    return raiz;
}
TpNodo *inicializar(){
    TpNodo *new = (TpNodo *)malloc(sizeof(TpNodo));
    new->left = NULL;
    new->right = NULL;
}
//-----------------------------------Tratar casos para modificações--------------------------------------//
void case1(treeRaiz *father, treeRaiz *child, treeRaiz *uncle){
    (*uncle)->color = 'P';
    (*father)->father->color = 'V';
    (*father)->color = 'P';
    //Condição para manter raiz Preta (condição RedBlack)
    if ((*father)->father->chave == (*father)->father->father->chave){
        (*father)->father->color = 'P';
        (*father)->father->father->color = 'P';
    }
    printf("Caso 1 realizada com sucesso!\n");
    pause();
}
void case3(TpNodo *father, TpNodo *child){
    TpNodo *grandma = father->father;
    father->color = 'P';
    grandma->color = 'V';
    if(grandma->chave > grandma->father->chave){
        father->left = grandma;  //casos de simetria
        grandma->father->right = father;
        grandma->right = NULL;
        father->father = grandma->father;
        grandma->father = father;
    }else if(grandma->chave < grandma->father->chave){
        father->right = grandma;
        grandma->father->left = father;
        grandma->left = NULL;
        father->father = grandma->father;
        grandma->father = father;
    }else if(grandma->chave == grandma->father->chave){
        TpNodo *aux = inicializar();
        aux->color = grandma->color;
        aux->chave = grandma->chave;
        aux->father = father;
        grandma->father->chave = father->chave;
        grandma->father->color = father->color;
        if(father->left == NULL){
            grandma->left = aux;
            grandma->right = child;
        }else{
            grandma->right = aux;
            grandma->left = child;
        }
    }
    printf("Caso 3 realizada com sucesso!\n");
    pause();
    global = 1;
}
void case2(TpNodo *father, TpNodo *child){
    TpNodo *grandma = father->father;
    child->father = father->father;
    if (father->chave < grandma->chave){
        child->father->left = child; // Casos de simetria
        father->right = NULL;
        child->left = father;
    }else if (father->chave > grandma->chave){
        child->father->right = child; 
        father->left = NULL;
        child->right = father;
    }
    father->father = child;
    printf("caso 2 realizada com sucesso!\n");
    case3(child, father);
    global = 1;
}
//-----------------------------------INSERIR---------------------------------------------//
int inserir(treeRaiz *raiz, int valor, treeRaiz *father){
    int rt;
    if (*raiz == NULL){ //Árvore vazia ou nó folha
        TpNodo *new = (TpNodo *)malloc(sizeof(TpNodo));
        if (new == NULL){ //Verificar se alocou memória, se sim será != de NULL
            return 0;
        }
        if (first == 0){ //Verificar se primeiro elemento, se não for vai ter pai father que é valor anterior
            new->father = new;
            new->color = 'P';
        }else if (first == 1){
            new->color = 'V';
            new->father = *father;
        }
        new->chave = valor;
        new->left = NULL;
        new->right = NULL;
        *raiz = new;
        first = 1;
        return 1;
    }
    TpNodo *atual = *raiz;
    if (valor < atual->chave){ //Se valor menor que atual vai pro lado esquerdo da raiz
        if ((rt = inserir(&(atual->left), valor, &(atual))) == 1){ //Encontrar nó folha a esquerda
            if(global == 1){ //Se já aplicou o caso retorna tudo para encerrar
                    return rt;
            }
            if (atual->color == 'V' && atual->left->color == 'V'){ //Verifica se pai e filho são Red
                if (atual->father->right != NULL && atual->father->right->color == 'V' && atual->father->right->chave > atual->chave){
                    case1(&(atual), &(atual)->left, &(atual)->father->right); //----Caso 1 ----//
                    return rt;
                }else if (atual->father->left != NULL && atual->father->left->color == 'V' && atual->father->left->chave < atual->chave){
                    case1(&(atual), &(atual)->left, &(atual)->father->left); //----Caso 1 ----//
                    return rt;
                }
                if (atual->chave > atual->father->chave && atual->chave > atual->left->chave){ //----Caso 2 ----//
                    case2(atual, atual->left);
                    return rt;
                }
                if (atual->chave < atual->father->chave && atual->chave > atual->left->chave){ //----Caso 3 ----//
                    case3(atual, atual->left);
                }
            }
        }
    }else{ //Se valor maior que atual vai pro lado direito da raiz
        if (valor > atual->chave){
            if ((rt = inserir(&(atual->right), valor, &(atual))) == 1){ //Encontrar nó folha a direita
                if(global == 1){//Se já aplicou o caso retorna tudo para encerrar
                    return rt;
                }
                if (atual->color == 'V' && atual->right->color == 'V'){ //Verifica se pai e filho são Red
                    if (atual->father->left != NULL && atual->father->left->color == 'V' && atual->father->left->chave < atual->chave){
                        case1(&(atual), &(atual)->right, &(atual)->father->left); //----Caso 1 ----//
                        return rt;
                    }else if (atual->father->right != NULL && atual->father->right->color == 'V' && atual->father->right->chave > atual->chave){
                        case1(&(atual), &(atual)->right, &(atual)->father->right); //----Caso 1 ----//
                        return rt;
                    }  
                    if (atual->chave < atual->father->chave && atual->chave < atual->right->chave){//----Caso 2 ----//
                        case2(atual, atual->right);
                        return rt;
                    }
                    if (atual->chave > atual->father->chave && atual->chave < atual->right->chave){//----Caso 3 ----//
                        case3(atual, atual->right);
                    }
                }
            }
        }else{ //Se valor já existe na árvore
            printf("Já existe essa chave...\n");
            pause();
            return 0;
        }
    }
    return rt;
}
//-----------------------------------IMPRIMIR-------------------------------------------//
int listar(treeRaiz *raiz, int i, treeRaiz *father){
    int rt;
    
    if (*raiz == NULL){ //Verifica até chegar na primeira altura e começar a retornar recursividade
        return 1;
    }
    TpNodo *atual = *raiz;
    if((rt = listar(&(atual->left), i, &(atual))) == 1){ //começar recursividade a esquerda
        
        if ((*raiz)->chave < (*father)->chave){
            //printf("Nível: %d\n", nivel);
            printf("|Child-Left: %d| |Child-Color: %c|\n", (*raiz)->chave, (*raiz)->color);
        }else if ((*raiz)->chave > (*father)->chave){
            //printf("Nível: %d\n", nivel);
            pr  intf("|Child-Right: %d| |Child-Color: %c|\n", (*raiz)->chave, (*raiz)->color);
        }
        printf("|Father: %d| |Father-Color: %c|\n\n", (*raiz)->father->chave, (*raiz)->father->color);
        i = 1; //significa que é o ultimo nó a esquerda e que já foi imprimido
    }
    if((rt = listar(&(atual->right), i, &(atual))) == 1){ //faz as recursividades a direita
        if (i == 1){ //verifica se já foi imprimido e retorna 1 para voltar mais uma chamada recursiva
            return 1;
        }
    }
    return rt;
}
//-----------------------------------MAIN------------------------------------------------//
int main(){
    treeRaiz *arvore = inicializa();
    int menu, valor, y, i = -1;
    do{
        system("clear");
        printf("1-Inserir elemento:\n");
        printf("2-Listar elementos:\n");
        printf("0-Encerrar\n");
        scanf("%d", &menu);
        switch (menu){
        case 1:
            printf("\nValor a ser inserido: ");
            scanf("%d", &valor);
            int x = inserir(arvore, valor, arvore);
            printf("Caso 3 realizada com sucesso!\n");
            global = 0;
            break;
        case 2:
            y = listar(arvore, i, arvore);
            pause();
            break;
        }
    } while (menu);
    return 0;
}