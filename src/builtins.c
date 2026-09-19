#include "builtins.h"
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int cd(char **argumentos) {
  if (argumentos[1] == NULL) {
    printf("cd: missing argument\n");
    return 1;
  }
  if (chdir(argumentos[1])) {
    perror("cd");
    return 1;
  } else {
    return 0;
  }
}

int pwd(void) {
  char buffer[PATH_MAX];
  if (getcwd(buffer, PATH_MAX) == NULL) {
    perror("pwd");
    return 1;
  }
  printf("%s\n", buffer);
  return 0;
}
int export(char **argumentos) {
  if (argumentos[1] == NULL) {
    printf("export: missing argument\n");
    return 1;
  }
  char *igual = strchr(argumentos[1], '=');
  if (igual == NULL) {
    printf("export: not valid argument\n");
    return 1;
  }
  int longitudNombre = igual - argumentos[1];
  char nombre[longitudNombre + 1];
  strncpy(nombre, argumentos[1], longitudNombre);
  nombre[longitudNombre] = '\0';
  char *valor = igual + 1;
  if (setenv(nombre, valor, 1)) {
    perror(argumentos[0]);
    return 1;
  }
  return 0;
}

int unset(char **argumentos) {
  if (argumentos[0] == NULL) {
    printf("unset: missing argument\n");
    return 1;
  }
  if (unsetenv(argumentos[1])) {
    perror(argumentos[0]);
  }
  return 0;
}
void env(void) {
  extern char **environ;

  for (char **env = environ; *env != NULL; env++) {
    printf("%s\n", *env);
  }
}

void help(void) {
  printf("exit\n");
  printf("cd\n");
  printf("pwd\n");
  printf("export\n");
  printf("unset\n");
  printf("env\n");
  printf("help\n");
}
