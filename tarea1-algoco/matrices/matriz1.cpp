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

// Función para multiplicar dos matrices
void multiplicarMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C) {
    int m = A.size();        // Número de filas en A
    int n = A[0].size();     // Número de columnas en A (y filas en B)
    int p = B[0].size();     // Número de columnas en B

    // Inicializar la matriz de resultado C con ceros
    C.assign(m, vector<int>(p, 0));

    // Realizar la multiplicación de matrices
    for (int i = 0; i < m; ++i) {     //Filas A
        for (int j = 0; j < p; ++j) {    //Columnas B
            for (int k = 0; k < n; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Función para imprimir una matriz
void escribirResultado(const vector<vector<int>>& matriz) {
    ofstream arch("resultado.txt");
    for (const auto& fila : matriz) {
        for (int elemento : fila) {
            arch << elemento << " ";
        }
        arch << endl;
    }
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
    multiplicarMatrices(A, B, C);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    cout << "Tiempo de ejecución: " << duration.count() << " segundos" << endl;

    // Imprimir resultado
    escribirResultado(C);

    return 0;
}

