#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
using namespace std;

// Función para leer una matriz desde un archivo
vector<vector<int>> leerMatrizDesdeArchivo(const string& nombreArchivo, int& filas, int& columnas) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo: " << nombreArchivo << endl;
        exit(1);
    }

    // Leer dimensiones de la matriz
    archivo >> filas >> columnas;

    // Crear la matriz
    vector<vector<int>> matriz(filas, vector<int>(columnas));

    // Leer datos de la matriz
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            archivo >> matriz[i][j];
        }
    }

    archivo.close();
    return matriz;
}

// Función para transponer una matriz
vector<vector<int>> transponerMatriz(const vector<vector<int>>& matriz) {

    //Obtener datos matriz 
    int filas = matriz.size();
    int columnas = matriz[0].size();
    vector<vector<int>> matrizTranspuesta(columnas, vector<int>(filas));

    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            matrizTranspuesta[j][i] = matriz[i][j];
        }
    }

    return matrizTranspuesta;
}

// Función para multiplicar matrices (matriz b transpuesta)
void multiplicarMatrices(const vector<vector<int>>& A, const vector<vector<int>>& BTranspuesta, vector<vector<int>>& C) {
    int m = A.size();        // Número de filas en A
    int n = A[0].size();     // Número de columnas en A (y filas en BTranspuesta)
    int p = BTranspuesta.size(); // Número de columnas en BTranspuesta

    // Inicializar la matriz de resultado C con ceros
    C.assign(m, vector<int>(p, 0));

    // Realizar la multiplicación de matrices
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < p; ++j) {
            for (int k = 0; k < n; ++k) {
                C[i][j] += A[i][k] * BTranspuesta[j][k];
            }
        }
    }
}

// Función para escribir una matriz en un archivo
void escribirResultado(const vector<vector<int>>& matriz, const string& nombreArchivo) {
    ofstream arch(nombreArchivo);
    // Escribir datos de la matriz en el archivo resultados.txt
    for (const auto& fila : matriz) {
        for (int elemento : fila) {
            arch << elemento << " ";
        }
        arch << endl;
    }

    arch.close();
}

int main() {
    int filasA, columnasA, filasB, columnasB;

    // Leer matrices desde archivos
    vector<vector<int>> A = leerMatrizDesdeArchivo("../datasets-matrices/matrizE.txt", filasA, columnasA); //cambiar dependiendo de matriz a multiplicar
    vector<vector<int>> B = leerMatrizDesdeArchivo("../datasets-matrices/matrizF.txt", filasB, columnasB);

    // Comprobar si la multiplicación es posible
    if (columnasA != filasB) {
        cerr << "Las dimensiones de las matrices no permiten la multiplicación." << endl;
        return 1;
    }

    // Crear matriz de resultado C
    vector<vector<int>> C;

    // Multiplicar matrices
    auto start = chrono::high_resolution_clock::now();
    vector<vector<int>> BTranspuesta = transponerMatriz(B);
    multiplicarMatrices(A, BTranspuesta, C);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    cout << "Tiempo de ejecución: " << duration.count() << " segundos" << endl;

    // Escribir resultado en archivo
    escribirResultado(C, "resultado.txt");

    return 0;
}

