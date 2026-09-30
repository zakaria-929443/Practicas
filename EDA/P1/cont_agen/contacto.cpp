#include "agenda.hpp"

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

static void mostrarAgenda(agenda& a){
    contacto c;
    iniciarIterador(a);
    while(existeSiguiente(a)){
        siguiente(a, c);
        cout << "Nombre: " << nombre(c) << endl;
        cout << "Direccion: " << direccion(c) << endl;
        cout << "Telefono: " << telefono(c) << endl;
    }
}

int main(){
    agenda a;
    contacto c;
    string nombreBuscado;

    iniciar(a);
    crear("Zakaria", "Calle Falsa 123", 123456789, c);
    anyadir(a, c);
    crear("Maria", "Calle Verdadera 456", 987654321, c);
    anyadir(a, c);
    crear("Lucia", "Gran Via 10", 612345678, c);
    anyadir(a, c);

    cout << "Contactos de la agenda:" << endl;
    mostrarAgenda(a);

    borrarUltimo(a);
    cout << "\nAgenda tras borrar el ultimo contacto:" << endl;
    mostrarAgenda(a);

    cout << "\nNombre que desea buscar: ";
    cin >> nombreBuscado;
    crear(nombreBuscado, "", 0, c);
    if(esta(a, c)){
        cout << "El contacto esta en la agenda." << endl;
    } else {
        cout << "El contacto no esta en la agenda." << endl;
    }
}