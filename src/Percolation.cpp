//============================================================================
// Name        : Percolation.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "PGrid.h"
#include<time.h>
#include <cstdlib>

using namespace std;

int main() {
	srand(time(NULL));//Seeds the random funcion
	int gSize = 10; //size of grid
	double pValue = 0.5; //probability of cell being populated

	//initilaising grid;
	PGrid grid(gSize, pValue);

	//setting  finish point
	grid.setFinish();

	for (int i = 0; i<gSize ; i++){
		for ( int j = 0; j<gSize ; j++){


			cout << grid.getCell(i*gSize+j);
		}
		cout << endl;
	}

	return 0;
}
