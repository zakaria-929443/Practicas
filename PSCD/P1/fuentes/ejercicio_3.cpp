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
#include <cmath>
#include <functional>


using namespace std;

const int N = 100;
int v[N];

void inicializar(){
    srand(time(NULL));
    for(int i=0; i<N; i++){
        v[i] = rand(); // número aleatorio entre 0 y RAND_MAX
    }
}

void media(int &media){
    int suma = 0;
    for(int i=0; i<N; i++){
        suma += v[i];
    }
    media = suma / N;

}

void maxmin(int &max, int &min){
    max = v[0];
    min = v[0];
    for(int i=1; i<N; i++){
        if(v[i] > max){
            max = v[i];
        }
        if(v[i] < min){
            min = v[i];
        }
    }

}

void sigma(int &sigma, int media){
    int suma2 = 0;
    for(int i=0; i<N; i++){
        suma2 += (v[i] - media) * (v[i] - media);
    }
    sigma = sqrt(suma2 / N);

}

void mostrarResultado(int media, int max, int min, int sigma){
    cout << "Media: " << media << endl;
    cout << "Maximo: " << max << endl;
    cout << "Minimo: " << min << endl;
    cout << "Sigma: " << sigma << endl;

}

int main(int argc, char* argv[]) {
    inicializar();
    int media_result, min, max, sigma_result = 0;
    thread th_media(media, ref(media_result));
    thread th_maxmin(maxmin, ref(max), ref(min));

    th_media.join();
    thread th_sigma(sigma, ref(sigma_result), media_result);

    th_maxmin.join();
    th_sigma.join();
    mostrarResultado(media_result, max, min, sigma_result);

    cout << "Fin\n";
    return 0;
}