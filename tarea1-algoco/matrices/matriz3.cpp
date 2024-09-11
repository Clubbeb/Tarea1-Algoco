#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <cmath>

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

// Función para escribir una matriz en un archivo
void escribirResultado(const vector<vector<int>>& matriz, const string& nombreArchivo) {
    ofstream arch(nombreArchivo);
    if (!arch.is_open()) {
        cerr << "Error al abrir el archivo para escribir: " << nombreArchivo << endl;
        exit(1);
    }

    // Escribir datos de la matriz
    for (const auto& fila : matriz) {
        for (int elemento : fila) {
            arch << elemento << " ";
        }
        arch << endl;
    }

    arch.close();
}

// Función para sumar dos matrices
vector<vector<int>> sumarMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int filas = A.size();
    int columnas = A[0].size();
    vector<vector<int>> C(filas, vector<int>(columnas));

    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }

    return C;
}

// Función para restar dos matrices
vector<vector<int>> restarMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int filas = A.size();
    int columnas = A[0].size();
    vector<vector<int>> C(filas, vector<int>(columnas));

    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }

    return C;
}

// Función para multiplicar matrices usando el algoritmo de Strassen
vector<vector<int>> multiplicarMatricesStrassen(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    if (n == 1) {
        // Base case: 1x1 matrix multiplication
        vector<vector<int>> C(1, vector<int>(1));
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }

    // Dividir las matrices en submatrices
    int m = n / 2;
    vector<vector<int>> A11(m, vector<int>(m));
    vector<vector<int>> A12(m, vector<int>(m));
    vector<vector<int>> A21(m, vector<int>(m));
    vector<vector<int>> A22(m, vector<int>(m));
    vector<vector<int>> B11(m, vector<int>(m));
    vector<vector<int>> B12(m, vector<int>(m));
    vector<vector<int>> B21(m, vector<int>(m));
    vector<vector<int>> B22(m, vector<int>(m));

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; ++j) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + m];
            A21[i][j] = A[i + m][j];
            A22[i][j] = A[i + m][j + m];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + m];
            B21[i][j] = B[i + m][j];
            B22[i][j] = B[i + m][j + m];
        }
    }

    // Calcular las 7 matrices intermedias
    auto M1 = multiplicarMatricesStrassen(sumarMatrices(A11, A22), sumarMatrices(B11, B22));
    auto M2 = multiplicarMatricesStrassen(sumarMatrices(A21, A22), B11);
    auto M3 = multiplicarMatricesStrassen(A11, restarMatrices(B12, B22));
    auto M4 = multiplicarMatricesStrassen(A22, restarMatrices(B21, B11));
    auto M5 = multiplicarMatricesStrassen(sumarMatrices(A11, A12), B22);
    auto M6 = multiplicarMatricesStrassen(restarMatrices(A21, A11), sumarMatrices(B11, B12));
    auto M7 = multiplicarMatricesStrassen(restarMatrices(A12, A22), sumarMatrices(B21, B22));

    // Calcular las submatrices del resultado
    vector<vector<int>> C11 = sumarMatrices(restarMatrices(sumarMatrices(M1, M4), M5), M7);
    vector<vector<int>> C12 = sumarMatrices(M3, M5);
    vector<vector<int>> C21 = sumarMatrices(M2, M4);
    vector<vector<int>> C22 = sumarMatrices(restarMatrices(sumarMatrices(M1, M3), M2), M6);

    // Combinar las submatrices para formar la matriz final
    vector<vector<int>> C(n, vector<int>(n));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; ++j) {
            C[i][j] = C11[i][j];
            C[i][j + m] = C12[i][j];
            C[i + m][j] = C21[i][j];
            C[i + m][j + m] = C22[i][j];
        }
    }

    return C;
}

// Función para hacer la matriz tamaño de 2^k x 2^k
vector<vector<int>> hacerPotenciaDeDos(vector<vector<int>>& matriz) {
    int n = matriz.size();
    int m = matriz[0].size();
    int tamaño = max(n, m);
    int nuevaTamaño = pow(2, ceil(log2(tamaño)));

    vector<vector<int>> nuevaMatriz(nuevaTamaño, vector<int>(nuevaTamaño, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            nuevaMatriz[i][j] = matriz[i][j];
        }
    }

    return nuevaMatriz;
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

    // Multiplicar matrices usando Strassen
    auto start = chrono::high_resolution_clock::now();

    // Ajustar el tamaño de las matrices a la potencia de 2 más cercana
    A = hacerPotenciaDeDos(A);
    B = hacerPotenciaDeDos(B);

    C = multiplicarMatricesStrassen(A, B);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    cout << "Tiempo de ejecución: " << duration.count() << " segundos" << endl;

    // Escribir resultado en archivo
    escribirResultado(C, "resultado.txt");

    return 0;
}
