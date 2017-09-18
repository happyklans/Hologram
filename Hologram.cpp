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
using namespace std;

const int ON = 255; //defines the states of the hardware 
const int OFF = 0; //			"
const int ATTRIBUTES = 3; // number of attributes for every cell in the abstraction space (status, red, green, blue)
const int MAX_SCALE = 7; //maximum length for any vector to be displayed
const int DIMENSIONS = 3; // dimension space that the vectors occupy
const int DIMENSION_VARIABLES = 120; // letter variables that describe spacial dimensions
const double SLICE_WIDTH = .1963495408; // the slice width in radians

int main()
{
	// variables
	vector< vector< vector< vector< int > > > > slices; // abstratction of the FPGA display bitmap
	
	vector< vector< vector< int > > > constructor_one; //used for constructing the matrix
	
	vector< vector< int > >  constructor_two; //				"
	
	vector< int > constructor_three; //							"
	
	vector<int> start; // start point of a vector
	
	vector<int> end; // endpoint of a vector

	vector<vector<double>> user_vector_info; //attributes of the user entered vector(s)
	
	ofstream bitmap("bitmap.csv");
	
	double rho = 0;  //cylindrical coordinates for the user entered vector
	
	double theta = 0;	//				"
	
	double phi = 0; //once the vector has been assigned to a slice, this angle is used to transpose the 3d vector to a 2d space
	
	int red = 0; //12 bit color variable

	int green = 0;//		"

	int blue = 0; //		"
	
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
	cout << "Enter the dimensions of your abstract space (z -> Enter -> y -> Enter -> x -> Enter): ";
	cin >> zdimension;
	cin.ignore(1);
	cin >> ydimension;
	cin.ignore(1);
	cin >> xdimension;

	//construct the matrix itself
	for (int n = 0; n < zdimension; n++)
	{
		slices.push_back(constructor_one);

		for (int row = 0; row < xdimension; row++)
		{
			slices[n].push_back(constructor_two);

			for (int col = 0; col < ydimension; col++)
			{
				slices[n][row].push_back(constructor_three);

				for (int i = 0; i < ATTRIBUTES; i++)
				{
					slices[n][row][col].push_back(OFF);
				}
			}
		}
	}

	//created slices
	/*cout << endl << "starting point = (";

	for (int i = 0; i < DIMENSIONS; i++)
	{
	cout << start[i] << ',';
	}
	cout << ')' << endl;

	cout  << "ending point = (";

	for (int i = 0; i < DIMENSIONS; i++)
	{
	cout << end[i] << ',';
	}
	cout << ')' << endl;*/
	//query user for total number of vectors they want to enter
	cout << "Enter the number of vectors to be displayed: ";
	cin >> num_vectors;

	//populate user_entered_vectors vector
	for (int i = 0; i < num_vectors; i++)
	{
		//populating start and end point vectors
		for (int i = 0; i < DIMENSIONS; i++)
		{
			cout << "Enter your starting " << static_cast<char>(DIMENSION_VARIABLES + i) << " point: ";
			cin >> temp;
			start.push_back(temp);
			cin.ignore(1);
		}

		for (int i = 0; i < DIMENSIONS; i++)
		{
			cout << "Enter your ending " << static_cast<char>(DIMENSION_VARIABLES + i) << " point: ";
			cin >> temp;
			end.push_back(temp);
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

		//translating color preference to numerical values
		switch (color)
		{
		case 1:
		{
			red = ON;
			blue, green = OFF;
			break;
		}
		case 2:
		{
			green = ON;
			red, blue = OFF;
			break;
		}
		case 3:
		{
			blue = ON;
			red, green = OFF;
			break;
		}
		case 4:
		{
			red, green = ON;
			blue = OFF;
			break;
		}
		case 5:
		{
			green, blue = ON;
			red = OFF;
			break;
		}
		case 6:
		{
			red, blue = ON;
			green = OFF;
			break;
		}
		case 7:
		{
			red, green, blue = ON;
			break;
		}
		default:
		{
			red, green, blue = ON;
			break;
		}	
		}
		//defining the vector in rectangular coordinates
		xprime = end[0] - start[0];
		yprime = end[1] - start[1];
		zprime = end[2] - start[2];

		//convert from rectangular to cylindrical coordinates
		rho = sqrt((xprime*xprime) + (yprime*yprime));
		
		theta = atan(yprime / xprime);
		
		phi = asin(zprime / rho);

		temp = user_vector_info[0][0]; // in this context, temp is the max value of all the rho values of the vectors
		
		//finding the max rho value
		for (int i = 0; i < (user_vector_info.size() - 1); i++)
		{

			if (user_vector_info[i + 1][0] > temp)
				temp = user_vector_info[i + 1][0];
		}

		//scale all values to proper relative size to fit the display device (max length of 7)
		for (int i = 0; i < user_vector_info.size(); i++)
		{
			user_vector_info[i][0] = round((MAX_SCALE - ((temp - user_vector_info[i][0]) / user_vector_info[i][0])*MAX_SCALE));
		}

		//add attributes to the vector index
		user_vector_info[i].push_back(rho);
		user_vector_info[i].push_back(theta);
		user_vector_info[i].push_back(phi);
		user_vector_info[i].push_back(red);
		user_vector_info[i].push_back(green);
		user_vector_info[i].push_back(blue);
	}
	

	
	
	
	//draw the user entered vector on the appropriate slice
	for (int vector_id = 0; vector_id < user_vector_info.size(); vector_id++)
	{
		n_index = theta / SLICE_WIDTH;
		n_index = round(n_index);
		n_index -= 1;
		n_index = static_cast<int>(n_index);
		
		//slope of an abstract 2d vector that is identical to the 3d user inputted vector when the slice upon which the 
		//user inputted vector sits is viewed head on
		slope = user_vector_info[vector_id][0] * sin(user_vector_info[vector_id][2]) / user_vector_info[vector_id][0] * cos(user_vector_info[vector_id][2]);
		// in plain terms, slope = y/x, and in this case, y = rho*sin(phi), and x = rho*cos(phi)
		//for 
		if (slope >= 1)
		{

			//for integer slopes
			if (modf(slope, &double_temp) == 0.0)
			{
				//in plain terms, i < magnitude of the x portion of the vector
				//see above explaintion of mathmatical background for this claim
				for (int i = 0; i < round(user_vector_info[vector_id][0] * cos(user_vector_info[vector_id][2])); i++)
				{ 
					for (int j = (slope*i); j < round(user_vector_info[vector_id][0] * sin(user_vector_info[vector_id][2])); j++)
					{
						for (int k = 0; k < ATTRIBUTES; k++)
						{
							slices[n_index][i][j][k] = user_vector_info[vector_id][3 + k];
						}
					}
				}
			}
			//for non-integer slopes greter than 1
			else
			{

			}
		}
		else if (slope < 1)
		{
			//for slopes that can be expressed as 1/n where n is some integer greater than 1
			if (modf((1/slope), &double_temp) == 0.0)
			{
				//in plain terms, i < magnitude of the x portion of the vector
				//see above explaintion of mathmatical background for this claim
				for (int i = 0; i < round(user_vector_info[vector_id][0] * sin(user_vector_info[vector_id][2])); i++)
				{
					for (int j = ((1/slope)*i); j < round(user_vector_info[vector_id][0] * cos(user_vector_info[vector_id][2])); j++)
					{
						for (int k = 0; k < ATTRIBUTES; k++)
						{
							slices[n_index][j][i][k] = user_vector_info[vector_id][3 + k];
						}
					}
				}
			}
			//for all other slopes less than 1
			else
			{
			
			}
		}

		for (int row = 0; row < 16; row++)
		{
			/*for (int col = 0; col++)
			{

			}*/
		}
	}
	/*for (int n = 0; n < zdimension; n++)
	{
		for (int row = 0; row < ydimension; row++)
		{
			for (int col = 0; col < xdimension; col++)
			{
				for (int i = 0; i < ATTRIBUTES; i++)
				{
					cin.peek();

					cout << "hi";

					slices[n][row][col].push_back(OFF);
				}
			}
		}
	}*/

	return 0;
}