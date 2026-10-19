 /* Practica 1 TC - Ejercicio 2
    Autores: Nombre Apellidos (NIP), Nombre Apellidos (NIP) */
%{
#include <stdio.h>
int contador = 0;
%}
%%
@hotmail    { contador++; printf("%s", yytext); }
%%
int main() {
    int error = yylex();
    if (error == 0) {
        printf("Total de usuarios: %d\n", contador);
    }
    return error;
}
