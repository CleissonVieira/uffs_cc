#include  <stdio.h>
#include  <stdlib.h>
#include  <stdio_ext.h>

typedef struct nodo{
  int chave;
  int altura;
  struct nodo *father;
  struct nodo *left;
  struct nodo *right;
}TpNodo;

typedef struct nodo *treeRaiz;
//Inicializa Raiz

void pause(){
  printf("Press enter for next...\n");
  __fpurge(stdin);
  getchar();
}

treeRaiz *inicializa() {
  treeRaiz *raiz = (treeRaiz*) malloc(sizeof (treeRaiz));
  (*raiz) = NULL;
  return raiz;
}
//função para retornar a altura do nodo
int altura(TpNodo *no){
  if(no == NULL){
    return -1;
  }else{
    return no->altura;
  }
}
//função para calcular o fator de balanceamento do nodo
int balanceamento(TpNodo *no){
  //return indiferente se positivo ou negativo nesse momento | função labs retorna um valor absoluto (positivo)
  return labs(altura(no->left) - altura(no->right));
}
//Calcular o maior valor
int maior(int x, int y){
  if(x > y){
    return x;
  }else{
    return y;
  }
}
//Left Left (aplica R)
void LL(treeRaiz *raiz){
  printf("Rotação LL (na prática aplica R)\n");
  printf("|    x |   y   |\n");
  printf("|  y   | Z   x |\n");
  printf("|Z     |       |\n");
  TpNodo *no;
  no = (*raiz)->left;
  (*raiz)->left = no->right;
  no->right = *raiz;
  (*raiz)->altura = maior(altura((*raiz)->left), altura((*raiz)->right)) + 1;
  no->altura = maior(altura(no->left), (*raiz)->altura) + 1;
  *raiz = no;
  printf("Rotação LL realizada com sucesso!\n");
  pause();
}
//Right Right (aplica L)
void RR(treeRaiz *raiz){
  printf("Rotação RR (na prática aplica L)\n");
  printf("|x-    |  -y-  |\n");
  printf("|  y-  | x   Z |\n");
  printf("|    Z |       |\n");
  TpNodo *no;
  no = (*raiz)->right;
  (*raiz)->right = no->left;
  no->left = (*raiz);
  (*raiz)->altura = maior(altura((*raiz)->left), altura((*raiz)->right)) + 1;
  no->altura = maior(altura(no->right), (*raiz)->altura) + 1;
  *raiz = no;
  printf("Rotação RR realizada com sucesso!\n");
  pause();
}
//Left Right (aplica R e L)
void LR(treeRaiz *raiz){
  printf("Rotação LR (RR (aplica L) e LL (aplica R))\n");
  printf("|      -x-    |       -q-       |\n");
  printf("|  -y-      w |   -y-      x-   |\n");
  printf("|z    -q      |  z   F       w |\n");
  printf("|    F        |                 |\n");
  RR(&(*raiz)->left);
  LL(raiz);
  printf("Rotação LR realizada com sucesso!\n");
  pause();
}
//Right Left (Aplica L e R)
void RL(treeRaiz *raiz){
  printf("Rotação RL (LL (aplica R) e RR (aplica L))\n");
  printf("|     -a-       |       -d-       |\n");
  printf("|  b      -c-   |   -a      -c-   |\n");
  printf("|       d-    e | b        F   e |\n");
  printf("|         F     |                 |\n");
  LL(&(*raiz)->right);
  RR(raiz);
  printf("Rotação RL realizada com sucesso!\n");
  pause();
}

int inserir(treeRaiz *raiz, int valor){
  int rt;
  if(*raiz == NULL){ //Árvore vazia ou nó folha
      TpNodo *new = (TpNodo*)malloc(sizeof(TpNodo));
      if(new == NULL){ //Verificar se alocou memória, se sim será != de NULL
        return 0;
      }
      new->chave = valor;
      new->altura = 0;
      new->left = NULL;
      new->right = NULL;
      *raiz = new;
      return 1;
  }
  TpNodo *atual = *raiz;
  if(valor < atual->chave){ //Se valor menor que atual vai pro lado esquerdo da raiz
    if((rt = inserir(&(atual->left), valor)) == 1){ //if que faz recursividade com função inserir até encontrar o nó folha
      if(balanceamento(atual) >= 2){ //if pra verificar o fator de balanceamente se >= 2 (função retorna absoluto)
        if(valor < (*raiz)->left->chave){ //Se valor menor que seu father, então
          LL(raiz);
        }else{ //Se valor maior que seu father, então
          LR(raiz);
        }
      }
    }
  }else{ //Se valor maior que atual vai pro lado direito da raiz
    if(valor > atual->chave){
      if((rt = inserir(&(atual->right), valor)) == 1){ //if que faz recursividade com função inserir até encontrar o nó folha
        if(balanceamento(atual) >= 2){ //if pra verificar o fator de balanceamente se >= 2 (função retorna absoluto)
          if((*raiz)->right->chave < valor){ //Se valor maior que father
            RR(raiz);
          }else{ //Se valor menor que father
            RL(raiz);
          }
        }
      }
    }else{ //Se valor já existe na árvore
      printf("Já existe essa chave...\n");
      pause();
      return 0;
    }
  }
  atual->altura = maior(altura(atual->left), altura(atual->right)) + 1; //Altura total da árvore pega maior altura do lado direito/esquerdo +1
  return rt;
}

int listar(treeRaiz *raiz, int i, treeRaiz *father){
  int rt;
  if(*raiz == NULL){ //Verifica até chegar na primeira altura e começar a retornar recursividade
      return 1;
  }
  TpNodo *atual = *raiz;
  if((rt = listar(&(atual->left), i, &(atual))) == 1){ //começar recursividade a esquerda
    if((*raiz)->chave < (*father)->chave){
        printf("|Height-Child: %d| |Child-Left: %d|\n", (*raiz)->altura, (*raiz)->chave);
    }else if((*raiz)->chave > (*father)->chave){
      printf("|Height-Child: %d| |Child-Right: %d|\n", (*raiz)->altura, (*raiz)->chave);
    }
    printf("|Height-Father: %d| | Father: %d|\n\n", (*father)->altura, (*father)->chave);
    i = 1; //significa que é o ultimo nó a esquerda e que já foi imprimido
  }if((rt = listar(&(atual->right), i, &(atual))) == 1){ //faz as recursividades a direita
    if(i == 1){ //verifica se já foi imprimido e retorna 1 para voltar mais uma chamada recursiva
      return 1;
    }
  }
  return rt;
}

int main() {
  treeRaiz *raiz = inicializa();
  int menu, valor, y, i = -1;

  do{
    system("clear");
    printf("1-Inserir elemento:\n");
    printf("2-Listar elementos:\n");
    printf("0-Encerrar\n");
    scanf("%d", &menu);
    switch(menu){
      case 1: printf("\nValor a ser inserido: ");
              scanf("%d", &valor);
              int x = inserir(raiz, valor); break;
      case 2: y = listar(raiz, i, raiz);
              pause();
              break;
    }
  }while(menu);
  return 0;
}
