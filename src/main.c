#include "procesartextos.h"
#include <stdio.h>

int main() {
  char *linea = "ls -la /home";
  char **argumentos = parsear(linea);
  for (int i = 0; argumentos[i] != NULL; i++) {
    printf("%s \n", argumentos[i]);
  }
  liberar(argumentos);
  return 0;
}
