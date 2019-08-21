#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
int cor = 7;
int main(int argc, char const *argv[]){
    int matrizAdjacencia[11][11] = {
        //   a  b  c  d  e  f  g  h  i  j  k (aresta)
        /*A*/0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0,
        /*B*/1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
        /*C*/0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
        /*D*/0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1,
        /*E*/0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1,
        /*F*/0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0,
        /*G*/0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1,
        /*H*/1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1,
        /*I*/0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0,
        /*J*/0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1,
        /*K*/0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0
        //(vértice)
    };
    int grau[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int grauOr [11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int corv[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int count = 0;
    for(int i = 0; i < 11; i++){
        count = 0;
        for(int j = 0; j < 11; j++){
            if(matrizAdjacencia[i][j] == 1){
                count++;
            }
        }
        grau[i] = count;
        grauOr[i] = count;
    }
    for (int i = 1; i < 11; i++) {
        for (int j = 0; j < i; j++) {
            if (grauOr[i] > grauOr[j]) {
                int temp = grauOr[i];
                grauOr[i] = grauOr[j];
                grauOr[j] = temp;
            }
        }
    }
    for( ; ; ){
        for(int i = 0; i < 11; i++){
            if(grauOr[i] > 0){
                for(int j = 0; j < 11; j++){
                    if(grauOr[i] == grau[j] && corv[j] == 0){
                        corv[j] = cor;
                        int count = 0;
                        for(int k = 0; k < 11; k++){
                            if(matrizAdjacencia[j][k] == 1){
                                if(corv[k] == corv[j]){
                                    count ++;
                                }
                            }
                            if(count > 0){
                                corv[j] = 0;
                                break;
                            }
                        }
                        if(count == 0){
                            grauOr[i] *= -1;
                            grau[j] *= -1;
                        }
                    }
                }
            }
        }cor++;
        if(cor >= 10)
            break;
    }
    printf("\n\nVertices:   A B C D E F G H I J K");
    printf("\nGrau dos V: ");
    for(int i = 0; i < 11; i++){
        printf("%d ", grau[i]*-1);
    }printf("\nCor dos V:  ");
    for(int i = 0; i < 11; i++){
        printf("%d ", corv[i]);
    }printf("\n\nGrau Ordenado: ");
    for(int i = 0; i < 11; i++){
        printf("%d ", grauOr[i]*-1);
    }printf("\n\n\n");
    return 0;
}
