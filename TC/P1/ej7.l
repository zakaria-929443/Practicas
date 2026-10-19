 /* Practica 1 TC - Ejercicio 7
    Autores: Nombre Apellidos (NIP), Nombre Apellidos (NIP)
    La categoria (OK / F_1 / F_2 / F_3) se decide SOLO con la estructura de la
    expresion regular (numero de P agrupados de 3 en 3), sin contadores en C ni
    operacion modulo. En la accion solo se eliminan las C de la salida. */
%{
#include <stdio.h>
void emitir(const char* marca) {
    printf("%s", marca);
    for (char* p = yytext; *p != '\0'; p++) {
        if (*p != 'C') putchar(*p);
    }
    printf("%s\n", marca);
}
%}
%%
B(C*PC*PC*P)+C*E       { emitir("[OK]"); }
B(C*PC*PC*P)*C*PC*E    { emitir("[F_1]"); }
B(C*PC*PC*P)*C*PC*PC*E { emitir("[F_2]"); }
BC*E                   { emitir("[F_3]"); }
.|\n                   { /* se suprime el resto del texto */ }
%%
