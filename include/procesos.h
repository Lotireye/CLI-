#ifndef PROCESOS_H
#define PROCESOS_H

void ejecutarProceso(char **argumentos);
int extraerRedireccion(char **argumentos, char **archivoSalida);
void ejecutarPipe(char **argumentos, int indicePipe);

#endif
