#include "ldijkstra.hpp"
#include <ctime>
using namespace std; 
int main(int argc, char *argv[]){
srand(time(NULL));
int n;
if(argc>1) n=atoi(argv[1]);
else n=7;
int **grafo=(int**)malloc(n*sizeof(int*));
for(int i=0;i<n;i++) grafo[i]=(int*)malloc(n*sizeof(int));
  
  creaGrafo(grafo,n,0,n-1);
  algDijkstra(grafo,n,0,n-1);

for(int i=0;i<n;i++) free(grafo[i]);
free(grafo);
cout<<"Su programa ha terminado\n";
return 0;}
