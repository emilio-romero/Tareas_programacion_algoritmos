#include "ldijkstra.hpp"

void creaGrafo(int **G, int n, int pi, int pf){
  for(int i=0;i<n;i++){
    for(int j=0;j<i;j++){
      G[j][i]=G[i][j]=(rand()%(n+1));
   }
  }
 G[pi][pf]=G[pf][pi]=0;
}

typedef std::pair<int,int> Par;

int algDijkstra(int **G, int n, int pi, int pf){
  int u;
  int *store=(int*)malloc(n*sizeof(int));
  std::vector<Par > dist; 
  for(int i=0;i<n;i++){
    dist.push_back(Par (1000,i));
    store[i]=-1;
    } 
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
          store[v]=u;
          Q.push(dist[v]);
        } 
      }
    }
  }
  std::cout<<"La distancia mas corta: "<<dist[pf].first<<std::endl;
  std::vector<int> ruta; 
  ruta.push_back(pf);
  while(store[ruta.back()]!=-1){
    ruta.push_back(store[ruta.back()]);
  }
  drawGraphPng(G,n,1,ruta);
  drawGraphPdf(G,n,1,ruta);
free(store);
return 0;}

int drawGraphPng(int **G, int n, int tipo,std::vector<int> mruta){
double space=2*M_PI/(double)n;//Cuantos nodos se dibujaran
  cairo_surface_t *surface;
  cairo_t *cr;
  double colorn[3]={207.0/255.0,0,15.0/255.0};
  double colora[3]={0,0.5,0.5};
  double colorr[3]={58.0/255.0,83.0/255.0,155.0/255.0};
  surface=cairo_image_surface_create(CAIRO_FORMAT_ARGB32,500,500);
  cr=cairo_create(surface);
  cairo_set_line_width(cr,2);
  cairo_set_source_rgb (cr,1,1,1);
  cairo_rectangle(cr,0,0,500,500);
  cairo_fill(cr);
/*Dibujo del grafo*/
  dibujaAristas(cr,G,n); 
  dibujaNodos(cr,n,colorn);
  dibujaRutaA(cr,n,mruta,colorr);
  dibujaRuta(cr,n,mruta,colorr);
/*Fin dibujado de grafo*/
  cairo_surface_write_to_png(surface,"migrafo.png");
  cairo_destroy(cr);
  cairo_surface_destroy(surface);

  for(int i=0;i<mruta.size();i++){
    std::cout<<mruta[i]<<" "<<std::endl; 
  } 
  std::cout<<" \n";
return 1;}

void dibujaRuta(cairo_t *cr,int n,std::vector<int> mruta, double *color){
  double space=2*M_PI/(double)n;//Cuantos nodos se dibujaran
  int nx, ny;
  char numnodo[2];
  for(int i=mruta.size()-1;i>=0;i--){ 
    nx=250+200*cos((double)mruta[i]*space);
    ny=250+200*sin((double)mruta[i]*space);
    creaNodo(cr,nx,ny,color);
    cairo_set_source_rgb (cr,0,0,0);
    cairo_move_to(cr,nx-7,ny+9);
    sprintf(numnodo,"%d",mruta[i]);
    cairo_show_text(cr,numnodo);
  }
}

void creaNodo(cairo_t *cr,int x0, int y0,double *color){
  cairo_set_source_rgb (cr,color[0],color[1],color[2]);
  cairo_arc(cr,x0,y0,20,0,2*3.141592);
  cairo_fill(cr);
}
void creaLinea(cairo_t *cr, int x1, int y1, int x2, int y2){
  cairo_move_to(cr, x1, y1);
  cairo_line_to(cr, x2, y2);
  cairo_stroke(cr);
}

void dibujaRutaA(cairo_t *cr,int n,std::vector<int> mruta, double *color){
  double space=2*M_PI/(double)n;//Cuantos nodos se dibujaran
  int nx, ny;
  int nnx, nny;
  cairo_set_source_rgb (cr,color[0],color[1],color[2]);
  for(int i=mruta.size()-1;i>0;i--){
    nx=250+200*cos((double)mruta[i]*space);
    ny=250+200*sin((double)mruta[i]*space);
    nnx=250+200*cos((double)mruta[i-1]*space);
    nny=250+200*sin((double)mruta[i-1]*space);
        creaLinea(cr,nx,ny,nnx,nny);
  }
}

