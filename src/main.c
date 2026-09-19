#include "gestorcomandos.h"
#include "procesartextos.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  char *linea = malloc(1024 * sizeof(char));
  char **argumentos;
  int seguir;

  do {
    printf(">");
    fgets(linea, 1024, stdin);
    argumentos = parsear(linea);
    if (argumentos == NULL) {
      perror("malloc");
      exit(1);
    }
    seguir = analizarComando(argumentos);
    liberar(argumentos);
  } while (seguir);

  free(linea);
  return 0;
}
