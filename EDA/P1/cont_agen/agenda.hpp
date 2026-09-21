/* Nombre, apellidos y NIP del (de los) autor(es).
*/

#ifndef AGENDA_HPP
#define AGENDA_HPP

#include "contacto.hpp"

// PREDECLARACION DEL TAD agenda (inicio INTERFAZ)

const int MAX = 40;

/* Los valores del TAD agenda representan colecciones de contactos a las 
   que se pueden añadir elementos de tipo contacto, y de las que se pueden eliminar 
   sus contactos de uno en uno, eliminandose siempre el ultimo contacto añadido de 
   todos los que contenga la agenda.
   Dado que la implementacion es estatica, se impone una maxima capacidad de la
   agenda, igual al valor de la constante MAX.
 */
struct agenda;

/* Devuelve una agenda vacia en a, sin contactos.
*/
void iniciar(agenda& a);

/* Si la agenda a no esta llena (numero de contactos almacenados menor que MAX),
   la funcion devuelve false y añade el contacto c a la agenda a.
   Si la agenda esta llena, la funcion devuelve true y la agenda a no se modifica.
*/
bool anyadir(agenda& a, const contacto& c);

/* Devuelve true si y solo si la agenda a esta vacia. 
*/
bool vacia(const agenda& a);

/* Si a no esta vacia, la funcion devuelve la agenda modificada eliminando el ultimo contacto 
   añadido a ella. Si a esta vacia, la funcion devuelve la agenda sin modificar.
*/
void borrarUltimo(agenda& a);

/* Dada una agenda a y un contacto c, devuelve true si y solo si en 
   a hay algun contacto igual a c (en el sentido de la funcion == del TAD contacto), 
   false en caso contrario.
 */
bool esta(const agenda& a, const contacto& c);

//COMPLETAR CON OPERACIONES ITERADOR
//....

// FIN de la PREDECLARACION DEL TAD agenda (fin INTERFAZ)


// DECLARACION DEL TAD agenda 
struct agenda{
    friend void iniciar(agenda& a);
    friend bool anyadir(agenda& a, const contacto& c);
	 friend bool vacia(const agenda& a);
    friend void borrarUltimo(agenda& a);
	 friend bool esta(const agenda& a, const contacto& c);
    //COMPLETAR CON OPERACIONES ITERADOR
    //....
  private: //declaracion de la representacion interna del tipo
           //... a COMPLETAR CON documentacion sobre la representacion interna ...
          contacto datos[MAX];
     int total;
    //COMPLETAR CAMPOS ITERADOR

    
    //...
};

#endif //fin de agenda.hpp

