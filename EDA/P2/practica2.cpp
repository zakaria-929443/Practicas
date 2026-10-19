/* Nombre, apellidos y NIP del (de los) autor(es).
*/

#include "agrupacion.hpp"
#include "contacto.hpp"
#include "producto.hpp"

// Muestra por pantalla todos los contactos de la agenda usando el iterador.
static void mostrarAgenda(agrupacion<contacto>& a){
    contacto c;
    iniciarIterador(a);
    while(existeSiguiente(a)){
        siguiente(a, c);
        cout << "Nombre: " << nombre(c) << endl;
        cout << "Direccion: " << direccion(c) << endl;
        cout << "Telefono: " << telefono(c) << endl;
    }
}

// Muestra por pantalla todos los productos de la lista usando el iterador.
static void mostrarLista(agrupacion<producto>& l){
    producto p;
    iniciarIterador(l);
    while(existeSiguiente(l)){
        siguiente(l, p);
        cout << "Producto: " << nombre(p) << endl;
        cout << "Cantidad: " << cantidad(p) << endl;
    }
}

int main(){
    // ---- Tarea 2: agenda de contactos con agrupacion<contacto> ----
    agrupacion<contacto> a;
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

    cout << "\nNombre de contacto que desea buscar: ";
    cin >> nombreBuscado;
    crear(nombreBuscado, "", 0, c);
    if(esta(a, c)){
        cout << "El contacto esta en la agenda." << endl;
    } else {
        cout << "El contacto no esta en la agenda." << endl;
    }

    // ---- Tarea 4: lista de la compra con agrupacion<producto> ----
    agrupacion<producto> lista;
    producto p;
    string productoBuscado;

    iniciar(lista);
    crear("Leche", 2, p);
    anyadir(lista, p);
    crear("Pan", 1, p);
    anyadir(lista, p);
    crear("Huevos", 12, p);
    anyadir(lista, p);

    cout << "\nProductos de la lista de la compra:" << endl;
    mostrarLista(lista);

    borrarUltimo(lista);
    cout << "\nLista tras borrar el ultimo producto:" << endl;
    mostrarLista(lista);

    cout << "\nNombre de producto que desea buscar: ";
    cin >> productoBuscado;
    crear(productoBuscado, 0, p);
    if(esta(lista, p)){
        cout << "El producto esta en la lista." << endl;
    } else {
        cout << "El producto no esta en la lista." << endl;
    }

    // ---- Tarea 4e) ----
    // Intentar introducir un contacto en la lista de la compra NO compila:
    // anyadir(lista, c) exige que c sea de tipo producto, pero c es de tipo
    // contacto. El sistema de tipos de las plantillas (agrupacion<producto>)
    // impide la operacion en tiempo de compilacion. Descomentar para comprobarlo:
    //
    //   anyadir(lista, c);   // error de compilacion: no coincide el tipo T

    return 0;
}
