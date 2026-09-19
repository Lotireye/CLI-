#include "procesos.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

void ejecutarProceso(char **argumentos) {
  pid_t pid = fork();
  if (pid == -1) {
    perror(argumentos[0]);
  } else if (pid == 0) {
    char *archivoSalida = NULL;
    if (extraerRedireccion(argumentos, &archivoSalida)) {
      int fd = open(archivoSalida, O_WRONLY | O_CREAT, O_TRUNC, 0644);
      if (fd == -1) {
        perror("open");
        exit(1);
      }
      dup2(fd, 1);
    }
    execvp(argumentos[0], argumentos);
    perror(argumentos[0]);
    exit(1);
  } else {
    waitpid(pid, NULL, 0);
  }
}

int extraerRedireccion(char **argumentos, char **archivoSalida) {
  for (int i = 0; argumentos[i] != NULL; i++) {
    if (!strcmp(argumentos[i], ">")) {
      *archivoSalida = argumentos[i + 1];
      argumentos[i] = NULL;
      return 1;
    }
  }
  return 0;
}

void ejecutarPipe(char **argumentos, int indicePipe) {
  argumentos[indicePipe] = NULL;
  char **comando2 = &argumentos[indicePipe + 1];
  int fds[2];
  pipe(fds);
  pid_t pid1 = fork();
  if (pid1 == 0) {
    dup2(fds[1], 1);
    close(fds[0]);
    close(fds[1]);

    execvp(argumentos[0], argumentos);
    perror(argumentos[0]);
    exit(1);
  }

  pid_t pid2 = fork();
  if (pid2 == 0) {
    dup2(fds[0], 0);
    close(fds[0]);
    close(fds[1]);

    execvp(comando2[0], comando2);
    perror(comando2[0]);
    exit(1);
  }

  close(fds[0]);
  close(fds[1]);
  waitpid(pid1, NULL, 0);
  waitpid(pid2, NULL, 0);
}
