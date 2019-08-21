#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//5 == ⊲ (start)
//4 == u (espaço em branco)
void meio(int fim, int *fita){
    for(int i = 0; i < fim; i++){
        printf("%d", fita[i]);
    }
    printf(",");
}
void fim(int inicio, int *fita, int fim){
    for(int i = inicio; i < fim; i++){
        printf("%d", fita[i]);
    }
    printf(") --> \n");
}

main(int argc, char const *argv[]){
    int TamF;
    char *estado = "q0";
    printf("Tamanho da Fita:\n");
    scanf("%d", &TamF);
    TamF += 2;
    int fita[TamF];
    printf("Digite a Fita (inicie com o n5, digite sua fita e finalize com  o n4):\n");
    for(int j = 0; j < TamF; j++){
        scanf("%d", &fita[j]);
    }
    printf("---------------COMECO-----------------\n");
    for(int i = 0;;){
        //ESTADO Q0
        if(estado == "q0" && fita[i] == 5){
            printf("(%s, ", estado);
            printf("|> ");
            meio(i, fita);
            fim(i, fita, TamF);
            i++;
        }if(estado == "q0" && fita[i] == 1){
            printf("(%s, ", estado);
            printf("|> ");
            meio(i, fita);
            fim(i, fita, TamF);
            estado = "qli1";
            fita[i] = 5;
            i++;
        }if(estado == "q0" && fita[i] == 0){
            printf("(%s, ", estado);
            printf("|> ");
            meio(i, fita);
            fim(i, fita, TamF);
            estado = "qli0";
            fita[i] = 5;
            i++;
        }if(estado == "q0" && fita[i] == 4){
            printf("(%s, ", estado);
            printf("|> ");
            meio(i, fita);
            fim(i, fita, TamF);
            estado = "qsim";
            break;
        }//ESTADO QLI1 E QLI0
        if((estado == "qli1" || estado == "qli0") && (fita[i] == 0 || fita[i] == 1)){
            printf("(%s, ", estado);
            printf("|> ");
            meio(i, fita);
            fim(i, fita, TamF);
            i++;
        }if(estado == "qli1" && fita[i] == 4){
            printf("(%s, ", estado);
            printf("|> ");
            meio(i, fita);
            fim(i, fita, TamF);
            estado = "qte1";
            i--;
        }if(estado == "qli0" && fita[i] == 4){
            printf("(%s, ", estado);
            printf("|> ");
            meio(i, fita);
            fim(i, fita, TamF);
            estado = "qte0";
            i--;
        }//ESTADO QTE1 E QTE0 (qtest1 e qtest0)
        if((estado == "qte1" || estado == "qte0") && fita[i] == 5){
            printf("(%s, ", estado);
            printf("|> ");
            meio(i, fita);
            fim(i, fita, TamF);
            estado = "qsim";
            break;
        }if((estado == "qte1" && fita[i] == 0) || (estado == "qte0" && fita[i] == 1)){
            printf("(%s, ", estado);
            printf("|> ");
            meio(i, fita);
            fim(i, fita, TamF);
            estado = "qnao";
            break;
        }if((estado == "qte1" && fita[i] == 1) || (estado == "qte0" && fita[i] == 0)){
            printf("(%s, ", estado);
            printf("|> ");
            meio(i, fita);
            fim(i, fita, TamF);
            estado = "qvolt";
            fita[i] = 4;
            i--;
        }//ESTADO QVOLT (q<-)
        if(estado == "qvolt" && fita[i] == 5){
            printf("(%s, ", estado);
            printf("|> ");
            meio(i, fita);
            fim(i, fita, TamF);
            estado = "q0";
            i++;
        }if(estado == "qvolt" && (fita[i] == 1 || fita[i] == 0)){
            printf("(%s, ", estado);
            printf("|> ");
            meio(i, fita);
            fim(i, fita, TamF);
            i--;
        }if(estado == "qsim" || estado == "qnao"){

        }
    }
    printf("-----------Qsim || Qnao--------------");
    printf("\n(%s, ", estado);
    meio(1, fita);
    fim(1, fita, TamF-1);
    printf("---------------FIM-----------------");
    return 0;
}
