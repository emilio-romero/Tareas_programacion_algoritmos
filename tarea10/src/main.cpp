#include <iostream> 
#include "redneuronal.hpp"
using namespace std;
int main(){
srand(time(NULL));
int ndata=8; 
int nneuronas=5;
double expval=1.0;
double learn_rate=0.1, error;
double *mydata=(double*)malloc(8*sizeof(double));
for(int i=0;i<8;i++){
  mydata[i]=i+1;
}
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
Neurona *mineurona=new Neurona[nneuronas];
Neurona salida;
double *neurondata=(double*)malloc(nneuronas*sizeof(double));
/*Proceso entero de lectura de datos*/
/*obtencion de valores de entrada a la neurona y activacion*/
sini.salida(mydata);
double *myptr=sini.getSalida();
for(int i=0;i<5;i++){
  mineurona[i].setValor(myptr[i]);
  neurondata[i]=mineurona[i].getValor_activado();
}
sino.salida(neurondata);
double *mysld=sino.getSalida();
salida.setValor(mysld[0]);
cout<<salida.getValor_activado()<<endl;
error=expval-salida.getValor_activado();
double **coni, **cono;
coni=sini.getConexiones();
cono=sino.getConexiones();
//learn_rate
sini.actualizaConexiones(learn_rate,error,mydata);
//for(int i=0;i<nneuronas;i++) 
for(int i=0;i<nneuronas;i++) mineurona[i].actualizaBias(learn_rate,error);
sino.actualizaConexiones(learn_rate,error,neurondata);
salida.actualizaBias(learn_rate,error);

/*Fin del proceso*/
nofuncion();

delete [] mineurona;
free(mydata);
free(neurondata);
cout<<"Su programa ha terminado\n";
return 0;}
