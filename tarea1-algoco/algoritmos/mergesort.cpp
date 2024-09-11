#include <iostream>
#include <fstream>
#include <chrono>
using namespace std;

void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];   //crear arreglos temporales que almacenen los subarreglos
    //guardar sus elementos
    for (i = 0; i < n1; ++i)
        L[i] = arr[left + i];
    for (j = 0; j < n2; ++j)
        R[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;
    //unir los arreglos temporales al arreglo original
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            ++i;
        } else {
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }
    //verificar si quedan elementos en L
    while (i < n1) {
        arr[k] = L[i];
        ++i;
        ++k;
    }
    //verificar si quedan elementos en R
    while (j < n2) {
        arr[k] = R[j];
        ++j;
        ++k;
    }
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;   //ver punto medio del arreglo

        mergeSort(arr, left, mid);        //ordenar mitad izquierda
        mergeSort(arr, mid + 1, right);    //ordenar mitad derecha 

        merge(arr, left, mid, right);   //combinar ambas mitades
    }
}
//Función para escribir el arreglo ordenado
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
    int arr[n];
    int size = n;

    for (int i = 0; i < n; i++) {
        file >> arr[i]; // Leer los datos
    }
    file.close();

    auto start = chrono::high_resolution_clock::now();
    mergeSort(arr, 0, n - 1);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    escribir(arr,n);
    cout << "Tiempo de ejecución: " << duration.count() << " segundos" << endl;

    return 0;
}