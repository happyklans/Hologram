/*
Benjamin Stanton & Paul Allen
9/3/2017
MSU Senior project
take some imput, convert from vector notation to cylindrical coordinates then map to a 16x16 array and then write to a file for hardware streaming
*/

#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

const int ON = 255; //defines the states of the hardware 
const int OFF = 0; //			"
const int ATTRIBUTES = 4; // number of attributes for every cell in the abstraction space (status, red, green, blue)
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
	//vector<int> active_slice_list; // list of slices that are not blank
	vector<int> start; // start point of a vector
	vector<int> end; // endpoint of a vector
	ofstream bitmap("bitmap.csv");
	double rho = 0;  //cylindrical coordinates for the user entered vector
	double theta = 0;	//				"
	int zeta = 0;	//					"
	double n_index = 0; // used to populate the active slice list
	int xprime = 0; //rectangular coordinates of the user entered vector
	int yprime = 0; //					"
	int zprime = 0; //					"
	int xdimension = 0; // the dimensions of the FPGA display bitmap
	int ydimension = 0; //				"
	int zdimension = 0; //				"
	double slope = 0; // slope of the vector line in the 2d layer of the bitmap
	//int num_vectors; // number of active vectors
	int temp = 0; // used to populate start and end point vectors
	unsigned char a = 0;
	//populating start and end point vectors
	for (int i = 0; i < DIMENSIONS; i++)
	{
		cout << "Enter your starting " << static_cast<char>(DIMENSION_VARIABLES+i) << " point: ";
		cin >> temp;
		start.push_back(temp);
		cin.ignore(1);
	}

	for (int i = 0; i < DIMENSIONS; i++)
	{
		cout << "Enter your ending " << static_cast<char>(DIMENSION_VARIABLES+i) << " point: ";
		cin >> temp;
		end.push_back(temp);
		cin.ignore(1);
	}
	//start and end point vectors populated

	// create slices bitmap as a multidimensional array of user entered dimensions 

	cout << "Enter the dimensions of your abstract space (z -> Enter -> y -> Enter -> x -> Enter): ";
	cin >> zdimension;
	cin.ignore(1);
	cin >> ydimension;
	cin.ignore(1);
	cin >> xdimension;

	for (int n = 0; n < zdimension; n++)
	{
		slices.push_back(constructor_one);
		
		for (int row = 0; row < ydimension; row++)
		{
			slices[n].push_back(constructor_two);
			
			for (int col = 0; col < xdimension; col++)
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

	//defining the vector in rectangular coordinates
	xprime = end[0] - start[0];
	yprime = end[1] - start[1];
	zprime = end[2] - start[2];

	//convert from rectangular to cylindrical coordinates
	rho = sqrt((xprime*xprime) + (yprime*yprime));
	theta = atan(yprime / xprime);
	zeta = zprime;

	/*cout << rho << endl << theta << endl << zeta << endl;
	*/
	
	// populate active slice index list
	//n_index is the slice that the vector will sit on, resolving one dimension of the matrix
	//thus, only a 2d vector must be drawn on the slices themselves
	n_index = theta / SLICE_WIDTH;
	n_index = round(n_index);
	n_index -= 1;
	n_index = static_cast<int>(n_index);
	//active slice index set
	
	//migrate the origin to the center of the FPGA display
	start[0] += 8;
	start[1] += 8;

	end[0] += 8;
	end[0] += 8;
	
	//draw the user entered vector on the appropriate slice
	if (yprime/xprime >= 1)
	{
		if(y)
	}
	else 
	{

	}
	
	for (int row = 0; row < 16; row++)
	{
		for (int col = 0; col++)
		{

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