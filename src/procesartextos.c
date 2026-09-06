#include "procesartextos.h"
#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

char **parsear(const char *input) {
  int longitudString = strlen(input);
  int cantidad = 0;
  int dentroPalabra = 0;

  for (int i = 0; i <= longitudString; i++) {
    if (!isspace(input[i]) && dentroPalabra == 0 && input[i] != '\0') {
      dentroPalabra = 1;
      cantidad++;
    } else if (isspace(input[i]) || input[i] == '\0') {
      dentroPalabra = 0;
    }
  }

  char **argumentos = malloc((cantidad + 1) * sizeof(*argumentos));
  if (argumentos == NULL) {
    return NULL;
  }

  dentroPalabra = 0;
  int inicio = 0;
  int indiceArg = 0;

  for (int i = 0; i <= longitudString; i++) {
    if (!isspace(input[i]) && dentroPalabra == 0 && input[i] != '\0') {
      dentroPalabra = 1;
      inicio = i;
    } else if ((isspace(input[i]) || input[i] == '\0') && dentroPalabra == 1) {
      int longitudPalabra = i - inicio;

      argumentos[indiceArg] = malloc(longitudPalabra + 1);
      if (argumentos[indiceArg] == NULL) {
        return NULL;
      }

      strncpy(argumentos[indiceArg], input + inicio, longitudPalabra);
      argumentos[indiceArg][longitudPalabra] = '\0';

      indiceArg++;
      dentroPalabra = 0;
    }
  }

  argumentos[cantidad] = NULL;

  return argumentos;
}

void liberar(char **argumentos) {
  for (int i = 0; argumentos[i] != NULL; i++) {
    free(argumentos[i]);
  }
  free(argumentos);
}
