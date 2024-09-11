#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <chrono>

using namespace std;

void escribir(const vector<int>& vec){

    ofstream arch("final.txt");
    int n = vec.size(); // Obtener el tamaño del vector
    arch << n << endl;
    for (const int& elem : vec) {
        arch << elem << endl; // Escribir cada elemento en el archivo
    }

    arch.close();
}

int main() {

    ifstream file("../datasets-ordenamiento/dataset-random.txt");
    if (!file) {
        cout << "Error al abrir el archivo" << endl;
        return 1;
    }

    int n;
    file >> n;
    vector<int> numeros;
    numeros.reserve(n);

    for (int i = 0; i < n; i++) {
        int numero;
        file >> numero; // Leer cada número de la entrada
        numeros.push_back(numero); // Agregar al vector
    }
    file.close();
    
    auto start = chrono::high_resolution_clock::now();
    // Ordenar el vector en orden ascendente
    sort(numeros.begin(), numeros.end());
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    escribir(numeros);

    cout << "Tiempo de ejecución: " << duration.count() << " segundos" << endl;

    return 0;
}