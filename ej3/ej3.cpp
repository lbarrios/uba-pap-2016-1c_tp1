#include <iostream>
#include <algorithm>

using namespace std;

int main() {
  // Obtengo N
  int N;
  cin >> N;

  // Creo dos arreglos de int:
  // "A" que va a guardar los A_i que vienen del input
  // "sumaMax" que va a guardar en la posicion "i" la suma del subarreglo de suma maxima considerando A[0, i]
  int A[N];
  int sumaMax[N];

  // Relleno A con los valores del input
  for(int i = 0; i < N; i++) {
    cin >> A[i];
  }

  // La primer posicion va a ser el maximo entre el subarreglo vacio (cuya suma es igual a 0), o el primer 
  // valor de A
  sumaMax[0] = max(0, A[0]);

  // Calculamos linealmente todas las posiciones de sumaMax usando la funcion de recurrencia a la vez que 
  // vamos guardando un maximo local para que al finalizar el recorrido lineal tengamos el maximo absoluto 
  // y asi poder devolverlo
  int res = sumaMax[0];
  for(int i = 1; i < N; i++) {
    // Usamos la formulacion recursiva que enunciamos en el informe para calcular la posicion i de sumaMax
    sumaMax[i] = max(sumaMax[i-1] + A[i], A[i]);
    if(sumaMax[i] > res) { // Este if se usa para ir guardando los maximos locales
      res = sumaMax[i];
    }
  }

  // res guarda el maximo absoluto, que hay que devolver
  cout << res << endl;

  return 0;
}