#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio_ext.h>

#define T 2
#define MaxChaves 3 //2*t-1
#define MaxFilhos 4 //2*t
#define MinOcup 1   //t-1

typedef struct noB arvoreB;

struct noB {
  int quantChaves;
  int chaves[MaxChaves];
  arvoreB *filhos[MaxFilhos];
}noB;

//PAUSAR PARA VERIFICAR
void pause(){
    printf("Press enter for next...\n");
    __fpurge(stdin);
    getchar();
}

//FUNÇÃO PARA ENCONTRAR UM NODO (POSIÇÃO DO VETOR) NULL PARA INSERIR
int pesquisa(arvoreB *nodo, int chave){
  int meio, i = 0, j = nodo->quantChaves - 1; //j = nodo->quantChaves posição do último valor inserido antes do Null
  while(i <= j){
    meio = (i + j) / 2;
    if(nodo->chaves[meio] == chave){ //Já existe esse valor, retorna a posição
      return meio;
    }else if(nodo->chaves[meio] > chave){ //Verificar se valor a ser inserido é maior ou menor para retornar posição
      j = meio - 1;
    }else{    //Retorna posição para inserir o filho
      i = meio + 1;
    }
  }
  return i;
}

//INSERE A CHAVE, ORDENA AS CHAVES, E INSERE O PONTEIRO PARA O FILHO DA DIREITA EM UM NÓ
void insereChave(arvoreB *raiz, int chave, arvoreB *filho){
  int pos = pesquisa(raiz, chave);
  int nChaves = raiz->quantChaves;
  while(nChaves > pos && chave < raiz->chaves[nChaves - 1]){  //Ordena as chaves
    raiz->chaves[nChaves] = raiz->chaves[nChaves - 1];
    raiz->filhos[nChaves + 1] = raiz->filhos[nChaves];
    nChaves--;
  }
  raiz->chaves[pos] = chave;  //Insere as chaves
  raiz->filhos[pos + 1] = filho;
  raiz->quantChaves++;
}

//ENCONTRA UM NODO VÁLIDO PARA FAZER INSERÇÃO
arvoreB *insere(arvoreB *raiz, int chave, bool *x, int *chaveReturn){
  int i, j, pos, infoMedio;
  arvoreB *noSplit, *filho;
  if(raiz == NULL){		//Checou se o nó que veio é null (raiz/primeiro) para poder inserir, retorna o Null e a chaveReturn
    *x = true;
    *chaveReturn = chave;
    return NULL;
  }else{
    pos = pesquisa(raiz, chave); //Se raiz for diferente de Null significa que já tem elemento, então precisa pesquisar um Null pra inserir
    if(raiz->quantChaves > pos && raiz->chaves[pos] == chave){   //pos == posição da ultima chave inserida, se for igual já existe esse valor
      printf("\nChave repetida, por favor insira uma nova chave...\n");
      *x = false;
      pause();
    }else{
      filho = insere(raiz->filhos[pos],chave,x,chaveReturn); //Aplica recursividade até pesquisar nó folha
      if(*x){ 		//Se x == true encontrou folha == null pra inserir
      	if(raiz->quantChaves < MaxChaves){	 //Se quantChaves ainda não está cheia, insere ao lado
      	  insereChave(raiz, *chaveReturn, filho);
      	  *x = false;
      	}else{ 	 //Se quantidade máxima de chaves foi alcançada (split)
            noSplit = (arvoreB *) malloc (sizeof(arvoreB));
            noSplit->quantChaves = 0;
            for(i = 0; i < MaxFilhos; i++){
              noSplit->filhos[i] = NULL;
            }
            infoMedio = raiz->chaves[MinOcup]; //Chave que vai subir/quebrar para o pai
            noSplit->filhos[0] = raiz->filhos[MinOcup + 1]; //insere metade do nó raiz no noSplit (split)
            for(i = MinOcup + 1; i < MaxChaves; i++){
              insereChave(noSplit, raiz->chaves[i], raiz->filhos[i + 1]);
            }
            for(i = MinOcup; i<MaxChaves; i++){ //Atualiza Raiz
              raiz->chaves[i] = 0;
              raiz->filhos[i+1] = NULL;
            }
            raiz->quantChaves = MinOcup;
            if(pos <= MinOcup){   //Verifica em qual nó sera inserida a nova chave
              insereChave(raiz, *chaveReturn, filho);
            }else{
              insereChave(noSplit, *chaveReturn, filho);
            }
            *chaveReturn = infoMedio; //retorna o mediano para inseri-lo no nó pai e o noSplit como filho direito do mediano
            return(noSplit);
      	}
      }
    }
  }
}

//FUNÇÃO PRINCIPAL, ONDE TUDO INICIA PARA INSERIR CHAVE
arvoreB *RealizaInsert(arvoreB *raiz, int chave){
  bool x;
  int chaveReturn, i;
  arvoreB *filho, *newRaiz;
  filho = insere(raiz, chave, &x, &chaveReturn);
  if(x){ 	//Se x == true significa que encontrou uma posição do vetor Null, então retorna
    newRaiz = (arvoreB *) malloc (sizeof(arvoreB));
    newRaiz->quantChaves = 1;
    newRaiz->chaves[0] = chaveReturn;
    newRaiz->filhos[0] = raiz;
    newRaiz->filhos[1] = filho;
    for (i = 2; i <= MaxChaves; i++){
      newRaiz->filhos[i] = NULL;     // Retorna para a Main a próxima posição Null do vetor pra recomeçar o ciclo de inserção
    }
    return(newRaiz);
  }
  else{
    return (raiz);
  }
}

//IMPRIMIR OS ELEMENTOS
void imprimir(arvoreB *raiz, int n){
  int i, j;
  if(raiz != NULL){
    for(i = 0; i < raiz->quantChaves; i++){
      imprimir(raiz->filhos[i], n+1);
      for(j = 0; j < n; j++){
        printf("---");
      }
      printf("%d<\n", raiz->chaves[i]);
    }
    imprimir(raiz->filhos[i], n+1);
  }
}

int main(void){
  int menu, chave;
  arvoreB *arvore = NULL;
  do{
    system("clear");
    printf("1-Inserir elemento:\n");
    printf("2-Listar elementos:\n");
    printf("0-Encerrar\n");
    printf("\nOpção desejada:  ");
    scanf("%d", &menu);
    switch (menu){
        case 1:
          printf("\nValor a ser inserido:  ");
          scanf("%d", &chave);
          arvore = RealizaInsert(arvore, chave);
          break;
        case 2:
          printf("\nÁRVORE B:\n\n");
          imprimir(arvore, 1);
          printf("\n");
          pause();
          break;
        case 0:
          menu = 0;
          break;
    }
  } while (menu);
  return 0;
}
