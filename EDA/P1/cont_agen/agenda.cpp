#include "agenda.hpp"

/* Devuelve una agenda vacia en a, sin contactos.
*/
void iniciar(agenda& a){
    a.total = 0;
    a.posicionIterador = 0;
}

/* Si la agenda a no esta llena (numero de contactos almacenados menor que MAX),
   la funcion devuelve false y añade el contacto c a la agenda a.
   Si la agenda esta llena, la funcion devuelve true y la agenda a no se modifica.
*/
bool anyadir(agenda& a, const contacto& c){
    if(a.total < MAX){
        a.datos[a.total] = c;
        ++a.total;
        return false;
    }
    return true;
}

/* Devuelve true si y solo si la agenda a esta vacia. 
*/
bool vacia(const agenda& a){
    return a.total == 0;
}

/* Si a no esta vacia, la funcion devuelve la agenda modificada eliminando el ultimo contacto 
   añadido a ella. Si a esta vacia, la funcion devuelve la agenda sin modificar.
*/
void borrarUltimo(agenda& a){
    if(a.total > 0){
        --a.total;
    }
}

/* Dada una agenda a y un contacto c, devuelve true si y solo si en 
   a hay algun contacto igual a c (en el sentido de la funcion == del TAD contacto), 
   false en caso contrario.
 */
bool esta(const agenda& a, const contacto& c){
    for(int i = 0; i < a.total; ++i){
        if(a.datos[i] == c){
            return true;
        }
    }
    return false;
}

/* Situa el iterador al principio de la agenda.
*/
void iniciarIterador(agenda& a){
    a.posicionIterador = 0;
}

/* Devuelve true si el iterador tiene algun contacto pendiente.
*/
bool existeSiguiente(const agenda& a){
    return a.posicionIterador < a.total;
}

/* Devuelve en c el siguiente contacto y avanza el iterador.
   Requiere que existeSiguiente(a) sea true.
*/
void siguiente(agenda& a, contacto& c){
    if(existeSiguiente(a)){
        c = a.datos[a.posicionIterador];
        ++a.posicionIterador;
    }
}