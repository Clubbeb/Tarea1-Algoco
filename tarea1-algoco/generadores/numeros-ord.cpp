#include <iostream>
#include <fstream>
using namespace std;

void descendente(int n){
    ofstream archivo("../datasets-ordenamiento/dataset-desc.txt");
    archivo << n<< endl;
    for(int i = n -1 ; i >=0 ; i--){
        archivo << i<< endl;
    }
    cout << "Numeros ordenados en orden descendente en datos.txt" <<endl;
    archivo.close();
}

void ascendente(int n){
    ofstream archivo("../datasets-ordenamiento/dataset-desc.txt");
    archivo << n<< endl;
    for(int i = 0; i < n; i++){
        archivo << i<< endl;
    }
    cout << "Numeros ordenados en orden ascendente en datos.txt" <<endl;
    archivo.close();
}

int main() {
    int cant_numeros = 10;
    //ascendente(cant_numeros);
    descendente(cant_numeros);

    return 0;
}
