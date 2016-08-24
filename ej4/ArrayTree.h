#ifndef __PAP_ARRAYTREE__
#define __PAP_ARRAYTREE__

#include <iostream>
#include <assert.h>
#include <math.h>
#include "ArrayAlgebra.h"

template <class T>
T poblarArbolIterativo(T neutro, T Arbol [], int sizeArbol, T Inputs[], int sizeInputs, int posicion){
    //Si es una hoja
    if(isLeaf(sizeArbol,posicion)){

        bool elInputNoTieneMasValoresParaDevolver = sizeInputs <= posicion - firstLeaf(sizeArbol);

        if(elInputNoTieneMasValoresParaDevolver){Arbol[posicion] = neutro;}

        else{Arbol[posicion] = Inputs[posicion - firstLeaf(sizeArbol)];}

    }else{

        T valorHijoIzquierdo = poblarArbolIterativo(neutro, Arbol, sizeArbol, Inputs, sizeInputs, getLeftChildren(sizeArbol,posicion));
        T valorHijoDerecho =   poblarArbolIterativo(neutro, Arbol, sizeArbol, Inputs, sizeInputs, getRightChildren(sizeArbol,posicion));

        Arbol[posicion] = valorHijoIzquierdo * valorHijoDerecho;
    }

    return Arbol[posicion];

}

//Funcion que empieze a correr el iterativo desde 0
template <typename T>
void poblarArbol(T neutro, T Arbol [], int sizeArbol, T Inputs[], int sizeInputs){
    assert(sizeInputs <= (sizeArbol + 1)/2);
    poblarArbolIterativo(neutro, Arbol, sizeArbol, Inputs, sizeInputs, 0);
}

template <typename T>
T resolverIntervaloIterativo(T neutro, T Arbol[], int sizeArbol, int startIntervalo, int endIntervalo, int posicion){
    assert(endIntervalo < sizeArbol - firstLeaf(sizeArbol));

    //Eligo los descendientes mas lejanos para crear el intervalo con el cual comparar
    int leftmostDescendant = getLeftmostDescendant(sizeArbol,posicion);
    int rightmostDescendant = getRightmostDescendant(sizeArbol,posicion);

    T answer;

    bool estaTotalmenteContenidoEnLaBusqueda =
                            (startIntervalo<=leftmostDescendant and rightmostDescendant<=endIntervalo);

    //Si el nodo actual esta enteramente contenido dentro de ese intervalo
    if(estaTotalmenteContenidoEnLaBusqueda){
        answer = Arbol[posicion]; //Dejo de iterar y devuelvo el valor actual
    }else{

        T leftAnswer;
        T rightAnswer;

    //En caso contrario, me fijo en los hijos.

        int leftChildLeftDescendant = getLeftmostDescendant(sizeArbol,getLeftChildren(sizeArbol,posicion));
        int leftChildRightDescendant = getRightmostDescendant(sizeArbol,getLeftChildren(sizeArbol,posicion));
        int rightChildLeftDescendant = getLeftmostDescendant(sizeArbol,getRightChildren(sizeArbol,posicion));
        int rightChildRightDescendant = getRightmostDescendant(sizeArbol,getRightChildren(sizeArbol,posicion));



        //Me fijo si alguno de los dos hijos tienen elementos que estan la busqeuda
        bool elHijoIzquierdoEstaContenidoEnLaBusqueda = (
            (startIntervalo<=leftChildLeftDescendant and leftChildLeftDescendant<=endIntervalo)
           or (startIntervalo<=leftChildRightDescendant and leftChildRightDescendant<=endIntervalo));

        bool elHijoDerechoEstaContenidoEnLaBusqueda = (
                (startIntervalo<=rightChildLeftDescendant and rightChildLeftDescendant<=endIntervalo)
             or (startIntervalo<=rightChildRightDescendant and rightChildRightDescendant<=endIntervalo));

        if(elHijoIzquierdoEstaContenidoEnLaBusqueda){
            leftAnswer = resolverIntervaloIterativo(
            neutro, Arbol, sizeArbol, startIntervalo,endIntervalo,getLeftChildren(sizeArbol,posicion));
        }
        else{leftAnswer = neutro;}


        if(elHijoDerechoEstaContenidoEnLaBusqueda){
            rightAnswer = resolverIntervaloIterativo(
            neutro, Arbol, sizeArbol, startIntervalo,endIntervalo, getRightChildren(sizeArbol,posicion));
        }
        else{rightAnswer = neutro;}

        answer = leftAnswer * rightAnswer;
    }
    return answer;
}

#endif

//Funcion que empieze a correr el iterativo desde 0
template <typename T>
T resolverIntervalo(T neutro, T Arbol[], int sizeArbol, int startIntervalo, int endIntervalo){
    return resolverIntervaloIterativo(neutro, Arbol, sizeArbol, startIntervalo, endIntervalo, 0);
}
