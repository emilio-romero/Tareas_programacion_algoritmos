#ifndef LDIJKSTRA_H
#define LDIJKSTRA_H
#include <iostream>
#include <queue>
#include <cstdlib>
#include <cairo/cairo.h>
#include <cairo/cairo-pdf.h>
#include <vector>
#include <map>
#include <cmath>
#include <cstdio>
//#define M_PI 3.14159265358979323846264338327950288
void creaGrafo(int **G, int n,int pi, int pf);
int algDijkstra(int **G, int n, int pi, int pf);
int drawGraphPng(int **G, int n, int tipo,std::vector<int> mruta);
void creaNodo(cairo_t *cr,int x0,int y0,double *color);
void creaLinea(cairo_t *cr,int x1,int y1, int x2, int y2);
void dibujaNodos(cairo_t *cr, int n,double *color);
void dibujaAristas(cairo_t *cr,int **G , int n);
double calculaPendiente(int x1, int y1, int x2, int y2);
void dibujaRuta(cairo_t *cr, int n, std::vector<int> mruta, double *color);
void dibujaRutaA(cairo_t *cr, int n, std::vector<int> mruta, double *color);
int drawGraphPdf(int **G, int n, int tipo,std::vector<int> mruta);
#endif 
