/*
Benjamin Stanton & Paul Allen
9/3/2017
MSU Senior project
take some input, convert from vector notation to cylindrical coordinates then map to a 16x16 array and then write to a file for hardware streaming
*/

#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include "User_Vector.h"
#include "display.h"
using namespace std;

const int COLOR_ATTRIBUTES = 3; //number of color attributes
const int MAX_SCALE = 9; //maximum length for any vector to be displayed
const int DIMENSIONS = 3; // dimension space that the vectors occupy
const int DIMENSION_VARIABLES = 120; // letter variables that describe spacial dimensions

int main()
{
	// variables
	vector< vector< vector< vector< int > > > > slices; // abstratction of the FPGA display bitmap
	
	vector<int> start; // start point of a vector
	
	vector<int> end; // endpoint of a vector

	vector<vector<double>> user_vector_info; //attributes of the user entered vector(s)

	ofstream bitmap;
	
	double xprime = 0; //rectangular coordinates of the user entered vector
	
	double yprime = 0; //					"
	
	double zprime = 0; //					"
	
	int xdimension = 0; // the dimensions of the FPGA display bitmap
	
	int ydimension = 0; //				"
	
	int zdimension = 0; //				"
	
	double slope = 0; // slope of the vector line in the 2d layer of the bitmap
	
	int num_vectors; // number of active vectors

	int n_index = 0; //numerical location of the slice that any particular vector sits on
	
	int temp = 0; // used to populate start and end point vectors

	double double_temp = 0; //used for render scaling and checking the integral nature of slope values  
	
	int color = 0; // used to get the color preference for the input vector
	
					 
	// create slices vector as a multidimensional array of user entered dimensions
	cout << "Enter the dimensions of your abstract space (z -> Enter -> x -> Enter -> y -> Enter): ";
	cin >> zdimension;
	cin.ignore(1);
	cin >> xdimension;
	cin.ignore(1);
	cin >> ydimension;

	//construct the matrix itself
	construct(slices, zdimension, xdimension, ydimension);

	for (int i = 0; i < DIMENSIONS; i++)
	{
		start.push_back(OFF);
		end.push_back(OFF);
	}

	
	//query user for total number of vectors they want to enter
	cout << "Enter the number of vectors to be displayed: ";
	cin >> num_vectors;

	//populate user_entered_vectors vector
	for (int i = 0; i < num_vectors; i++)
	{
		
		
		//construct a container for the user vector
		new_vector(user_vector_info);

		//populating start and end point vectors
		for (int i = 0; i < DIMENSIONS; i++)
		{
			cout << "Enter your starting " << static_cast<char>(DIMENSION_VARIABLES + i) << " point: ";
			cin >> temp;
			start[i] = temp;
			cin.ignore(1);
		}

		for (int i = 0; i < DIMENSIONS; i++)
		{
			cout << "Enter your ending " << static_cast<char>(DIMENSION_VARIABLES + i) << " point: ";
			cin >> temp;
			end[i] = temp;
			cin.ignore(1);
		}
		//start and end point vectors populated

		//get color preference from the user
		cout << "Enter the number of your color preference:" << endl <<
			"1) red		\n"
			"2) green	\n"
			"3) blue	\n"
			"4) yellow	\n"
			"5) cyan	\n"
			"6) magenta \n"
			"7) white   \n";
		cin >> color;

		

		//defining the vector in rectangular coordinates
		xprime = end[0] - start[0];
		
		yprime = end[1] - start[1];
		
		zprime = end[2] - start[2];


		//add attributes to the vector index
		//spherical coordinates for the user entered vector
		user_vector_info[i].push_back(calc_rho(xprime, yprime, zprime));
		
		user_vector_info[i].push_back(calc_theta(yprime, xprime));
		
		user_vector_info[i].push_back(calc_phi(zprime, calc_rho(xprime, yprime, zprime)));

		//12 bit color variables
		
		user_vector_info[i].push_back(red_value(color));
		
		user_vector_info[i].push_back(green_value(color));
		
		user_vector_info[i].push_back(blue_value(color));
	}
	
	//scaling vectors from the user vector list
	double_temp = user_vector_info[0][0]; // in this context, temp is the max value of all the rho values of the vectors

								   //finding the max rho value
	for (int i = 0; i < (user_vector_info.size() - 1); i++)
	{

		if (user_vector_info[i + 1][0] > temp)
			double_temp = user_vector_info[i + 1][0];
	}

	//scale all values to proper relative size to fit the display device (max length of 7)
	for (int i = 0; i < user_vector_info.size(); i++)
	{
		user_vector_info[i][0] = round((MAX_SCALE - ((double_temp - user_vector_info[i][0]) / user_vector_info[i][0])*MAX_SCALE));
	}

	
	
	
	//draw the user entered vector on the appropriate slice
	for (int vector_id = 0; vector_id < user_vector_info.size(); vector_id++)
	{
		n_index = calc_n(user_vector_info[vector_id][1]);

		//slope of an abstract 2d vector that is identical to the 3d user inputted vector when the slice upon which the 
		//user inputted vector sits is viewed head on
		slope = round(y_calc(user_vector_info[vector_id][0], user_vector_info[vector_id][2]) / round(x_calc(user_vector_info[vector_id][0], user_vector_info[vector_id][2])));
		// in plain terms, slope = y/x, and in this case, y = rho*sin(phi), and x = rho*cos(phi)
		//for 
		if (slope >= 1)
		{

			//for integer slopes
			if (modf(slope, &double_temp) == 0.0)
			{
				//in plain terms, i < magnitude of the x portion of the vector
				//see above explaintion of mathmatical background for this claim
				for (int i = 0; i < round(x_calc(user_vector_info[vector_id][0], (user_vector_info[vector_id][2]))); i++)
				{
					for (int j = (slope*i); j < round(slope*(i + 1)); j++)
					{
						for (int k = 0; k < COLOR_ATTRIBUTES; k++)
						{
							slices[n_index][i][j+6][k] = user_vector_info[vector_id][3 + k];
						}
					}
				}
			}
			//for non-integer slopes greater than 1
			else
			{
				for (int i = 0, j = 0; i < round(x_calc(user_vector_info[vector_id][0], (user_vector_info[vector_id][2]))); i++, j--)
				{
					
					while (j < (slope*(i + 1)))
					{
						for (int k = 0; k < COLOR_ATTRIBUTES; k++)
						{
							slices[n_index][i][j+6][k] = user_vector_info[vector_id][3 + k];
						}

						j++;
					}
					
				}
			}
		}
		else if (slope < 1)
		{
			//for slopes that can be expressed as 1/n where n is some integer greater than 1
			if (modf((1 / slope), &double_temp) == 0.0)
			{
				//in plain terms, i < magnitude of the x portion of the vector
				//see above explaintion of mathmatical background for this claim
				for (int i = 0; i < round(y_calc(user_vector_info[vector_id][0], (user_vector_info[vector_id][2]))); i++)
				{
					for (int j = ((1 / slope)*i); j < round((1 / slope)*(i + 1)); j++)
					{
						for (int k = 0; k < COLOR_ATTRIBUTES; k++)
						{
							slices[n_index][j][i+6][k] = user_vector_info[vector_id][3 + k];
						}
					}
				}
			}
			//for all non-integer slopes less than 1
			else
			{
				for (int i = 0, j = 0; i < (y_calc(user_vector_info[vector_id][0], (user_vector_info[vector_id][2]))); i++, j--) //due to the way that rho and phi (the variables 
				{																									//being used) are calculated, the product of this 
					while (j < ((1 / slope)*(i + 1)))																		//operation will always yield an integer
					{																								// removing the need to round it
						for (int k = 0; k < COLOR_ATTRIBUTES; k++)
						{
							slices[n_index][j][i+6][k] = user_vector_info[vector_id][3 + k];
						}

						j++;
					}

					//increment y 
					

				}
			}
		}

	}
	//DELETE THIS IS JUST TO TEST NOT ACTUAL CODE GET OFF MY CASE

	bitmap.open("bitmap.txt", ios::in);

	for (int n = 0; n < zdimension; n++)
	{
		

		for (int col = 0; col < ydimension; col++)
		{
			

			for (int row = 0; row < xdimension; row++)
			{
				
				for (int i = 0; i < 1; i++)
				{
					bitmap << slices[n][row][col][0] << "\t";
				}

				
			}
			bitmap << endl;
		}

		bitmap << endl;
	}
	bitmap.close();
	

	return 0;
}