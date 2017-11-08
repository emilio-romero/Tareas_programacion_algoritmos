#include <iostream>
#include <string>
#include "redneuronal.hpp"
using namespace std;
int main(){
srand(time(NULL));
int ndata=8; 
int nneuronas=5;
double learn_rate=0.1, error;
/*Lectura de datos*/
double *expval=(double*)malloc(768*sizeof(double));
double **mydata=(double**)malloc(768*sizeof(double**));
for(int i=0;i<768;i++) mydata[i]=(double*)malloc(ndata*sizeof(double));
readData(768,ndata+1,"dataset.txt",mydata,expval);
//Fin de lectura =======================
/*Declaracion de la arquitectura*/
/*Se declaran las sinapsis de entrada y de salida*/
   int **arqi=(int**)malloc(nneuronas*sizeof(int*));
    for(int i=0;i<nneuronas;i++) {arqi[i]=(int*)malloc(ndata*sizeof(int));
      for(int j=0;j<ndata;j++) arqi[i][j]=1;
    }
    int **arqo=(int**)malloc(1*sizeof(int*));
    for(int i=0;i<1;i++) {arqo[i]=(int*)malloc(ndata*sizeof(int));
      for(int j=0;j<ndata;j++) arqo[i][j]=1;
    }
Sinapsis sini=Sinapsis(ndata,nneuronas);
Sinapsis sino=Sinapsis(nneuronas,1);
sini.llena_conexiones(arqi);
sino.llena_conexiones(arqo);
//Fin de arquitectura==============================
Neurona *mineurona=new Neurona[nneuronas];
Neurona salida;
double *neurondata=(double*)malloc(nneuronas*sizeof(double));
/*obtencion de valores de entrada a la neurona y activacion*/
for(int epoch=0;epoch<768;epoch++){
sini.salida(mydata[epoch]);
double *myptr=sini.getSalida();
for(int i=0;i<5;i++){
  mineurona[i].setValor(myptr[i]);
  neurondata[i]=mineurona[i].getValor_activado();
}
sino.salida(neurondata);
double *mysld=sino.getSalida();
salida.setValor(mysld[0]);
cout<<"Valor activado: "<<salida.getValor_activado()<<" | ";
error=expval[epoch]-salida.getValor_activado();
double **coni, **cono;
coni=sini.getConexiones();
cono=sino.getConexiones();
//learn_rate
/*Correcion del error (?)*/
sini.actualizaConexiones(learn_rate,error,mydata[epoch]);
for(int i=0;i<nneuronas;i++) mineurona[i].actualizaBias(learn_rate,error);
sino.actualizaConexiones(learn_rate,error,neurondata);
salida.actualizaBias(learn_rate,error);
// Fin de correccion =======================
}
/*Fin del proceso*/
cout<<endl;
delete [] mineurona;
free(neurondata);
liberaData(768,9,mydata,expval);
cout<<"Su programa ha terminado\n";
return 0;}
