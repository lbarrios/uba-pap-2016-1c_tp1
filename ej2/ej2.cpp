#include <iostream>
#include <vector>
#include <math.h>
#include <limits.h>

using namespace std;

//Devuelve la diversion que aporta la fiesta representada por el subconjunto
//representado por el binario que representa al entero C. 
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


int main(int argc, char const *argv[]){
  int n;
  cin >> n;
  vector<vector<int> > amistades(n, vector<int>(n));
  //Parseo la matriz de amistades entre las amigas
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      cin >> amistades[i][j];
    }
  }
  int res = 0; 
  //En res guardo el resultado total de diversion
  int original = pow(2,n) - 1; 
  //En original guardo la configuracion original(en bits) del arreglo de amigas, la cual comienza con todos los bits en 1.
  //Cada bit representa si la amiga Ai esta en el subconjunto o no
  int conj_actual = original;
  //En conj_actual guardo el conjunto candidato para una fiesta(inicialmente es una fiesta con todas las amigas)
  while(original != 0){ //Itero hasta no tener mas subconjuntos para analizar, es decir que todos los bits son cero
    int div_actual = INT_MIN;
    //En div_actual guardo la diversion actual que aporta el conjunto candidato
    //que estoy recorriendo
    for(int i = original; i!=0; i = original & (i-1)){ //Recorro todos los posibles subconjuntos del original para analizar la diversion que aporta
      int div_candidata = diversion(i, n, &amistades);
      //Calculo la diversion que tiene este subconjunto
      if((div_candidata > div_actual) || ((div_candidata == div_actual) && (i < conj_actual))){
        //Si la diversion que aporta este subconjunto es mayor a la anterior o
        //si las diversiones son iguales, pero arme un grupo con menos
        //personas, me guardo la diversion que aporta y el numero que representa a ese
        //subconjunto
        div_actual = div_candidata;
        conj_actual = i;
      }
    }
    //Al terminar el ciclo, tengo en conj_actual el conjunto que mas diversion
    //aporta, asi que debo sacarlo del conjunto original para seguir armando
    //conjuntos con las personas que quedan. Limpio los bits con un XOR
    original = original^conj_actual;
    //Actualizo la diversion acumulada
    res += div_actual;
  }
  cout << res;
  return 0;
}
