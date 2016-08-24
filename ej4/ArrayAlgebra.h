#ifndef __PAP_ARRAYALGEBRA__
#define __PAP_ARRAYALGEBRA__

///////////// ALGEBRA DE POSICIONES:
///////////// TODO ESTO ES INDEPENDIENTE DEL TIPO DE ARBOL QUE ESTEMOS TRABAJANDO
///////////// FUNCIONA PARA TODO TIPO DE ARBOL

#include <iostream>
#include <assert.h>
#include <math.h>

using namespace std;


//Averigua la profundidad de una posicion
//Root tiene profundidad 0
//Como todo arbol es un subIntervalo de los arboles mas grande, es igual para todos
int depth(int posicion){
    return floor(log2(posicion));
}

// Consigue el proximo valor de 2 cuadrado
int proximoCuadrado(int sizeArbol){
    return pow(2,ceil(log2(sizeArbol)));
}

int proximoArbolBinario(int sizeArbol){
    return proximoCuadrado(sizeArbol)-1;
}

// Usamos esto para asegurarnos que el tamanio de los arboles sea el correcto.
// Es decir, que sea n*2 - 1. En caso contrario, devuelve false.
//
bool sizeArbolBinario (int sizeArbol){
    return sizeArbol == proximoArbolBinario(sizeArbol);
}

// Se asegura que la posicion no sea mas grande que el tamanio del arbol.
bool inRange(int sizeArbol, int posicion){
    assert(sizeArbolBinario(sizeArbol));
    return posicion < sizeArbol;
}

//  Consigue el primer elemento que es una hoja
int firstLeaf(int sizeArbol){
    assert(sizeArbolBinario(sizeArbol));
    return floor(sizeArbol/2);
}

// Pregunta si una posicion corresponde a una hoja.
bool isLeaf(int sizeArbol, int posicion){
    assert(sizeArbolBinario(sizeArbol));
    assert(inRange(sizeArbol,posicion));
    posicion++;
    return depth(posicion) == depth(sizeArbol);
}

// Pregunta si una posicion corresponde a roto
bool isRoot(int sizeArbol, int posicion){
    assert(inRange(sizeArbol,posicion));
    posicion++;
    return posicion == 1;
}

// Consigue el hijo de la izquierda
int getLeftChildren(int sizeArbol, int posicion){
    assert(!(isLeaf(sizeArbol,posicion)));
    posicion++;
    int answer = ((posicion) * 2);
    answer--;
    return answer;
};

// Consigue el hijo de la derecha
int getRightChildren(int sizeArbol, int posicion){
   // assert(sizeArbolBinario(sizeArbol));
    //assert(inRange(sizeArbol,posicion));
    assert(!(isLeaf(sizeArbol,posicion)));
    posicion++;
    int answer = ((posicion) * 2) + 1;
    answer--;
    return answer;
};

// Consigue al padre
int getFather(int sizeArbol, int posicion){
  //  assert(sizeArbolBinario(sizeArbol));
   // assert(inRange(sizeArbol,posicion));
    assert(!(isRoot(sizeArbol,posicion)));
    posicion++;
    int answer = (posicion/2);
    answer--;
    return answer;
};


int getLeftmostDescendant(int sizeArbol, int posicion){
    posicion++;
    int distanceToLeaves = depth(sizeArbol) - depth(posicion);
    int answer = ((posicion) * pow(2,distanceToLeaves));
    answer -= firstLeaf(sizeArbol); //Reacomodo para que el Intervalo empieze de 0
    answer--;
    return answer;
}


int getRightmostDescendant(int sizeArbol, int posicion){
    posicion++;
    int answer;// = 0;
    //Si esta a la derecha de todo, el valor mas a su derecha es el final
    if (depth(posicion) != depth(posicion+1)){
        answer = sizeArbol;
        answer -= firstLeaf(sizeArbol);
    }else{
        answer = getLeftmostDescendant(sizeArbol, posicion);
    }
    answer--;
    return answer;
}

void printArbol(int Arbol[], int sizeArbol, bool showdepth){
    int actualDepth = -1;
    int unidadBasica = 3;
    int i = 0;
    //bool showdepth = true;
    cout << "TREE" << endl << "------";
    for(int posicion = 1; posicion < sizeArbol+1; posicion++){
        if(depth(posicion) != actualDepth){
            i = 1;
            actualDepth = depth(posicion);
            cout << endl;
            if(showdepth) cout << "Profundidad : {" << actualDepth << "}" << endl;
        }else{
            for (int spaces = 0; spaces < pow(2,depth(sizeArbol+1) - actualDepth) ; ++spaces) cout << " ";
        }

        for (int spaces = 0; spaces < (pow(2,depth(sizeArbol+1) - actualDepth)) -1; ++spaces) cout << " ";
        cout << "" << Arbol[posicion-1] <<"";
    }
    cout << endl;


}


#endif
