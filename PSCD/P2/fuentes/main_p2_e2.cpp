//------------------------------------------------------------------------------
// File:   main_p2_e2.cpp
// Author: PSCD
// Date:   septiembre 2026
// Coms:   Parte del practica 2 de PSCD. Ejercicio 2 (Test&Set).
//         Igual que el e1, pero los buscadores actualizan en exclusion mutua
//         (test-and-set sobre atomic_flag) el trozo con mas ocurrencias.
//         Compilar mediante Makefile asociado:  make -f Makefile_p2_e2
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

// Mayor numero de ocurrencias hallado y limites del trozo donde se encontro.
int maxVeces;
int indMin;
int indMax;

// --- Variables de sincronizacion ---
atomic<bool> datosListos(false);         // el coordinador avisa de datos cargados
atomic<bool> finBuscador[N_BUSC];         // cada buscador avisa de que ha terminado
atomic_flag tas = ATOMIC_FLAG_INIT;       // cerrojo test-and-set para la exclusion mutua

//------------------------------------------------------------------------------
// Pre: 0 <= i <= d <= N-1
// Post: cuenta las ocurrencias de value en v[i..d]; si ese numero supera a
//       maxVeces (acceso en exclusion mutua mediante tas), actualiza maxVeces,
//       indMin e indMax con los datos de este trozo.
//------------------------------------------------------------------------------
void ocurrencias(const int v[N], const int i, const int d, const int value,
                 int &maxVeces, int &indMin, int &indMax, atomic_flag &tas){
    int veces = 0;
    for(int k = i; k <= d; ++k){
        if(v[k] == value){
            ++veces;
        }
    }
    // Seccion critica: acceso en exclusion mutua a las variables compartidas.
    while(tas.test_and_set()){ }             // espera activa a entrar
    if(veces > maxVeces){
        maxVeces = veces;
        indMin = i;
        indMax = d;
    }
    tas.clear();                             // libera el cerrojo
}

// Proceso buscador: espera los datos, procesa su trozo y avisa al terminar.
void buscador(int id){
    while(!datosListos){ }                   // espera activa a que haya datos
    int ini = id * TAM;
    int fin = ini + TAM - 1;
    ocurrencias(v, ini, fin, valorBuscado, maxVeces, indMin, indMax, tas);
    finBuscador[id] = true;                  // avisa al coordinador
}

// Proceso coordinador: carga datos, avisa, espera y muestra el trozo con mas ocurrencias.
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

    datosListos = true;                      // avisa a los buscadores

    for(int i = 0; i < N_BUSC; ++i){
        while(!finBuscador[i]){ }             // espera activa a cada buscador
    }

    cout << "El valor " << valorBuscado << " aparece como maximo " << maxVeces
         << " veces en el trozo del vector [" << indMin << ", " << indMax << "]." << endl;
}

int main(int argc, char* argv[]) {
    cout << "Introduzca el valor a buscar: ";
    cin >> valorBuscado;

    maxVeces = -1;                           // asi cualquier trozo (incluso con 0) puede ser maximo
    indMin = 0;
    indMax = 0;
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
