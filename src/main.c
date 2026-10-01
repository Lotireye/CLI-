#include "gestorcomandos.h"
#include "procesartextos.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void manejarSigint(int senal);

int main() {

  char *linea = malloc(1024 * sizeof(char));
  char **argumentos;
  int seguir;

  struct sigaction sa;
  sa.sa_handler = manejarSigint;
  sa.sa_flags = 0;
  sigemptyset(&sa.sa_mask);
  sigaction(SIGINT, &sa, NULL);

  do {
    printf("LotShell>");
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

void manejarSigint(int senal) { write(STDOUT_FILENO, "\n", 1); }
