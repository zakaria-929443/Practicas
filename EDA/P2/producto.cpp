/* Nombre, apellidos y NIP del (de los) autor(es).
*/

#include "producto.hpp"

/* Dada una cadena nom y un entero c, devuelve un producto p de nombre nom y
cantidad c.
*/
void crear(string nom, int c, producto& p){
    p.nombre = nom;
    p.cantidad = c;
}

/* Dado un producto p, devuelve la cadena correspondiente a su nombre.
*/
string nombre(const producto& p){
    return p.nombre;
}

/* Dado un producto p, devuelve el entero correspondiente a su cantidad.
*/
int cantidad(const producto& p){
    return p.cantidad;
}

/* Devuelve verdad si y solo si los productos p1 y p2 tienen el mismo nombre.
*/
bool operator==(const producto& p1, const producto& p2){
    return (p1.nombre == p2.nombre);
}