void dibujaAristas(cairo_t *cr, int **G, int n){
  double space=2*M_PI/(double)n;//Cuantos nodos se dibujaran
  int nx, ny;
  int nnx, nny;
  double m; 
  char weinodo[2];
  cairo_set_font_size(cr,20.0);
  for(int i=1;i<n;i++){//dibujo de vertices 
    nx=250+200*cos((double)i*space);
    ny=250+200*sin((double)i*space);
    for(int j=0;j<i;j++){  
      nnx=250+200*cos((double)j*space);
      nny=250+200*sin((double)j*space);
      if(G[i][j]!=0){
        creaLinea(cr,nx,ny,nnx,nny);
        cairo_set_source_rgb (cr,0,0,0);
        m=calculaPendiente(nx,ny,nnx,nny);
        if(m==0){
        cairo_move_to(cr,nx+(nnx-nx)/3,ny+(nny-ny)/3);
        sprintf(weinodo,"%d",G[i][j]);
        cairo_show_text(cr,weinodo);}
       /* else if(abs(m)>5000){
        cairo_move_to(cr,(nx+nnx)/4,ny);
        sprintf(weinodo,"%d",G[i][j]);
        cairo_show_text(cr,weinodo);} */
        else{
        cairo_move_to(cr,nx+(nnx-nx)/4,ny+(nny-ny)/4);
        sprintf(weinodo,"%d",G[i][j]);
        cairo_show_text(cr,weinodo);}
      }
    }
  }

}
double calculaPendiente(int x1, int y1, int x2, int y2){
  if(x1==x2){
    return 10000.0;
  }
  else if(y1==y2){
    return 0.0;
  }
  else{
   return((double)(y2-y1)/(double)(x2-x1));
  }
}


void dibujaNodos(cairo_t *cr, int n, double *color){
  double space=2*M_PI/(double)n;//Cuantos nodos se dibujaran
  int nx, ny;
  char numnodo[2];
  cairo_select_font_face (cr,"sans",CAIRO_FONT_SLANT_NORMAL,CAIRO_FONT_WEIGHT_NORMAL);
  cairo_set_font_size(cr,24.0);
  for(int i=0;i<n;i++){//Dibujo de nodos
    nx=250+200*cos((double)i*space);
    ny=250+200*sin((double)i*space);
    creaNodo(cr,nx,ny,color);
    cairo_set_source_rgb (cr,0,0,0);
    cairo_move_to(cr,nx-7,ny+9);
    sprintf(numnodo,"%d",i);
    cairo_show_text(cr,numnodo);
  }
}


int drawGraphPdf(int **G, int n, int tipo,std::vector<int> mruta){
double space=2*M_PI/(double)n;//Cuantos nodos se dibujaran
  cairo_surface_t *surface;
  cairo_t *cr;
  double colorn[3]={207.0/255.0,0,15.0/255.0};
  double colora[3]={0,0.5,0.5};
  double colorr[3]={58.0/255.0,83.0/255.0,155.0/255.0};
  surface=cairo_pdf_surface_create("migrafo.pdf",500,500);
  cr=cairo_create(surface);
  cairo_set_line_width(cr,2);
  cairo_set_source_rgb (cr,1,1,1);
  cairo_rectangle(cr,0,0,500,500);
  cairo_fill(cr);
/*Dibujo del grafo*/
  dibujaAristas(cr,G,n); 
  dibujaNodos(cr,n,colorn);
  dibujaRutaA(cr,n,mruta,colorr);
  dibujaRuta(cr,n,mruta,colorr);
/*Fin dibujado de grafo*/
  cairo_show_page(cr);
  cairo_destroy(cr);
  cairo_surface_destroy(surface);

return 1;}














