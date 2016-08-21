#include <iostream>
#include <assert.h>
#include <math.h>
#include "ArrayAlgebra.h"
#include "ArrayTree.h"
#include "..\catedra\libs\Matriz.h"

using namespace std;

int main()
{
    int i1 [8] = {2,1,1,-1,2,1,2,3};
    cout << proximoCuadrado(3);
    int i2 [15] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    Matriz m1 [8] = {Matriz(),Matriz(),Matriz(),Matriz(),Matriz(),Matriz(),Matriz(),Matriz()};

   // Matriz m2

    printArbol(i2,15, false);
    poblarArbol(1, i2, 15, i1, 8);
    printArbol(i2,15, false);
    cout << resolverConjunto(1,i2,15,2,4) << endl;
    return 0;

}
