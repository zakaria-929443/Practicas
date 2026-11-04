%option noyywrap

%{
#include <stdio.h>

int lineas_c = 0;         /* C1: lineas dentro de bloques %{ ... %} */
int lineas_acciones = 0;  /* C2: lineas dentro de las acciones      */
int lineas_codigo = 0;    /* C3: lineas de la seccion de codigo     */
int reglas = 0;           /* R:  numero de reglas                   */
%}

%%

\n    { lineas_codigo++; }   /* cada salto de linea suma 1 */
.     { }                    /* cualquier otro caracter se ignora */

%%

int main() {
    yylex();    /* lee toda la entrada */
    printf("C1:%d\n", lineas_c);
    printf("C2:%d\n", lineas_acciones);
    printf("C3:%d\n", lineas_codigo);
    printf("R:%d\n", reglas);
    return 0;
}
