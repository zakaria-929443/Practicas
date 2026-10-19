/* Nombre, apellidos y NIP del (de los) autor(es).
*/

#ifndef PRODUCTO_HPP
#define PRODUCTO_HPP

#include<iostream>
using namespace std;

// PREDECLARACION DEL TAD producto (inicio INTERFAZ)

/* Los valores del TAD producto representan productos para los que se tiene
informacion de su nombre y su cantidad.
Dos productos se consideran iguales (con el operador ==) si tienen el mismo nombre.
*/
struct producto;

/* Dada una cadena nom y un entero c, devuelve un producto p de nombre nom y
cantidad c.
*/
void crear(string nom, int c, producto& p);

/* Dado un producto p, devuelve la cadena correspondiente a su nombre.
*/
string nombre(const producto& p);

/* Dado un producto p, devuelve el entero correspondiente a su cantidad.
*/
int cantidad(const producto& p);

/* Devuelve verdad si y solo si los productos p1 y p2 tienen el mismo nombre.
*/
bool operator==(const producto& p1, const producto& p2);


// FIN de la PREDECLARACION DEL TAD producto (fin INTERFAZ)

// DECLARACION DEL TAD producto

struct producto {
  friend void crear(string nom, int c, producto& p);
  friend string nombre(const producto& p);
  friend int cantidad(const producto& p);
  friend bool operator==(const producto& p1, const producto& p2);

  private:  //declaracion de la representacion interna del tipo
    string nombre;
    int cantidad;
};

#endif
