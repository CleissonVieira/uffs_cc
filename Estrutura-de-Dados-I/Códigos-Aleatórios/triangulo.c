#include <stdio.h>
#include <stdlib.h>

int area(int x1, int y1, int x2, int y2, int x3, int y3){
   return abs((x1*(y2-y3) + x2*(y3-y1)+ x3*(y1-y2))/2.0);
}

int teste(int x1, int y1, int x2, int y2, int x3, int y3, int x, int y){   
   int a, b, c, d;
   a = area(x1, y1, x2, y2, x3, y3);
   b = area(x, y, x2, y2, x3, y3);
   c = area(x1, y1, x, y, x3, y3);
   d = area(x1, y1, x2, y2, x, y);
   return (a == b + c + d);
}

int main(){
   int x[10], y[10], j, i;
   printf("Digite os valores dos vértices:\n");
   printf("Primeiro: \n");
   scanf("%d %d", &y[0], &x[0]);
   printf("Segundo: \n");
   scanf("%d %d", &y[1], &x[1]);
   printf("Terceiro: \n");
   scanf("%d %d", &y[2], &x[2]);
   system("clear");
   for(i = 0; i < 50; i++){
      for(j = 0; j < 50; j++){
         printf(teste(y[0], x[0], y[1], x[1], y[2], x[2], i, j) ? "@" : "-");
      }
      printf("\n");
   }
   return 0;
}