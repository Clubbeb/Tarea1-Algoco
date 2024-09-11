#include <iostream>
#include <fstream>  // para manejo de archivos
#include <cstdlib>  // para rand() y srand()
#include <ctime>    // para time()
using namespace std;

int main() {
    // Semilla para generar números aleatorios basada en el tiempo actual
    srand(time(0));

    // abrir archivo datasets
    ofstream archivo("../datasets-ordenamiento/lolaza.txt");

    if (archivo.is_open()) {

        int cantidadNumeros = 100000;
        archivo << cantidadNumeros << endl;

        // Generar números aleatorios y escribirlos en el archivo
        for (int i = 0; i < cantidadNumeros; ++i) {
            int numeroAleatorio = rand();
            archivo << numeroAleatorio << endl;
        }
        archivo.close();
        cout << "Numeros aleatorios guardados en dataset-random.txt" << endl;
    } else {
        cerr << "No se pudo abrir el archivo!" << endl;
    }

    return 0;
}
