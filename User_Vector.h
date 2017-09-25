#ifndef USER_VECTOR_H

#define USER_VECTOR_H

#define ON 255 //used to define the color states of the RGB vector components

#define OFF 0 //used to define the color states of the RGB vector components


#include <vector>

#include <iostream>

#include <string>

#include <math.h>

void new_vector(std::vector<std::vector<double>>&user_vector_info);//constructs the vector

double red_value(int color_choice); //returns the red value of the color choice

double green_value(int color_choice); //returns the green value of the color choice

double blue_value(int color_choice); //returns the blue value of the color choice

double calc_rho(double xprime, double yprime, double zprime); //returns the value of the spherical component rho of the rectangular user vector

double calc_theta(double yprime, double xprime); //returns the value of the spherical component theta of the rectangular user vector

double calc_phi(double zprime, double phi); //returns the value of the spherical component phi of the rectangular user vector


#endif 

