#include <iostream>
#include <assert.h>
#include <math.h>
#include "ArrayAlgebra.h"
#include "ArrayTree.h"
#include "..\catedra\libs\Matriz.h"

using namespace std;

int main(int argc , char *argv[])
{
    ///    ETAPA 1, CARGO LOS DATOS
    ifstream file("inputs/ejemplo3.txt"); string str;
    int cantidadMatrices; int longitudIntervalo;int longitudArbol;
    vector<int> inputValues; int value;
    Matriz target; Matriz *inputs; Matriz *Arbol;
    file >> cantidadMatrices;
    file >> longitudIntervalo; longitudIntervalo = longitudIntervalo - 1;

    inputs = new Matriz[cantidadMatrices];

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

    /// ETAPA 2, CREO EL ARBOL Y LO POBLO CON LA INFORMACION QUE TENEMOS
    longitudArbol = (proximoCuadrado(cantidadMatrices)*2)-1;
    Arbol =  new Matriz[longitudArbol];
    poblarArbol(id(), Arbol, longitudArbol, inputs, cantidadMatrices);


    /// ETAPA 3, PARA TODOS LOS INTERVALOS QUE ESTAN DENTRO DE LOS DATOS QUE SUBIMOS, CALCULAMOS LA MULTIPLICACION Y NOS FIJAMOS SI ES TARGET
    bool found = false;

    for(int x=longitudIntervalo; x < cantidadMatrices; x++){
        found = found or (
                resolverConjunto(id(),Arbol,longitudArbol,x-longitudIntervalo,x)==target
                );
    }

    /// ETAPA 4, EXITO

    if(found) cout << "SI" << endl;
    if(!found) cout << "NO" << endl;

    delete [] inputs;
    delete [] Arbol;

    return 0;
}
