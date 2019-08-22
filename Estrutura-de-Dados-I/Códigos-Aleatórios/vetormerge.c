#include <stdio.h> 
#include <stdlib.h> 

void lerVet( int *p, int t ){

	int i, meio;

	for (i = 0; i < 1; ) {

		meio = t / 2;
		mergeSort(p, meio);
		mergeSort(p + meio, t - meio);
		merge(p, t);

	}
}


void main(){

	int *p, tam;

	printf("Quantidade de elementos do vetor?");
	scanf("%d",&tam);

	p = (int*) malloc(tam * sizeof(int));
	
	printf("\nDigite o conteudo do vetor:\n");
	lerVet(p, tam);

	printf("\nConteudo digitado para o vetor:\n");
	mostrarVet(p, tam);

	printf("\nOrdenando o vetor...\n");
	mergeSort(p, tam);

	printf("\nConteudo do vetor ja ordenado:\n");
	mostrarVet(p, tam);

	free(p);

}