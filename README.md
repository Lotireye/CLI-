# Command Line Interface
Un CLI (intérprete de línea de comandos) interactivo escrito en C puro, con arquitectura modular, que progresivamente incorpora funcionalidades propias de un shell tipo Unix.

## Objetivo

Construir un shell funcional desde cero, entendiendo en profundidad los conceptos que lo hacen posible: manejo manual de memoria, punteros, procesamiento de strings, creación y gestión de procesos, llamadas al sistema y manejo de errores a bajo nivel — todo lo que un lenguaje como Java resuelve por vos y que en C hay que construir explícitamente.

## Funcionalidad objetivo

```text
mycli> pwd
/home/user

mycli> cd proyectos
mycli> ls -la
mycli> echo hola > archivo.txt
mycli> cat archivo.txt
mycli> ls | grep ".c"
mycli> exit
```

Es decir, un shell capaz de: interpretar comandos, ejecutar tanto comandos internos (builtins) como programas externos, redirigir salida a archivos, encadenar procesos con pipes, y manejar señales del usuario (`Ctrl+C`, `Ctrl+Z`).

## Estado

Funcional de punta a punta: parser de comandos, builtins (`cd`, `pwd`, `exit`, `help`, `export`, `unset`, `env`), ejecución de programas externos vía `fork`/`execvp`/`waitpid`, redirección de salida (`>`) y pipes (`|`, con soporte para dos comandos encadenados). Queda pendiente el manejo de señales.

Limitaciones conocidas: sin historial de comandos ni edición de línea con flechas (requeriría integrar GNU Readline o libedit en vez de `fgets`); el parser no interpreta comillas, así que argumentos con espacios o caracteres especiales entre comillas (`grep ".c"`) se pasan literalmente con las comillas incluidas.

## Arquitectura

```text
Usuario → main.c (leer input)
             ↓
      procesartextos.c (PARSER) → char **argv
             ↓
      gestorcomandos.c (DECISIÓN)
        ├── builtin   → builtins.c
        └── externo   → procesos.c
```

```text
mi-cli/
├── include/
│   ├── builtins.h
│   ├── gestorcomandos.h
│   ├── procesartextos.h
│   └── procesos.h
│
└── src/
    ├── builtins.c
    ├── gestorcomandos.c
    ├── procesartextos.c
    ├── procesos.c
    └── main.c
```

- **main.c** — ciclo principal del shell: mostrar prompt, leer entrada, procesarla, ejecutarla, repetir.
- **procesartextos.c** — parser. Convierte la línea de texto ingresada por el usuario en un arreglo de argumentos (`char **`, estilo `argv`) que el resto del programa pueda usar.
- **gestorcomandos.c** — punto de decisión del shell. Determina si un comando es interno (builtin) o un programa externo, y delega la ejecución al módulo correspondiente, sin ejecutar nada él mismo.
- **builtins.c** — comandos que deben ejecutarse dentro del propio proceso del shell porque modifican su estado (por ejemplo `cd`, que no tendría efecto si se ejecutara en un proceso hijo): `cd`, `pwd`, `exit`, `export`, `unset`, `env`, `help`.
- **procesos.c** — ejecución de programas externos del sistema mediante creación de procesos (`fork`, `exec`, `wait`).

## Roadmap

1. CLI básico — prompt interactivo y lectura de comandos
2. Parser de la entrada del usuario
3. Gestor de comandos (builtin vs. externo)
4. Comandos internos (builtins)
5. Ejecución de procesos externos
6. Manejo de errores
7. Redirecciones de entrada/salida (`>`, `<`)
8. Pipes (`|`)
9. Manejo de señales (`Ctrl+C`, `Ctrl+Z`)

## Filosofía del proyecto

No busca ser una reimplementación de un shell existente, sino un ejercicio de construcción incremental: cada etapa se diseña, se implementa y se prueba antes de pasar a la siguiente, priorizando buenas prácticas de C — gestión correcta de memoria, separación de responsabilidades entre módulos y manejo explícito de errores.
Un CLI (intérprete de línea de comandos) interactivo escrito en C puro, con arquitectura modular, que progresivamente incorpora funcionalidades propias de un shell tipo Unix.

o (builtin) o un programa externo, y delega la ejecución al módulo correspondiente, sin ejecutar nada él mismo.
- **builtins.c** — comandos que deben ejecutarse dentro del propio proceso del shell porque modifican su estado (por ejemplo `cd`, que no tendría efecto si se ejecutara en un proceso hijo): `cd`, `pwd`, `exit`, `export`, `unset`, `env`, `help`.
- **procesos.c** — ejecución de programas externos del sistema mediante creación de procesos (`fork`, `exec`, `wait`).

## Roadmap

1. CLI básico — prompt interactivo y lectura de comandos
2. Parser de la entrada del usuario
3. Gestor de comandos (builtin vs. externo)
4. Comandos internos (builtins)
5. Ejecución de procesos externos
6. Manejo de errores
7. Redirecciones de entrada/salida (`>`, `<`)
8. Pipes (`|`)
9. Manejo de señales (`Ctrl+C`, `Ctrl+Z`)
