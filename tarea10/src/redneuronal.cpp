#include "redneuronal.hpp"

void nofuncion(){
  std::cout<<"Funcion inicio\n";
}

Neurona::Neurona(double val){
  valor=val; 
  funcion_activacion();
  //setBias();
  num_objs++; 
}
Neurona::Neurona(){
//  mbias=randx();
  //setBias();
}
Neurona::~Neurona(){
}

int Neurona::num_objs=0; 
void Neurona::funcion_activacion(){
    valor_activado=1.0/(1+exp(-1.0*(valor+mbias)));
}
double  mbias=randx();
void Neurona::setValor(double x){
  valor=x;
  funcion_activacion();
}

double Neurona::getValor(){
  return valor;
};

double Neurona::getValor_activado(){
  return valor_activado;
};

int Neurona::getNumobjs(){
  return num_objs;
}

void Neurona::actualizaBias(double lr, double error){
  mbias=mbias+lr*error;
}
/*Funciones de Sinapsis*/
Sinapsis::Sinapsis(int vi, int vo){
  ninput=vi; 
  noutput=vo;
  crea_conexiones();
}

void Sinapsis::crea_conexiones(){
  voutput=(double**)malloc(noutput*sizeof(double*));
  for(int i=0;i<noutput;i++) voutput[i]=(double*)malloc(ninput*sizeof(double));
}
void Sinapsis::libera_conexiones(){
  for(int i=0;i<noutput;i++) free(voutput[i]);
  free(voutput);
}

void Sinapsis::llena_conexiones(int **rule){
  for(int i=0;i<noutput;i++){
    for(int j=0;j<ninput;j++){
      voutput[i][j]=randx();
    }
  }
}

void Sinapsis::salida(double *indata){
  AlgLineal myalg;
  vout=(double *)malloc(noutput*sizeof(double));
  myalg.matxvec(vout,voutput,indata,noutput,ninput);
}

double *Sinapsis::getSalida(){
  return vout;
}
double **Sinapsis::getConexiones(){
  return voutput;
}

void Sinapsis::actualizaConexiones(double lr, double error, double *data){
  for(int i=0;i<noutput;i++){
    for(int j=0;j<ninput;j++){
      voutput[i][j]=voutput[i][j]+(lr*error*data[j]);
    }
  }
}

/*Funciones de algebra lineal*/
AlgLineal::AlgLineal(){
}
AlgLineal::~AlgLineal(){
}

void AlgLineal::matxvec(double *x, double **A, double *b, int nr, int nc){
  double suma;
  for(int i=0;i<nr;i++){
    suma=0;
    for(int j=0;j<nc;j++){
      suma+=A[i][j]*b[j];
    }
    x[i]=suma;
  }
}




/*Funciones para todos*/
double randx(){
  double aux;
  aux=(rand()/static_cast<double>(RAND_MAX));
return aux;}

void readData(int nr, int nc, std::string cfile, double **data, double *expected){
  std::ifstream mifile;
  mifile.open(cfile);
  std::string valor;
  for(int mi=0;mi<nr;mi++){
    for(int j=0;j<nc-1;j++){
    getline(mifile,valor,',');
    data[mi][j]=std::stod(valor);
    
  //std::cout<<data[mi][j]<<" ";
   }
    getline(mifile,valor,'\n');
    expected[mi]=std::stod(valor);
  }
  mifile.close();
}

void liberaData(int nr, int nc, double **data, double *expected){
  for(int i=0;i<nr;i++) free(data[i]);
  free(data);
  free(expected); 
}
