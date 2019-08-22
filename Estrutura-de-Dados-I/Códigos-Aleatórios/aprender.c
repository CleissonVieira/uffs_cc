#include <stdlib.h>
#include <stdio.h>

int main(){
	int *vetor, *vetorN, i, numero, j;
	printf("Digite cada sequencia de número seguido de enter:\n");
	printf("(Digite 0 para interromper e printar)\n");
	scanf("%d", &numero);
	vetor = (int *) malloc(5*sizeof(int));
	for(i=0; ; i++){
		if(numero!=0){
			*(vetor+i)=numero;
			if((i+1)%5==0 && i!=0){
				printf("Realocou\n");
				vetorN=(int *) realloc(vetor, (i+5)*sizeof(int));
				vetor=vetorN;
			}
			scanf("%d", &numero);
		}else{
			system("clear");
			break;
		}
	}
	for(j=0; j<i; j++){
		printf("Posição = %d | Conteúdo = %d\n", (j+1), *(vetor+j));
	}
	free(vetor);
	free(vetorN);
	return 0;
}