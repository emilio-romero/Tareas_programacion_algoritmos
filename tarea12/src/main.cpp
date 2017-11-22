#include <iostream>
#include <sqlite3.h>
#include "k_means.hpp"
using namespace std;
int main(){
srand(time(NULL));
string misdatos;
int nc;
cout<<"Introduzca el archivo: ";
cin>> misdatos;
cout<<"\n Introduzca la cantidad de clusters: ";
cin>> nc;
Kmedios mimina= Kmedios(nc,misdatos,100);

cout<<"La cantidad de datos es: "<<mimina.get_size_datos()<<endl;

mimina.Algoritmo();
for(int i=0;i<nc;i++){
  cout<<mimina.get_centroides()[i][0]<<", "<<mimina.get_centroides()[i][1]<<endl;
}
mimina.drawClusters();
return 0;}
