#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>  // Para std::rand() y std::srand()
#include <ctime>    // Para std::time()

using namespace std;

// Función para generar una matriz aleatoria
vector<vector<int>> generarMatriz(int filas, int columnas, int minValor = 0, int maxValor = 10) {
    vector<vector<int>> matriz(filas, vector<int>(columnas));

    // Inicializar generador de números aleatorios
    std::srand(static_cast<unsigned>(std::time(0)));

    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            matriz[i][j] = minValor + std::rand() % (maxValor - minValor + 1);
        }
    }

    return matriz;
}

// Función para guardar una matriz en un archivo
void guardarMatrizEnArchivo(const vector<vector<int>>& matriz, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo para escribir: " << nombreArchivo << endl;
        exit(1);
    }

    // Escribir dimensiones de la matriz
    archivo << matriz.size() << " " << matriz[0].size() << endl;

    // Escribir datos de la matriz
    for (const auto& fila : matriz) {
        for (int elemento : fila) {
            archivo << elemento << " ";
        }
        archivo << endl;
    }

    archivo.close();
}

int main() {
    //valores de las matriz
    int filas = 512;
    int columnas = 512;

    // Generar y guardar matriz
    vector<vector<int>> matriz = generarMatriz(filas, columnas);

    guardarMatrizEnArchivo(matriz, "../datasets-matrices/matrizF.txt");   //cambiar nombre para diferentes datasets de matrices

    cout << "Matriz generadas y guardadas en txt" << endl;

    return 0;
}
