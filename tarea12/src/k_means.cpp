#include "k_means.hpp"

Kmedios::Kmedios(int clusters,std::string archiv, int gen){
  cumulos=clusters;
  epocas=gen;
  read_data_txt(archiv);
  set_centroides0();
}
Kmedios::Kmedios(){
  set_centroides0();
}
Kmedios::~Kmedios(){
}

void Kmedios::set_cumulos(int clusters){
  cumulos=clusters;
}


void Kmedios::read_data_txt(std::string archivo){
  std::ifstream mifile;
  mifile.open(archivo.c_str()); 
  std::string valor; 
    getline(mifile,valor,'\t');
    datos1.push_back(atof(valor.c_str()));
    getline(mifile,valor,'\n');
    datos2.push_back(atof(valor.c_str()));
    maxd1=datos1.back(); mind1=datos1.back();
    maxd2=datos2.back(); mind2=datos2.back();
  while(!mifile.eof()){
    getline(mifile,valor,'\t');
    if(strcmp(valor.c_str(),"")!=0) datos1.push_back(atof(valor.c_str()));
     getline(mifile,valor,'\n');
    if(strcmp(valor.c_str(),"")!=0) datos2.push_back(atof(valor.c_str()));
    if(maxd1<datos1.back()) maxd1=datos1.back();
    if(mind1>datos1.back()) mind1=datos1.back();
    if(maxd2<datos2.back()) maxd2=datos2.back();
    if(mind2>datos2.back()) mind2=datos2.back();
  };
  mifile.close();
  t_datos=datos1.size();
  /*//Escala los datos 
  for(int i=0;i<t_datos;i++){
    datos1[i]=datos1[i]/maxd1;
    datos2[i]=datos2[i]/maxd2;
  }*/
}


/*Obtener los datos */
int Kmedios::get_size_datos(){
  return(t_datos);
}

std::vector<double> Kmedios::get_datos1(){
  return(datos1);
}
std::vector<double> Kmedios::get_datos2(){
  return(datos2);
}

void Kmedios::set_centroides0(){
  std::vector<double> cen1; 
  cen1.push_back(0.875*(maxd1-mind1)+mind1);
  cen1.push_back(0.5*(maxd2-mind2)+mind2);
  
  //cen1.push_back(sqrt(0.375*0.375-x0*x0));
  centroides.push_back(cen1);
  double ang=8*atan(1)/(double) cumulos;
  for(int i=1;i<cumulos;i++){
  cen1.clear();
/*//Generados equiespaciados en un "cuadro" de 1x1  
  cen1.push_back((0.375*cos(i*ang)+0.5)*(maxd1-mind1)+mind1);
  cen1.push_back((0.375*sin(i*ang)+0.5)*(maxd2-mind2)+mind2);*/
  //Generados aleatoriamente 
  cen1.push_back(randx()*(maxd1-mind1)+mind1);
  cen1.push_back(randx()*(maxd2-mind2)+mind2);

  centroides.push_back(cen1);}
}

std::vector<std::vector<double> > Kmedios::get_centroides(){
  return(centroides);
}

std::vector<int> Kmedios::get_etiquetas(){
  return(etiquetas);
}


/*Funciones para distancias*/
double Kmedios::dist_euclides(double x1, double y1, double x2, double y2){
  double dx=x2-x1;
  double dy=y2-y1;
  return((dx*dx+dy*dy));
}


/*Miscelanea*/
double randx(){
  return(rand()/(double)RAND_MAX);
}

/*El algoritmo principal*/
void Kmedios::Algoritmo(){
double d1,d2;
int cuen=0;
std::vector<std::vector<double> > viejos=centroides;
  for(int cont=0;cont<epocas;cont++){
    etiquetas.clear();
    etiqueta_datos();
    recalculate_centroides();
    /*Condicion de paro*/
    //std::cout<<"Error: "<<error(viejos)<<std::endl;
    cuen++;
    if(error(viejos)<0.0005) break; 
    else viejos=centroides;
    /*Condicion de paro fin*/
  }
  std::cout<<"Se hicieron <"<<cuen<<"> iteraciones."<<std::endl;
  /*//Reescalar los centroides si fueron escalados
  for(int i=0;i<cumulos;i++){
    centroides[i][0]=centroides[i][0]*maxd1;
    centroides[i][1]=centroides[i][1]*maxd2;
  }*/

}

void Kmedios::etiqueta_datos(){
double d1,d2;
for(int i=0;i<t_datos;i++){
  etiquetas.push_back(0);
  d1=dist_euclides(datos1[i],datos2[i],centroides[0][0],centroides[0][1]);
  for(int j=1;j<cumulos;j++){
    d2=dist_euclides(datos1[i],datos2[i],centroides[j][0],centroides[j][1]);
    if(d2<=d1){
      d1=d2;
      etiquetas[i]=j;
    } 
  }

}
}

