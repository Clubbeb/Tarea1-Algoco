#include <iostream>
#include <fstream>
#include <chrono>
using namespace std;

int partition(int arr[], int low, int high) {
    int pivot = arr[high]; //elige el pivote, en este caso el ultimo del array
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (arr[j] < pivot) {   //aqui compara si el actual es menor que el pivote 
            ++i;      //mueve el indice del mas pequeño una posicion
            swap(arr[i], arr[j]);        
        }
    }

    swap(arr[i + 1], arr[high]);   //poner el pivote en la posicion correcta

    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);   //aqui divide el arreglo en subarreglos para asignar pivote

        quickSort(arr, low, pi - 1);           //realiza el algoritmo recursivamente a la izq del pivote
        quickSort(arr, pi + 1, high);          //lo mismo pero a la derecha del pivote
    }
}

void escribir(int arr[], int n){

    ofstream arch("final.txt");
    arch << n<< endl;
    for(int i = 0; i <n;i++){
        arch << arr[i]<< endl;
    }
    arch.close();
}

int main() {
    ifstream file("../datasets-ordenamiento/dataset-random.txt"); //cambiar datasets
    if (!file) {
        cout << "Error al abrir el archivo" << endl;
        return 1;
    }

    int n;
    file >> n;
    int array[n];

    for (int i = 0; i < n; i++) {
        file >> array[i]; // Leer los datos
    }
    file.close();

    //tomar tiempo del algoritmo
    auto start = chrono::high_resolution_clock::now();
    quickSort(array, 0, n);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    escribir(array,n);
    cout << "Tiempo de ejecución: " << duration.count() << " segundos" << endl;

    return 0;
}