#include "agenda.hpp"

/* Devuelve una agenda vacia en a, sin contactos.
*/
void iniciar(agenda& a){
    a.total = 0;
}

/* Si la agenda a no esta llena (numero de contactos almacenados menor que MAX),
   la funcion devuelve false y añade el contacto c a la agenda a.
   Si la agenda esta llena, la funcion devuelve true y la agenda a no se modifica.
*/
bool anyadir(agenda& a, const contacto& c){
    if(a.total < MAX){
        
    }
}

/* Devuelve true si y solo si la agenda a esta vacia. 
*/
bool vacia(const agenda& a){

}

/* Si a no esta vacia, la funcion devuelve la agenda modificada eliminando el ultimo contacto 
   añadido a ella. Si a esta vacia, la funcion devuelve la agenda sin modificar.
*/
void borrarUltimo(agenda& a){

}

/* Dada una agenda a y un contacto c, devuelve true si y solo si en 
   a hay algun contacto igual a c (en el sentido de la funcion == del TAD contacto), 
   false en caso contrario.
 */
bool esta(const agenda& a, const contacto& c){

}