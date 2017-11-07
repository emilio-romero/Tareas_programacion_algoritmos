#ifndef REDNEURONAL_HPP
#define REDNEURONAL_HPP
#include <iostream>
#include <cmath> 
#include <cstdlib>
#include <cstdio>
#include <string>
#include <ctime>
void nofuncion();
/*Clase neurona*/
class Neurona{
private:
  double valor; //La suma de las entradas
  double valor_activado; //0-1 valor de funcion
  static int num_objs;
  double mbias;
public:
  Neurona(double val);
  Neurona();
  ~Neurona();
  void funcion_activacion();
  void setValor(double x);
  double getValor();
  double getValor_activado();
  //void setBias(double r);
  int getNumobjs();
  void actualizaBias(double lr, double error);
};

/*Conexiones de las neuronas*/
class Sinapsis{
private:
  int ninput; 
  int noutput;
  double **voutput;
  double *vout;
public:
  Sinapsis (int vi, int vo);//Constructor 
  void crea_conexiones();
  void libera_conexiones();
  void llena_conexiones(int **rule);
  void salida(double *indata);
  double *getSalida();
  double **getConexiones();
  void actualizaConexiones(double lr, double error, double *data);
};
/*Funciones de algebra lineal*/
class AlgLineal{
private:
  double sumas; 
public: 
  AlgLineal();
  ~AlgLineal();
  void matxvec(double *x,double **A, double *b, int nr, int nc);
};
/*Funciones para todos*/
double randx();
void readData(int nr, int nc, char *cfile, double **data, double *expected);

#endif 
