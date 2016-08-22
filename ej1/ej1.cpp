#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>

using namespace std;

// Calcula todas las posibles soluciones de D[inicio,fin) y las guarda en soluciones[empezar,empezar+2^(fin-inicio))
void calcularSoluciones(vector<int>* D, vector<int>* soluciones, int inicio, int fin, int empezar) {
  // Itero sobre todas las posibles soluciones, usando el int "posiblesSoluciones" como mascara de bits
  // Para determinar si el pack de donas "i" pertenece o no a la solucion actual veo si el bit "i" de
  // posiblesSoluciones esta prendido o no
  int posiblesSoluciones = pow(2,fin-inicio)-1; // Inicializo posiblesSoluciones con el valor de las posibles soluciones
  while(posiblesSoluciones >= 0) { // Mientras haya soluciones para evaluar...
    int sumaDonasSolucionActual = 0; // sumaDonasSolucionActual guarda la suma de las donas de la solucion actual
    for(int i = 0; i < fin-inicio; i++) { // Itero los fin-inicio packs de donas de la mitad actual
      if(posiblesSoluciones & (1<<i)) { // Si el pack de donas "i" pertenece a la solucion actual...
        sumaDonasSolucionActual+=(*D)[i+inicio]; // Actualizo la suma parcial de las donas de la solucion actual
      }
    }
    // Ahora que ya recorri todos los packs de donas y sume los que pertenecian a la solucion actual,
    // guardo en el vector soluciones la suma de las donas, y avanzo el puntero "empezar" para seguir 
    // escribiendo en la siguiente posicion
    (*soluciones)[empezar] = sumaDonasSolucionActual;
    empezar++;
    posiblesSoluciones--;
  }
}

// Devuelve el valor de soluciones[inicio, fin) X que maximiza la inecuacion X + Y <= P haciendo una suerte de
// busqueda binaria ya que el vector "soluciones" esta ordenado
int buscarOptimo(vector<int>* soluciones, int inicio, int fin, int Y, int P) {
  int res; // Guarda el X optimo
  if(fin-inicio <= 1) { // Si hay un solo elemento lo devuelvo
    res = (*soluciones)[inicio];
  } else { // Si hay varios elementos, parto en la mitad al arreglo, y me fijo para que lado tengo que moverme
    int medio = (inicio+fin)/2;
    if((*soluciones)[medio] + Y > P) { // Si con el elemento de la mitad supere a P, me llamo recursivamente en la primer mitad ya que todos los numeros menores a "medio" estan a la izquierda
      res = buscarOptimo(soluciones, inicio, medio, Y, P);
    } else if((*soluciones)[medio] + Y < P) { // Si con el elemento de la mitad no alcance a P, me llamo recursivamente en la segunda mitad ya que todos los numeros mayores a "medio" estan a la derecha
      res = buscarOptimo(soluciones, medio, fin, Y, P);
    } else { // Si con el elemento de la mitad llegue a P, ya llegue al valor maximo de la inecuacion y puedo devolverlo sin problemas
      res = (*soluciones)[medio];
    }
  }
  return res;
}

int main() {
  int P, N;
  cin >> P >> N; // Obtengo P y N del input

  bool esImpar = (N%2==1); // Si es impar, tengo que agregar un elemento al final con valor 0 asi puedo dividir por la mitad bien. Notar que agregar un paquete de 0 donas no afecta en lo absoluto al problema original
  
  vector<int> D(N);
  for(int i = 0; i < N; i++) { // Relleno D (el vector que guarda los packs de donas) con los valores de entrada
    cin >> D[i];
  }

  if(esImpar) { // Si N era impar, le agrego el elemento mencionado anteriormente (pack de 0 donas) para que N sea par
    D.push_back(0);
    N++;
  }
  
  // Divido a la mitad el arreglo D y calculo todas las posibles soluciones tanto de una mitad como de la otra
  int mitad = N/2;
  vector<int> soluciones(pow(2, (N/2)+1)); // Vector donde voy a guardar las 2^(N/2 + 1) soluciones
  calcularSoluciones(&D, &soluciones, 0, mitad, 0); // Relleno la primer mitad del vector "soluciones"
  calcularSoluciones(&D, &soluciones, mitad, N, pow(2, (N/2))); // Relleno la segunda mitad del vector "soluciones"
  
  
  // Ordeno la segunda mitad de "soluciones"
  sort(soluciones.begin()+pow(2, (N/2)), soluciones.end());

  // Recorro la primer mitad de "soluciones". Para cada solucion X dentro de esa primer mitad,
  // busco con busqueda binaria la solucion Y en la otra mitad que maximice la inecuacion X+Y <= P
  int solucionOptimaTotal = 0; // Guardara la maxima solucion total (suma de dos subsoluciones, una de la derecha y la otra de la izquierda)
  for(int i = 0; i < pow(2, (N/2)); i++) {
    int solucionIzquierda = soluciones[i];
    int solucionDerechaOptima = buscarOptimo(&soluciones, pow(2, (N/2)), pow(2, (N/2)+1), solucionIzquierda, P);
    int solucionActual = solucionIzquierda + solucionDerechaOptima;
    if(solucionActual > solucionOptimaTotal && solucionActual <= P) { // Si la solucion actual es mayor a la guardada como solucion optima, actualizo la solucion optima con el valor de la solucion actual (siempre y cuando la solucion actual no supere a P)
      solucionOptimaTotal = solucionActual;
    }
  }

  cout << solucionOptimaTotal << endl; // Escribo el resultado

  return 0;
}