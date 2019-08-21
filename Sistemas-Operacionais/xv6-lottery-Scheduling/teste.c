#include "types.h"
#include "stat.h"
#include "user.h"
#define OUTPUT_STREAM 1
int main(void) {
  int pid;
  pid = fork();
  if (pid) pid = fork();
  if (pid) pid = fork();
  if (pid) pid = fork();
  if (pid) pid = fork();
  if (pid) pid = fork();
  if (pid) pid = fork();
  if (pid) pid = fork();
  if (pid) pid = fork();
  if (pid) pid = fork();
  if (pid) pid = fork();
  if (pid) pid = fork();
  if (pid) pid = fork();
  if (pid) pid = fork();
  if (pid) pid = fork();
  if (pid) pid = fork();
  if (!pid) { // Se for o filho
    int i = 0;
    printf(OUTPUT_STREAM, "Filho: %d\n", getpid());
    while(i++ < 99999) {
      int j = 0;
      while(j++ < 1) {
        int b = getpid() * 5 / 3 + 7;
        b += b + getpid();
      }
    }
    // Imprime a saída
  } else if (pid > 0) {
    printf(OUTPUT_STREAM, "Pai: %d\n", getpid());
    printf(OUTPUT_STREAM, "Esperando filho terminar.\n");
    wait();
    printf(OUTPUT_STREAM, "filho terminou.\n");
  } else {
    printf(OUTPUT_STREAM, "Erro\n");
  }
  exit();
}