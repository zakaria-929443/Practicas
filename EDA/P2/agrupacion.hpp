/* Nombre, apellidos y NIP del (de los) autor(es).
*/

#ifndef AGRUPACION_HPP
#define AGRUPACION_HPP

// PREDECLARACION DEL TAD GENERICO agrupacion (inicio INTERFAZ)

const int MAX = 40;

/* Los valores del TAD generico agrupacion representan colecciones a las que se
   pueden anyadir elementos de tipo T, y de las que se pueden eliminar sus
   elementos de uno en uno, eliminandose siempre el ultimo elemento anyadido de
   todos los que contenga la agrupacion.
   Dado que la implementacion es estatica, se impone una maxima capacidad de la
   agrupacion, igual al valor de la constante MAX.
   El parametro de tipo T debe disponer del operador == (igualdad entre dos
   elementos de tipo T), que es la funcion "iguales" del parametro formal elem.
*/
template<typename T> struct agrupacion;


/* Devuelve una agrupacion vacia en a, sin elementos.
*/
template<typename T> void iniciar(agrupacion<T>& a);


/* Si la agrupacion a no esta llena (numero de elementos menor que MAX),
   la funcion devuelve false y anyade el elemento e a la agrupacion a.
   Si la agrupacion esta llena, la funcion devuelve true y a no se modifica.
*/
template<typename T> bool anyadir(agrupacion<T>& a, const T& e);


/* Devuelve true si y solo si la agrupacion a esta vacia.
*/
template<typename T> bool vacia(const agrupacion<T>& a);


/* Si a no esta vacia, elimina de a el ultimo elemento anyadido a ella.
   Si a esta vacia, a no se modifica.
*/
template<typename T> void borrarUltimo(agrupacion<T>& a);


/* Dada una agrupacion a y un elemento e, devuelve true si y solo si en a hay
   algun elemento igual a e (en el sentido de la funcion == del tipo T),
   false en caso contrario.
*/
template<typename T> bool esta(const agrupacion<T>& a, const T& e);


/* Situa el iterador al principio de la agrupacion.
*/
template<typename T> void iniciarIterador(agrupacion<T>& a);


/* Devuelve true si el iterador tiene algun elemento pendiente.
*/
template<typename T> bool existeSiguiente(const agrupacion<T>& a);


/* Devuelve en e el siguiente elemento y avanza el iterador.
   Requiere que existeSiguiente(a) sea true.
*/
template<typename T> void siguiente(agrupacion<T>& a, T& e);


// FIN predeclaracion del TAD GENERICO agrupacion (Fin INTERFAZ)



// DECLARACION DEL TAD GENERICO agrupacion

template<typename T>
struct agrupacion{
    friend void iniciar<T>(agrupacion<T>& a);
    friend bool anyadir<T>(agrupacion<T>& a, const T& e);
    friend bool vacia<T>(const agrupacion<T>& a);
    friend void borrarUltimo<T>(agrupacion<T>& a);
    friend bool esta<T>(const agrupacion<T>& a, const T& e);
    friend void iniciarIterador<T>(agrupacion<T>& a);
    friend bool existeSiguiente<T>(const agrupacion<T>& a);
    friend void siguiente<T>(agrupacion<T>& a, T& e);
  private: //declaracion de la representacion interna del tipo
     // datos: almacena los elementos en orden de insercion (datos[0] el primero
     //        anyadido, datos[total-1] el ultimo).
     // total: numero de elementos almacenados actualmente.
     // posicionIterador: indice del proximo elemento a devolver por el iterador.
     T datos[MAX];
     int total;
     int posicionIterador;
};


// IMPLEMENTACION DE LAS OPERACIONES DEL TAD GENERICO agrupacion


template<typename T>
void iniciar(agrupacion<T>& a) {
    a.total = 0;
    a.posicionIterador = 0;
}

template<typename T>
bool anyadir(agrupacion<T>& a, const T& e) {
    if(a.total < MAX){
        a.datos[a.total] = e;
        ++a.total;
        return false;
    }
    return true;
}

template<typename T>
bool vacia(const agrupacion<T>& a) {
    return a.total == 0;
}

template<typename T>
void borrarUltimo(agrupacion<T>& a) {
    if(a.total > 0){
        --a.total;
    }
}

template<typename T>
bool esta(const agrupacion<T>& a, const T& e) {
    for(int i = 0; i < a.total; ++i){
        if(a.datos[i] == e){
            return true;
        }
    }
    return false;
}

template<typename T>
void iniciarIterador(agrupacion<T>& a) {
    a.posicionIterador = 0;
}

template<typename T>
bool existeSiguiente(const agrupacion<T>& a) {
    return a.posicionIterador < a.total;
}

template<typename T>
void siguiente(agrupacion<T>& a, T& e) {
    if(existeSiguiente(a)){
        e = a.datos[a.posicionIterador];
        ++a.posicionIterador;
    }
}

#endif //fin de agrupacion.hpp
