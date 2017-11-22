#ifndef K_MEANS_HPP
#define K_MEANS_HPP
#include <iostream> 
#include <cstdlib> 
#include <cmath> 
#include <vector>
#include <string> 
#include <cstring> 
#include <fstream>
#include <ctime>
#include <cairo/cairo.h>
//#include <cairo/cairo-pdf.h>
class Kmedios{
private:
  int epocas;
  int cumulos;
  std::vector<double> datos1; 
  std::vector<double> datos2;
  std::vector<int> etiquetas;
  double maxd1,maxd2,mind1,mind2;
  int t_datos;
  std::vector<std::vector<double> > centroides;
public:
  Kmedios(int,std::string,int);
  Kmedios();
  ~Kmedios();
  void set_cumulos(int);
  void read_data_txt(std::string);
  std::vector<double> get_datos1();
  std::vector<double> get_datos2();
  int get_size_datos();
  void set_centroides0();
  std::vector<std::vector<double> > get_centroides();
  /*Funciones algoritmo*/
  void Algoritmo();
  void etiqueta_datos();
  void recalculate_centroides();
  double error(std::vector<std::vector<double> >);
  /*Fin funciones algoritmo*/
  std::vector<int> get_etiquetas();
  /*Funciones para distancias*/
  double dist_euclides(double,double,double,double);
  /*Funciones para dibujar*/
  int drawClusters();
  void punto(cairo_t *,double, double);
  void genera_labels(cairo_t *);
  void drawCentroides(cairo_t *);
};

double randx();

#endif 
