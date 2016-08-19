#include <iostream>
#include "../catedra/libs/Matriz.h"

using namespace std;

bool aux(Matriz M, Matriz arreglo[], int N, int L, int inicio, int fin) {
  if(fin-inicio <= L) {
    //ad hoc
    //multiplicar las L matrices, agregando por izquierda o por derecha sea cual fuese el caso
    int diferencia = L-(fin-inicio); //cuantas posiciones me faltan para llegar a L
    while(inicio >= 0 && diferencia > 0) {
      inicio--;
      diferencia--;
    }
    if(diferencia > 0) {
      while(fin <= N && diferencia > 0) {
        fin++;
        diferencia--;
      }
    }
    if(diferencia > 0) return false;
    //se llego a L con inicio y fin (hay q comprobar que fin-inicio = L
    Matriz producto = id();
    for(int i = inicio; i < fin; i++) {
      producto = producto * arreglo[i];
    }
    return (producto == M);
  } else { //dividir y combinar
    int medio = (inicio+fin)/2;
    bool izq = aux(M, arreglo, N, L, inicio, medio);
    bool der = aux(M, arreglo, N, L, medio, fin);
    if(izq || der) { // si alguno dio true, significa que existe el subarreglo
      return true;
    } else { //sino, falta todavía ver el medio
      inicio = medio - L;
      if(inicio < 0) inicio = 0;
      fin = medio + L;
      if(fin > N) fin = N;
      bool res = false;
      for(int i = inicio; i < fin+1-L; i++) { // veo todas las opciones que pasen por el medio, el tema es que no se si esto es N^2 ....
        Matriz producto = id();
        for(int j = i; j < i+L; j++) {
          producto = producto*arreglo[j];
        }
        if(producto == M) {
          res = true;
        }
      }
      return res;
    }
  }
}

int main(int argc, char const *argv[]) {
  int N;
  cin >> N;
  int L;
  cin >> L;
  vector<int> vectorM(9);
  Matriz arreglo[N];
  for(int i = 0; i < 9; i++) {
    cin >> vectorM[i];
  }
  Matriz M = Matriz(vectorM);
  for(int i = 0; i < N; i++) {
    vector<int> matrizAux(9);
    for(int j = 0; j < 9; j++) {
      cin >> matrizAux[j];
    }
    arreglo[i] = Matriz(matrizAux);
  }
  
  if(aux(M, arreglo, N, L, 0, N)) {
    cout << "SI" << endl;
  } else {
    cout << "NO" << endl;
  }
  
  return 0;
}