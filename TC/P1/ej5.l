 /* Practica 1 TC - Ejercicio 5
    Autores: Nombre Apellidos (NIP), Nombre Apellidos (NIP)
    Procesa un log HTTP: anonimiza la IP en peticiones con error (4XX/5XX)
    y calcula las metricas P, S, E, A. */
%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int P = 0, S = 0, E = 0, A = 0;
%}

IP      [0-9]+\.[0-9]+\.[0-9]+\.[0-9]+

%%
{IP}[ ]+[A-Z]+[ ]+[^ \t\n]+[ ]+[0-9][0-9][0-9][ ]+[0-9]+ms    {
    char ip[64], metodo[16], ruta[256], tiempo[32];
    int codigo;
    sscanf(yytext, "%s %s %s %d %s", ip, metodo, ruta, &codigo, tiempo);
    P++;
    int esError = (codigo >= 400 && codigo <= 599);
    if (codigo >= 200 && codigo <= 299) S++;
    if (esError) E++;
    if (strncmp(ruta, "/api/", 5) == 0) A++;
    if (esError) printf("[ANON]");
    else printf("%s", ip);
    printf(" %s %s %d %s", metodo, ruta, codigo, tiempo);
}
%%
int main() {
    int error = yylex();
    if (error == 0) {
        printf("P:%d\n", P);
        printf("S:%d\n", S);
        printf("E:%d\n", E);
        printf("A:%d\n", A);
    }
    return error;
}
