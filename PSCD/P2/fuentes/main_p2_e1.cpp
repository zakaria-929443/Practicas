//------------------------------------------------------------------------------
// File:   main_p2_e1.cpp
// Author: PSCD
// Date:   septiembre 2026
// Coms:   Parte del practica 2 de PSCD. Ejercicio 1.
//         Coordinador + 8 buscadores sincronizados mediante esperas activas.
//         Compilar mediante Makefile asociado:  make -f Makefile_p2_e1
//------------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <thread>
#include <atomic>
#include <cstdlib>

using namespace std;

const int N = 512;
const int N_BUSC = 8;           // # de procesos buscadores
const int TAM = N / N_BUSC;     // tamanyo del trozo de cada buscador

// --- Datos compartidos ---
int v[N];                       // vector de datos (solo lectura para buscadores)
int valorBuscado;               // valor que se busca
int resultados[N_BUSC];         // cada buscador escribe en su propia casilla

// --- Variables de sincronizacion (esperas activas) ---
atomic<bool> datosListos(false);        // el coordinador avisa de datos cargados
atomic<bool> finBuscador[N_BUSC];        // cada buscador avisa de que ha terminado

//------------------------------------------------------------------------------
// Pre: 0 <= i <= d <= N-1
// Post: result = Num alpha in [i,d].value == v[alpha]
//------------------------------------------------------------------------------
void ocurrencias(const int v[N], const int i, const int d, const int value, int &result){
    result = 0;
    for(int k = i; k <= d; ++k){
        if(v[k] == value){
            ++result;
        }
    }
}

// Proceso buscador: espera los datos, cuenta en su trozo y avisa al terminar.
void buscador(int id){
    while(!datosListos){ }                       // espera activa a que haya datos
    int ini = id * TAM;
    int fin = ini + TAM - 1;
    ocurrencias(v, ini, fin, valorBuscado, resultados[id]);
    finBuscador[id] = true;                      // avisa al coordinador
}

// Proceso coordinador: carga datos, avisa, espera a los buscadores y muestra el total.
void coordinador(){
    ifstream file("datos.txt");
    if(!file.is_open()){
        cerr << "Error: no se pudo abrir el fichero datos.txt" << endl;
        exit(1);
    }
    int idx = 0, valor;
    while(idx < N && file >> valor){
        v[idx++] = valor;
    }
    file.close();
    if(idx < N){
        cerr << "Error: el fichero datos.txt contiene menos de " << N << " valores" << endl;
        exit(1);
    }

    datosListos = true;                          // avisa a los buscadores

    for(int i = 0; i < N_BUSC; ++i){
        while(!finBuscador[i]){ }                 // espera activa a cada buscador
    }

    int total = 0;
    for(int i = 0; i < N_BUSC; ++i){
        total += resultados[i];
    }
    cout << "El valor " << valorBuscado << " aparece " << total
         << " veces en el vector." << endl;
}

int main(int argc, char* argv[]) {
    cout << "Introduzca el valor a buscar: ";
    cin >> valorBuscado;

    for(int i = 0; i < N_BUSC; ++i){
        finBuscador[i] = false;
    }
    datosListos = false;

    // El proceso principal lanza los 9 procesos (1 coordinador + 8 buscadores)
    thread coord(coordinador);
    thread busc[N_BUSC];
    for(int i = 0; i < N_BUSC; ++i){
        busc[i] = thread(buscador, i);
    }

    coord.join();
    for(int i = 0; i < N_BUSC; ++i){
        busc[i].join();
    }

    return 0;
}
