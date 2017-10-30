#ifndef LDIJKSTRA_H
#define LDIJKSTRA_H
#include <iostream>
#include <queue>
#include <cstdlib>
#include <cairo/cairo.h>
#include <vector>
#include <map>
void creaGrafo(int **G, int n);
int algDijkstra(int **G, int n, int pi, int pf);
#endif 
