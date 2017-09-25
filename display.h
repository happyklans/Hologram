#ifndef DISPLAY_H
#define DISPLAY_H

#define OFF 0 //defines the states of the hardware 
#define ATTRIBUTES 6 // number of attributes for every cell in the abstraction space (status, red, green, blue)
#define SLICE_WIDTH .1963495408 // the slice width in radians

#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>



void construct(std::vector<std::vector<std::vector<std::vector<int> > > > &display_vector, int z, int x, int y); //constructs vector array

int calc_n(double theta); //returns slice number from 0-31

double x_calc(double rho, double phi); //returns x value of vector on abstract 2D plane 

double y_calc(double rho, double phi); //returns y value of vector on abstract 2D plane 

#endif
