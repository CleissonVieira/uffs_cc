#include "types.h"
#include "user.h"

#define N 6

int main(){
    int pid, i, x;

    for (i = 0, x = 50; i < N; i++, x += 50){
        pid = fork(x);
        if(pid == 0){
            for(;;){
            }
            exit();
        }
    }
    while(1){
      pid = wait();
      if(pid < 0) break;
    }
    exit();
}
