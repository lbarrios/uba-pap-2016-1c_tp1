#include <iostream>
#include <assert.h>
#include <math.h>
#include "BinaryTreePositionalLogic.h"
#include "BinaryTreeManipulation.h"
#include "IntervalLogic.h"
#include "..\catedra\libs\Matriz.h"

using namespace std;

int main(int argc , char *argv[])
{
    ///    ETAPA 1,
    /// CARGO LOS DATOS
    string str;
    int cantidadMatrices; int longitudIntervalo;int alturaArbol;
    Matriz target; Matriz *inputs; Matriz *Arbol;

    cin >> cantidadMatrices;
    cin >> longitudIntervalo;
    cin >>target;

    inputs = new Matriz[cantidadMatrices];
    for(int x=0; x < cantidadMatrices; x++) cin >> inputs[x];

    /// ETAPA 2,
    /// CREO EL ARBOL Y LO POBLO CON LA INFORMACION QUE TENEMOS
    alturaArbol = (proximoCuadrado(cantidadMatrices)*2)-1;
    Arbol =  new Matriz[alturaArbol];
    poblarArbol(id(), Arbol, alturaArbol, inputs, cantidadMatrices);


    /// ETAPA 3,
    /// PARA TODOS LOS INTERVALOS QUE ESTAN DENTRO DE LOS DATOS QUE SUBIMOS,
    /// CALCULAMOS LA MULTIPLICACION Y NOS FIJAMOS SI ES TARGET
    bool found = false;

    for(int x=longitudIntervalo; x <= cantidadMatrices; x++){
        int comienzoIntervalo = x-longitudIntervalo;
        int finintervalo = x;
        Matriz respuestaMultiplicarIntervalo = resolverIntervalo(id(),Arbol,alturaArbol,comienzoIntervalo,finintervalo);
        found = found or (respuestaMultiplicarIntervalo==target);
    }

    /// ETAPA 4,
    /// RETURN RESULTS
    /// ???
    /// PROFIT

    if(found) cout << "SI" << endl;
    if(!found) cout << "NO" << endl;

    delete [] inputs;
    delete [] Arbol;


    return 0;
}
