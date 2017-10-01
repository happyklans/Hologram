#include "User_Vector.h"

void new_vector(std::vector<std::vector<double>>&user_vector_info)//constructs the vector
{	
	std::vector<double> beta_constructor_one; //used for constructing the user_vector_info vector
								  
	user_vector_info.push_back(beta_constructor_one);//construct a container for the user vector

	return;
}

double red_value(int color_choice) //returns the red value of the color choice
{
	double red = 0;

	switch (color_choice)
	{
	case 1:
		red = ON;
		
		break;

	case 2:
		red = OFF;
		
		break;

	case 3:
		red = OFF;
		
		break;

	case 4:
		red = ON;
		
		break;

	case 5:
		red = OFF;
		
		break;

	case 6:
		red = ON;
		
		break;

	case 7:
		red = ON;
		
		break;

	default:
		red = ON;
		
		break;
	}
	
	return red;
}

double green_value(int color_choice) //returns the green value of the color choice
{
	double green = 0;

	switch (color_choice)
	{
	case 1:
		green = ON;

		break;

	case 2:
		green = OFF;

		break;

	case 3:
		green = OFF;

		break;

	case 4:
		green = ON;

		break;

	case 5:
		green = OFF;

		break;

	case 6:
		green = ON;

		break;

	case 7:
		green = ON;

		break;

	default:
		green = ON;

		break;
	}

	return green;
}

double blue_value(int color_choice) //returns the blue value of the color choice
{
	double blue = 0;

	switch (color_choice)
	{
	case 1:
		blue = ON;

		break;

	case 2:
		blue = OFF;

		break;

	case 3:
		blue = OFF;

		break;

	case 4:
		blue = ON;

		break;

	case 5:
		blue = OFF;

		break;

	case 6:
		blue = ON;

		break;

	case 7:
		blue = ON;

		break;

	default:
		blue = ON;

		break;
	}

	return blue;
}

double calc_rho(double xprime, double yprime, double zprime) //returns the value of the spherical component rho of the rectangular user vector
{
	double rho = 0;

	rho = std::sqrt((xprime*xprime) + (yprime*yprime) + (zprime*zprime));

	return rho;
}

//Pre-condition: xprime cannot = 0 and yprime = 0
double calc_theta(double yprime, double xprime) //returns the value of the spherical component theta of the rectangular user vector
{
	double theta = 0;

	theta = atan(yprime / xprime);

	return theta;
}

double calc_phi(double zprime, double rho) //returns the value of the spherical component phi of the rectangular user vector
{
	double phi = 0;
	
	phi = acos(zprime / rho);

	return phi;
}
