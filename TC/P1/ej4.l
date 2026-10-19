 /* Practica 1 TC - Ejercicio 4
    Autores: Nombre Apellidos (NIP), Nombre Apellidos (NIP) */
%{
#include <stdio.h>
#include <stdlib.h>
%}
%%
[0-9]    { int n = atoi(yytext); printf("%d", n + 1); }
\n       { printf("\n\n"); }
%%
