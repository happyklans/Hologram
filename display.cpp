#include "display.h"

void construct(std::vector<std::vector<std::vector<std::vector<int> > > > &display_vector, int z, int x, int y, int ATTRIBUTES, int OFF) //constructs vector array
{
	std::vector< std::vector< std::vector< int > > > constructor_one; //used for constructing the matrix

	std::vector< std::vector< int > >  constructor_two; //				"

	std::vector< int > constructor_three; //							"

	//construct the matrix itself
	for (int n = 0; n < z; n++)
	{
		display_vector.push_back(constructor_one);

		for (int row = 0; row < x; row++)
		{
			display_vector[n].push_back(constructor_two);

			for (int col = 0; col < y; col++)
			{
				display_vector[n][row].push_back(constructor_three);

				for (int i = 0; i < ATTRIBUTES; i++)
				{
					display_vector[n][row][col].push_back(OFF);
				}
			}
		}
	}
	return;
}

int calc_n(double theta, double SLICE_WIDTH) //returns slice number from 0-31
{
	int n_index = 0; 
	n_index = theta / SLICE_WIDTH; 
	n_index = round(n_index); //round n_index to the nearest whole number
	n_index = static_cast<int>(n_index); //convert from double to int
	return n_index;
}

double x_calc(double rho, double phi) //returns x value of vector on abstract 2D plane 
{
	int x;
	x = round(rho * sin(phi));
	return x;
}

double y_calc(double rho, double phi) //returns y value of vector on abstract 2D plane 
{
	int y;
	y = round(rho * cos(phi));
	return y;
}