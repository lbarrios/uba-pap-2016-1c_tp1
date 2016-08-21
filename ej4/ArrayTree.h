#ifndef __PAP_ARRAYTREE__
#define __PAP_ARRAYTREE__

#include <iostream>
#include <assert.h>
#include <math.h>
#include "ArrayAlgebra.h"

template <class T>
T poblarArbolIterativo(T neutro, T Arbol [], int sizeArbol, T Inputs[], int sizeInputs, int posicion){
    if(isLeaf(sizeArbol,posicion)){
        if(sizeInputs <= posicion - firstLeaf(sizeArbol)){
            Arbol[posicion] = neutro;
        }else{
            Arbol[posicion] = Inputs[posicion - firstLeaf(sizeArbol)];
        }
    }else{
        Arbol[posicion] = poblarArbolIterativo(neutro, Arbol, sizeArbol, Inputs, sizeInputs, getRightChildren(sizeArbol,posicion))
        * poblarArbolIterativo(neutro, Arbol, sizeArbol, Inputs, sizeInputs, getLeftChildren(sizeArbol,posicion));
    }
    return Arbol[posicion];
}


template <typename T>
void poblarArbol(T neutro, T Arbol [], int sizeArbol, T Inputs[], int sizeInputs){
    assert(sizeInputs <= (sizeArbol + 1)/2);
    poblarArbolIterativo(neutro, Arbol, sizeArbol, Inputs, sizeInputs, 0);
}

template <typename T>
T resolverConjuntoIterativo(T neutro, T Arbol[], int sizeArbol, int startConjunto, int endConjunto, int posicion){
    assert(endConjunto < sizeArbol - firstLeaf(sizeArbol));
    int leftDomain = getConjuntoLeft(sizeArbol,posicion);
    int rightDomain = getConjuntoRight(sizeArbol,posicion);

    T answer;

    if(startConjunto<=leftDomain and rightDomain<=endConjunto){
        answer = Arbol[posicion];
    }else{
        int leftChildLeftDomain = getConjuntoLeft(sizeArbol,getLeftChildren(sizeArbol,posicion));
        int leftChildRightDomain = getConjuntoRight(sizeArbol,getLeftChildren(sizeArbol,posicion));
        int rightChildLeftDomain = getConjuntoLeft(sizeArbol,getRightChildren(sizeArbol,posicion));
        int rightChildRightDomain = getConjuntoRight(sizeArbol,getRightChildren(sizeArbol,posicion));

        T leftAnswer = neutro;
        T rightAnswer = neutro;

        if((startConjunto<=leftChildLeftDomain and leftChildLeftDomain<=endConjunto)
           or (startConjunto<=leftChildRightDomain and leftChildRightDomain<=endConjunto) ){
            leftAnswer = resolverConjuntoIterativo(
                                          neutro, Arbol, sizeArbol, startConjunto,endConjunto,getLeftChildren(sizeArbol,posicion)
                                          );
        }

        if((startConjunto<=rightChildLeftDomain and rightChildLeftDomain<=endConjunto)
           or (startConjunto<=rightChildRightDomain and rightChildRightDomain<=endConjunto) ){
            rightAnswer = resolverConjuntoIterativo(
                                          neutro, Arbol, sizeArbol, startConjunto,endConjunto, getRightChildren(sizeArbol,posicion)
                                           );
        }
        answer = leftAnswer * rightAnswer;
    }
    return answer;
}

#endif

template <typename T>
T resolverConjunto(T neutro, T Arbol[], int sizeArbol, int startConjunto, int endConjunto){
    return resolverConjuntoIterativo(neutro, Arbol, sizeArbol, startConjunto, endConjunto, 0);
}
