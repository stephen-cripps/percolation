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
#include <fstream>

using namespace std;

int main() {
	srand(time(NULL));//Seeds the random funcion
	int gSize = 1000; //size of grid
	int repetitions = 100; //Amount of times tested at each pValue
	PGrid grid(gSize); //initilaising grid;
	ofstream output; //creating CSV to plot in matlab
	output.open("percolation.csv");

	for (double pValue = 0.1; pValue < 1; pValue = pValue + 0.001) {

		int sCount = 0; //counts how many successful percolations for this pValue
		for (int i = 0; i < repetitions; i++) {

			//populating grid
			grid.populate(pValue);

			//setting  finish point
			grid.setFinish();

			//set start point, check if it connects
			if (grid.process()) {
				sCount++;
			}
		}
		cout << pValue << endl;
		output << pValue << "," << double(sCount) / repetitions << "\n";
	}
	return 0;
}
