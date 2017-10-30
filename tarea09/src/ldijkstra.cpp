#include "ldijkstra.hpp"

void creaGrafo(int **G, int n){
  for(int i=0;i<n;i++){
    for(int j=0;j<i;j++){
      G[j][i]=G[i][j]=(1+rand()%5)*(rand()%6);
   }
  }
}

typedef std::pair<int,int> Par;

int algDijkstra(int **G, int n, int pi, int pf){
  int u;
  std::vector<Par > dist; 
  for(int i=0;i<n;i++)
    dist.push_back(Par (1000,i)); 
  dist[pi].first=0;
  std::priority_queue<Par, std::vector<Par>, std::greater<Par> > Q;
   Q.push(dist[pi]);
  while(!Q.empty()){
    u=Q.top().second;
    Q.pop();
    for(int v=0;v<n;v++){
      if(v!=u && G[u][v]!=0){
        if(dist[v].first>(dist[u].first +G[u][v])){
          dist[v].first=dist[u].first +G[u][v];
          Q.push(dist[v]);
        } 
      }
    }
  }
  std::cout<<"dist[v]: "<<dist[pf].first<<std::endl;
return 0;}
