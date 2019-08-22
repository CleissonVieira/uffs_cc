#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio_ext.h>

int BuscaBinRec(int vetor[], int ini, int fim, int x){
 	while(ini <= fim){
 		int meio;
 		if(fim == meio && meio != x){
 			break;
 		}
  		meio = (ini + fim) / 2;
  		if(vetor[meio] == x){
  	//verifica se o meio é igual ao valor desejado para retornar a posição
		   return meio+1;
		}
		else if (vetor[meio] < x){ 
	//verifica se valor desejado é maior que o meio
	//retorno do meio+1 será o novo inicio
		   return BuscaBinRec(vetor, meio+1, fim, x);
		}
		else{
	//se não for maior então é menor
	//retorno do meio-1 será o novo fim
		   return BuscaBinRec(vetor, ini, meio-1, x);
		}
 	}
 	printf("Não encontrado\n");
}

void Ordena(int vetor[]){
	int i, j, aux; 
        for(i = 0; i < 5; i++){
            for(j = i + 1; j < 5; j++){
                if( vetor[i] > vetor[j] ){
                    aux = vetor[i];
                    vetor[i] = vetor[j];
                    vetor[j] = aux;
                } 
            }
        }
}

  
int main (){
 	int vetor[5] = {0 ,0 ,0 ,0 ,0}, final, x, i, j;
 	for(i = 0; i < 5; i++){
 		scanf("%d", &vetor[0]);
 		Ordena(vetor);
 	}
 	printf("Vetor Ordenado: ");
 	for(j = 0; j < 5; j++){
 			printf("|%d", vetor[j]);
 	}
 	printf("| \n");
 	printf("Informe o valor a ser encontrado: ");
 	scanf("%d", &x);
 	final = BuscaBinRec(vetor,0,4,x);
 	if(final <= 5){
 		printf("Número informado se encontra na %dº posição do Vetor\n", final);
 	}
 return 0;
}