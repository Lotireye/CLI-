#ifndef BUILTINS_H
#define BUILTINS_H

int cd(char **argumentos);
int pwd(void);
int export(char **argumentos);
int unset(char **argumentos);
void env(void);
void help(void);

#endif // !BUILTINS
