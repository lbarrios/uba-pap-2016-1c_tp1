#include <iostream>
#include <vector>
#include <math.h>
#include <limits.h>

using namespace std;

//Devuelve la diversion que aporta el subconjunto representado por el binario del entero c. 
int diversion(int c, int n, vector<vector<int> >* amistades){
  int res = 0;
  for(int i = 0; i<n; i++){
    if(c & (1<<i)){
      //Si el iesimo bit esta prendido tengo que calcular la amistad que aporta
      //esa persona con todas las demas que tambien estan en el subconjunto
      for(int j = i; j<n; j++){
        if(c & (1<<j)){
          //Chequeo las otras personas que estan en el grupo(o sea que tienen
          //el bit en 1) y sumo la diversion que aportan
          res+=(*amistades)[i][j];
        }
      }
    }
  }
  return res;
}


//Devuelve la diversion maxima que puede aportar el subconjunto s, mirando
//todos sus subconjuntos y sus combinaciones
int maximaDiversion(int s, vector<vector<int> >* amistades, vector<bool>* CALCULADA_MAXIMA_DIVERSION, vector<int>* MAXIMA_DIVERSION, int n){
  //Si el resultado ya fue calculado lo devuelvo
  if((*CALCULADA_MAXIMA_DIVERSION)[s]) return (*MAXIMA_DIVERSION)[s];
  //Si llegue al caso base en el cual el numero binario s es 0, devuelvo 0,
  //pues no suma diversion
  if(s == 0) return 0;
  int maximaDiversionPosible = INT_MIN;
  int complemento, diversion_actual;
  int mascara_de_unos = pow(2,n) - 1;
  for(int i = s; i != 0; i = s & (i-1)){ //Recorro todos los posibles subconjuntos de s
    //Calculo el conjunto complemento de i
    complemento = (i^mascara_de_unos) & s;
    //Calculo la diversion que aporta el subconjunto y la de su complemento
    diversion_actual = diversion(i, n, amistades) + maximaDiversion(complemento, amistades, CALCULADA_MAXIMA_DIVERSION, MAXIMA_DIVERSION, n);
    //Actualizo la maxima diversion hasta el momento
    maximaDiversionPosible = (diversion_actual > maximaDiversionPosible) ? diversion_actual : maximaDiversionPosible;
  }
  //Actualizo el arreglo dinamico con lo que acabo de calcular
  (*CALCULADA_MAXIMA_DIVERSION)[s] = true;
  (*MAXIMA_DIVERSION)[s] = maximaDiversionPosible;
  return maximaDiversionPosible;
}




int main(int argc, char const *argv[]){
  int n;
  cin >> n;
  int cantidad_de_conjuntos_posibles = pow(2,n);
  vector<bool> CALCULADA_MAXIMA_DIVERSION(cantidad_de_conjuntos_posibles, false);
  vector<int> MAXIMA_DIVERSION(cantidad_de_conjuntos_posibles, INT_MIN); //Guardo la maxima diversion que puede aportar cada subconjunto
  vector<vector<int> > amistades(n, vector<int>(n));
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      cin >> amistades[i][j];
    }
  }
  cout << maximaDiversion(cantidad_de_conjuntos_posibles-1, &amistades, &CALCULADA_MAXIMA_DIVERSION, &MAXIMA_DIVERSION, n) << endl;
  return 0;
}