void Kmedios::recalculate_centroides(){
double sumax,sumay;
int cant; 
for(int i=0;i<cumulos;i++){
  sumax=0; sumay=0;
  cant=0;
  for(int j=0;j<t_datos;j++){
    if(etiquetas[j]==i){
      sumax+=datos1[j];
      sumay+=datos2[j];
      cant++;
    }
  }
 centroides[i][0]=sumax/(double)(cant+0.1);
 centroides[i][1]=sumay/(double)(cant+0.1);
}
}

double Kmedios::error(std::vector<std::vector<double> > oldcentros){
  double tx=0,ty=0, total=0;
  for(int i=0;i<cumulos;i++){
    tx+=(oldcentros[i][0]-centroides[i][0])*(oldcentros[i][0]-centroides[i][0])/
    (centroides[i][0]*centroides[i][0]);
    ty+=(oldcentros[i][1]-centroides[i][1])*(oldcentros[i][1]-centroides[i][1])/
    (centroides[i][1]*centroides[i][1]);
  }
 total=sqrt(tx+ty); 
return(total);
}

/*Fin del algoritmo principal*/
/*Dibujar los clusters*/
int Kmedios::drawClusters(){
  cairo_surface_t *surface; 
  cairo_t *cr; 
  surface=cairo_image_surface_create(CAIRO_FORMAT_ARGB32,500,500);
  cr=cairo_create(surface);
  cairo_set_line_width(cr,2);
  cairo_set_source_rgb (cr,1,1,1);
  cairo_rectangle(cr,0,0,500,500);
  cairo_fill(cr);
  /*Prepara el lienzo*/
  genera_labels(cr);
  /*Dibuja!*/
  for(int et=0;et<cumulos;et++){
    cairo_set_source_rgb (cr,randx(),randx(),randx());
    for(int i=0;i<t_datos;i++){
      if(etiquetas[i]==et){
      punto(cr,datos1[i],datos2[i]);}
    }
  }
  drawCentroides(cr);
  /**/
  cairo_surface_write_to_png(surface,"clusters.png");
  cairo_destroy(cr);
  cairo_surface_destroy(surface);
}

void Kmedios::genera_labels(cairo_t *cr){
  double ejex=500.0-(500.0/8.0);
  double ejey=500.0/8.0;
  double origenx=500.0/8.0; 
  double origeny=500.0-(500.0/8.0);
  cairo_set_source_rgb(cr,0.0,0.0,0.0);
  cairo_set_line_width(cr,3.0);
  cairo_move_to(cr,origenx,origeny); cairo_line_to(cr,ejex,origeny); cairo_stroke(cr);
  cairo_move_to(cr,origenx,origeny); cairo_line_to(cr,origenx,ejey); cairo_stroke(cr);
  double metricax=(ejex-origenx)/10.0;
  double metricay=(origeny-ejey)/10.0;
  /*for(int i=0;i<11;i++){
  cairo_set_source_rgb(cr,0.0,0.0,0.0);
  cairo_select_font_face (cr,"Sans",CAIRO_FONT_SLANT_NORMAL,CAIRO_FONT_WEIGHT_NORMAL);
  cairo_set_font_size(cr,10.0);
  cairo_move_to(cr,(origenx+(metricax*i)),(origeny+10));
  cairo_save(cr);
  cairo_rotate(cr,45.0);
  //cairo_
  }*/
}

void Kmedios::punto(cairo_t * cr,double mix, double miy){
 double nx=500/8.0+(500-500/8.0)*(mix/maxd1);//Seria normalmente la longitud
 double ny=(500-500/8.0)-((500.0-500/8.0)*(miy/maxd2));//Seria normalmente la altura
// cairo_set_source_rgb(cr,0.69,0.19,0);
 cairo_arc(cr,nx,ny,2.1,0,2*M_PI);
 cairo_fill(cr);
}

void Kmedios::drawCentroides(cairo_t *cr){
 double nx;//Seria normalmente la longitud
 double ny;//Seria normalmente la altura
 double origenx=500.0/8.0;
 double origeny=500.0-(500.0/8.0);
 cairo_set_source_rgb(cr,0.0,0.0,0.0);
 for(int i=0;i<cumulos;i++){
  nx=origenx+(500-500/8.0)*(centroides[i][0]/maxd1);
  ny=origeny-((500.0-500/8.0)*(centroides[i][1]/maxd2));
  cairo_arc(cr,nx,ny,5,0,2*M_PI);
  cairo_fill(cr);
 }
}
