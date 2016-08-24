#include <iostream>
#include <assert.h>
#include <math.h>
#include "ArrayAlgebra.h"
#include "ArrayTree.h"
#include "..\catedra\libs\Matriz.h"

using namespace std;

int main(int argc , char *argv[])
{
    ///    ETAPA 0, ELIJO EL ARCHIVO DE INPUT
    ///    (ESTO DESPUES HABRIA QUE HACERLO CON EL INPUT DE TERMINAL)
    ifstream file("inputs/ejemplo3.txt");


    ///    ETAPA 1, CARGO LOS DATOS
    string str;
    int cantidadMatrices; int longitudIntervalo;int alturaArbol;
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
    alturaArbol = (proximoCuadrado(cantidadMatrices)*2)-1;
    Arbol =  new Matriz[alturaArbol];
    poblarArbol(id(), Arbol, alturaArbol, inputs, cantidadMatrices);


    /// ETAPA 3, PARA TODOS LOS INTERVALOS QUE ESTAN DENTRO DE LOS DATOS QUE SUBIMOS, CALCULAMOS LA MULTIPLICACION Y NOS FIJAMOS SI ES TARGET
    bool found = false;

    for(int x=longitudIntervalo; x < cantidadMatrices; x++){
        int comienzoIntervalo = x-longitudIntervalo;
        int finintervalo = x;
        found = found or (
                resolverIntervalo(
                        id(),Arbol,alturaArbol,comienzoIntervalo,finintervalo)==target
                );
    }

    /// ETAPA 4, EXITO

    if(found) cout << "SI" << endl;
    if(!found) cout << "NO" << endl;

    delete [] inputs;
    delete [] Arbol;


    int a[8] = {1,3,2,1,2,1,0};
    int b[15] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    printArbol(b,15,false);
    poblarArbol(1,b,15,a,8);
    printArbol(b,15,false);

    //cout <<
    for(int x=0; x < 15; x++){
    //cout << "[" << x << "]:" << getLeftmostDescendant(15, x) << "--" << getRightmostDescendant(15, x) << endl;// << endl;
    }

    return 0;
}
