#include "contacto.hpp"

/* Dada una cadena nombre, una cadena direccion y un entero telefono, 
devuelve un contacto c con esos datos. 
*/
void crear(string nombre, string direccion, int telefono, contacto& c){
    c.nombre = nombre;
    c.direccion = direccion;
    c.telefono = telefono;
}

/* Dado un contacto c, devuelve la cadena correspondiente al nombre de c. 
*/
string nombre(const contacto& c){
    return c.nombre;
}

/* Dado un contacto c, devuelve la cadena correspondiente a la direccion de c. 
*/
string direccion(const contacto& c){
    return c.direccion;
}

/* Dado un contacto c, devuelve el entero correspondiente al telefono de c. 
*/
int telefono(const contacto& c){
    return c.telefono;
}

/* Devuelve verdad si y sólo si los contactos c1 y c2 tienen el mismo nombre. 
*/
bool operator==(const contacto& c1, const contacto& c2){
    return (c1.nombre == c2.nombre);
}

int main(){
    struct contacto c1, c2;
    crear("Zakaria", "Calle Falsa 123", 123456789, c1);
    crear("Maria", "Calle Verdadera 456", 987654321, c2);
    cout << "Nombre de c1: " << nombre(c1) << endl;
    cout << "Direccion de c1: " << direccion(c1) << endl;
    cout << "Telefono de c1: " << telefono(c1) << endl;
    cout << "Nombre de c2: " << nombre(c2) << endl;
    cout << "Direccion de c2: " << direccion(c2) << endl;
    cout << "Telefono de c2: " << telefono(c2) << endl;
    if (c1 == c2) {
        cout << "Los contactos c1 y c2 son iguales." << endl;
    } else {
        cout << "Los contactos c1 y c2 son diferentes." << endl;
    }
}