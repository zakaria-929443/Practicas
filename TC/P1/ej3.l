 /* Practica 1 TC - Ejercicio 3
    Autores: Nombre Apellidos (NIP), Nombre Apellidos (NIP)
    Se escapa el punto (\.) para que solo concuerde el literal "@unizar.es".
    Si se usara "@unizar.es" sin escapar, el '.' concordaria con cualquier
    caracter y una direccion como jrg@unizaroes.es se modificaria por error. */
%%
@unizar\.es    { printf("@gmail.com"); }
%%
