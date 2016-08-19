#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main(int argc, char const *argv[]) {
  int N;
  cin >> N;
  int arreglo[N];
  int sumas[N];
  for(int i = 0; i < N; i++) {
    cin >> arreglo[i];
    sumas[i] = 0;
  }
  sumas[0] = max(sumas[0], arreglo[0]);
  int res = 0;
  for(int i = 1; i < N; i++) {
    sumas[i] = max(sumas[i-1] + arreglo[i], arreglo[i]);
    if(sumas[i] > res) {
      res = sumas[i];
    }
  }
  cout << res << endl;
  return 0;
}