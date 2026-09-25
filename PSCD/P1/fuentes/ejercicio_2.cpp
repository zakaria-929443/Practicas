//------------------------------------------------------------------------------
// File:   practica_1_V2.cpp
// Author: PSCD-Unizar
// Date:   septiembre 2026
// Coms:   Parte del práctica 1 de PSCD
//         Compilar mediante
//           g++ practica_1_V2.cpp -o practica_1_V2 -std=c++11 -pthread
//------------------------------------------------------------------------------

#include <iostream>
#include <thread>
#include <string>
#include <chrono>
#include <cstdlib>
#include <ctime>

using namespace std;

void mostrar(int numero, int retardo, int veces) {
    for(int i=1; i<=veces; i++) {
        // cout << "Soy " << numero << endl;
        cout << "Soy " + to_string(numero) + "\n";
        //el thread que me ejecuta se bloquea durante "retardo" milisegundos
        this_thread::sleep_for(chrono::milliseconds(retardo));
    }
}

int main(int argc, char* argv[]) {
    const int N = 10;
    thread P[N]; //de momento, ningún thread se pone en marcha
    srand(time(NULL));
    int numAleo = 5 + rand() % 11; // número aleatorio entre 5 y 15
    int tmpAlea = 100 + rand() % 201; // tiempo aleatorio entre 100 y 300 ms
    for(int i = 0; i < N; i++) {
        P[i] = thread(&mostrar, i, tmpAlea, numAleo); //P[i] se pone en marcha
    }

    for (int i=0; i<N; i++) { 
        P[i].join(); //me bloqueo hasta que "P[i]" termine
    }

    cout << "Fin\n";
    return 0;
}
