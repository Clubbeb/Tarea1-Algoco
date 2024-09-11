#include <iostream>
#include <fstream>
#include <chrono>
using namespace std;

void selection_sort(int array[],int n){
    for(int i=0;i<n-1;i++){
        int menor_index = i; //elige como menor el primero del arreglo

        for(int j = i+1 ; j<n ;j++){
            if(array[j]<array[menor_index]){ //compara si el prox es menor
                menor_index = j;
            }
        }

        if(menor_index != i){//intercambia el nuevo menor a la primera posicion
            swap(array[menor_index],array[i]);
        }
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

int main(){

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
    selection_sort(array,n);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    escribir(array,n);
    cout << "Tiempo de ejecución: " << duration.count() << " segundos" << endl;

    return 0;
}

