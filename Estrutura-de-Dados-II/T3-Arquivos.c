#include <stdio.h>
#include <stdlib.h>
#include <stdio_ext.h>

typedef struct TpProduto{
    char codigo[10];
    char nome[50];
    char preco[10];
}TpProduto;

void pause(){
    printf("Press enter for next...\n");
    __fpurge(stdin);
    getchar();
}

void listar(FILE *arquivo){
    arquivo = fopen("produtos.txt", "rb");
    char frase[100];
    printf("\nTODOS OS PRODUTOs");
    while (fgets(frase, 100, arquivo) != NULL){
        printf("%s", frase);
    }
    printf("-\n-----------------------------------------\n");
    fclose(arquivo);
} 

void inserir(FILE *arquivo, TpProduto *produto){
    arquivo = fopen("produtos.txt", "ab");
    printf("\nCADASTRANDO PRODUTO");
    printf("\nCódigo: ");
    fprintf(arquivo, "\n------------------------------------------\nCódigo: ");
    scanf("%s", &produto->codigo);
    fputs(produto->codigo, arquivo);
    printf("Nome: ");
    fprintf(arquivo, "\nNome: ");
    scanf("%s", &produto->nome);
    fputs(produto->nome, arquivo);
    printf("Preço: ");
    fprintf(arquivo, "\nPreço: ");
    scanf("%s", &produto->preco);
    fputs(produto->preco, arquivo);
    fclose(arquivo);
}

int main(){
    FILE *arquivo;
    TpProduto *produto = (TpProduto *)malloc(sizeof(TpProduto));
    arquivo = fopen("produtos.txt", "wb");
    int menu;
    do{
        system("clear");
        printf("1-Inserir produto:\n");
        printf("2-Listar produtos:\n");
        printf("0-Encerrar\n");
        scanf("%d", &menu);
        switch (menu){
        case 1:
            inserir(arquivo, produto);
            break;
        case 2:
            listar(arquivo);
            printf("\n");
            pause();
            break;
        }
    } while (menu);
    fclose(arquivo);
    return 0;
}