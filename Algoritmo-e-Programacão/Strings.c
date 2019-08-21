#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <string.h>
#include <ctype.h>

char *strupr(char *str)
{
  unsigned char *p = (unsigned char *)str;

  while (*p) {
     *p = toupper(*p);
      p++;
  }

  return str;
}

    //       EXERCICIO 1

void exercicio1(){
    printf("\n-----------------------------------------------\n");
    printf(">> Criptografador _ Codifica uma String <<\n");
    char codigo[50];
    int i;

    fgets(codigo, 50, stdin);

    for(i=0;  i<strlen(codigo); i++){
        codigo[i]+=5;
    }
    codigo[i-1]='\0';
    printf("%s\n", codigo);




}

    //        EXERCICIO 2

void exercicio2(){
    printf("\n-----------------------------------------------\n");
    printf(">> Descriptografador _ Decodifica uma String <<\n");
    char codigo[50];
    int i;

    fgets(codigo, 50, stdin);

    for(i=0;  i<strlen(codigo); i++){
        codigo[i]-=5;
    }
    codigo[i-1]='\0';
    printf("%s\n", codigo);


}


    //        EXERCICIO 3

void exercicio3(){
    printf("\n-----------------------------------------------\n");
    char palavra[50];
    printf(">> Converte Texto: Minusculas para Maiusculas <<\n");
    fgets(palavra, 50, stdin);
    strupr(palavra);
    printf("%s", palavra);
}

    //        EXERCICIO 4

void exercicio4(){
    printf("\n-----------------------------------------------\n");
    char primeira[40], segunda[40];
    printf(">> Concatenador de Frases <<\n");
    fgets(primeira, 40, stdin);
    strtok(primeira, "\n");
    fgets(segunda, 40, stdin);
    strcat(primeira, segunda);

    printf("%s\n", primeira);
}

    //         EXERCICIO 5

void exercicio5(){
    printf("\n-----------------------------------------------\n");
    printf(">> Escreva 10 valores inteiros e descubra quais sao primos! <<\n");
    int vetor[10], i, j, k, l ,soma;
    for(i=0; i<10; i++){
        scanf("%d", &vetor[i]);     //loop para escrever os n�meros do vetor
    }
    for(j=0; j<10; j++){
        printf("%d ", vetor[j]);    //loop pra imprimir o vetor
    }
    printf("\n");

    printf("\nQuais dos numeros acima sao primos?\n");
    for(k=0; k<10; k++){        //loop pra verificar se s�o primos
        soma=0;                 //zerar soma pra n�o interferir nas demais posi��es do vetor

        if(vetor[k]<=3 && vetor[k]>=2){              //condi��o para n�meros primos sem c�lculos
            printf("%d ", vetor[k]);

        }

        else{         //pegar n�meros acima de 3 para verificar se s�o primos, pois abaixo s�o!
            for(l=1; l<=sqrt(vetor[k]); l++){        //loop pra dividir at� a ra�z quadrada do n�mero
                if(vetor[k]%l==0){           //se resto for igual a zera soma recebe 1 e se tiver mais que 2 divisores ent�o n�o primo
                    soma++;
                }
            }
            if(soma<=1){                        //condi��o para imprimir os primos
                printf("%d ", vetor[k]);
            }
        }
    }
}

    //          EXERCICIO 6

void exercicio6(){
    printf("\n-----------------------------------------------\n");
    printf(">>Digite seu nome completo: <<\n");
    char nome[100], copia2[100], copia1[100], sobrenome[100];
    int i, j, k=0;
    getchar();
    fgets(nome, 50, stdin);

    strcpy(copia2, nome);
    char tamanho=strlen(nome);


    for (i=tamanho-1, j=0; nome[i]!=' '; i--, j++){ //for para pegar a ultima palagra e inverter ela
            copia1[j]=nome[i];
    }
    copia1[j]='\0'; //definir o final da string invertida

    for(i=strlen(copia1)-1; i>=0; i--){         //for para fazer a ultima palavra voltar ao normal
        sobrenome[k]=copia1[i];
        k++;
    }
    sobrenome[k-1]='\0';  //definir o final da string normalizada


    for(i=0; i<strlen(copia2);i++){         //for para pegar o primeiro nome digitado
        if(copia2[i]==' '){
            copia2[i]='\0';
        }
    }
    strcat(sobrenome,", ");
    strcat(sobrenome, copia2);
    printf("%s", sobrenome);
}


int main(){

    exercicio1();

    exercicio2();

    exercicio3();

    exercicio4();

    exercicio5();

    exercicio6();

    return 0;
}
