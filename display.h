#ifndef DISPLAY_H
#define DISPLAY_H

#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>

void construct(std::vector<std::vector<std::vector<std::vector<int> > > > &display_vector, int z, int x, int y, int ATTRIBUTES, int OFF); //constructs vector array

int calc_n(double theta, double SLICE_WIDTH); //returns slice number from 0-31

double x_calc(double rho, double phi); //returns x value of vector on abstract 2D plane 

double y_calc(double rho, double phi); //returns y value of vector on abstract 2D plane 

#endif
