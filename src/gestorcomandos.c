#include "gestorcomandos.h"
#include "builtins.h"
#include "procesos.h"
#include <string.h>

int analizarComando(char **argumentos) {
  // Built ins
  if (argumentos[0] == NULL) {
    return 1;
  }
  if (!strcmp(argumentos[0], "exit")) {
    return 0;
  } else if (!strcmp(argumentos[0], "cd")) {
    cd(argumentos);
    return 1;
  } else if (!strcmp(argumentos[0], "pwd")) {
    pwd();
    return 1;
  } else if (!strcmp(argumentos[0], "export")) {
    export(argumentos);
    return 1;
  } else if (!strcmp(argumentos[0], "unset")) {
    unset(argumentos);
    return 1;
  } else if (!strcmp(argumentos[0], "env")) {
    env();
    return 1;
  } else if (!strcmp(argumentos[0], "help")) {
    help();
    return 1;
  } else {
    int indice = buscarPipe(argumentos);
    if (indice != -1) {
      ejecutarPipe(argumentos, indice);
    } else {
      ejecutarProceso(argumentos);
    }
    return 1;
  }
  return 1;
}

int buscarPipe(char **argumentos) {
  for (int i = 0; argumentos[i] != NULL; i++) {
    if (!strcmp(argumentos[i], "|")) {
      return i;
    }
  }
  return -1;
}
