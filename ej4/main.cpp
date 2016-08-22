#include <iostream>
#include <assert.h>
#include <math.h>
#include "ArrayAlgebra.h"
#include "ArrayTree.h"
#include "..\catedra\libs\Matriz.h"

using namespace std;

int main(int argc , char *argv[])
{
    ifstream file("inputs/ejemplo4.txt"); string str;
    int cantidadMatrices; int longitudIntervalo;int longitudArbol;
    vector<int> inputValues; int value;
    Matriz target; Matriz *inputs; Matriz *Arbol;
    //
    // CARGO LOS DATOS
    //
    file >> cantidadMatrices;
    longitudArbol = (proximoCuadrado(cantidadMatrices)*2)-1;
    file >> longitudIntervalo; longitudIntervalo = longitudIntervalo - 1;

    inputs = new Matriz[cantidadMatrices];
    Arbol =  new Matriz[longitudArbol];
    //defino target
    for(int x = 0; x < 9; x++){
        file >> value;
        inputValues.push_back(value);
    }

    target = Matriz(inputValues);

    for(int x=0; x < cantidadMatrices; x++){
        inputValues.clear();
        for(int y = 0; y < 9; y++){
            file >> value;
            inputValues.push_back(value);
        }
        inputs[x] = Matriz(inputValues);
    }

    poblarArbol(id(), Arbol, longitudArbol, inputs, cantidadMatrices);

    bool found = false;

    for(int x=longitudIntervalo; x < cantidadMatrices; x++){
        found = found or (resolverConjunto(id(),Arbol,longitudArbol,x-longitudIntervalo,x)==target);
        //cout << endl<< "Intervalo:" << x-longitudIntervalo << "[]" << x << endl;
    }

    cout << endl << "Estaba:" << found << endl;

    delete [] inputs;
    delete [] Arbol;
    //for (int i=0; i<inputValues.size();i++){
    //    cout << inputValues[i] << endl;
    //}

    //cout << inputValues;
    //cout << cantidadMatrices;

    //cout << endl << "@@@" << endl;
    //cout << "hola"[1] << endl;
    /*

    istream_iterator<double> start(is), end;
    vector<double> numbers(start, end);
    cout << "Read " << numbers.size() << " numbers" << endl;*/

    //while (getline(file, str))
    //while ( a)
    //{
     //   cout << a << endl;// Process str
    //}

    return 0;

}
