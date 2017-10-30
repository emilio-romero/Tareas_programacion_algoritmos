#include "ldijkstra.hpp"
#include <ctime>
using namespace std; 
int main(){
srand(time(NULL));
int n=4;
int **grafo=(int**)malloc(n*sizeof(int*));
for(int i=0;i<n;i++) grafo[i]=(int*)malloc(n*sizeof(int));
  creaGrafo(grafo,n);

  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
      cout<<grafo[i][j]<<" ";
    } cout<<"\n";
  }
  algDijkstra(grafo,n,0,n-1);

for(int i=0;i<n;i++) free(grafo[i]);
free(grafo);
cout<<"Su programa ha terminado\n";
return 0;}
