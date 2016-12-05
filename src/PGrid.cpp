/*
 * PGrid.cpp
 *
 *  Created on: 4 Dec 2016
 *      Author: user
 */

#include "PGrid.h"
#include <cstdlib>
#include <iostream>
#include "PGrid.h"
#include<time.h>
#include <cstdlib>

using namespace std;

PGrid::PGrid(int gSize, double pValue) {
	// TODO Auto-generated constructor stub
	m_gSize = gSize;
	grid = new PCell[gSize * gSize]; //set new grid
	for (int i = 0; i < m_gSize * m_gSize; i++) {
		double rNum = ((double) rand() / (RAND_MAX));
		if (rNum < pValue) {
			grid[i].updateCell(1);
		}

	}
}

PGrid::~PGrid() {
	// TODO Auto-generated destructor stub
	delete[] grid;
}
void PGrid::init() {

}
void PGrid::setFinish() {
	bool finishSet = 0;
	while (!finishSet) {
		int end = rand() % (m_gSize * m_gSize);
		if (grid[end].getState() == 1) { //if cell is active set as finish point
			grid[end].updateCell(2);
			finishSet = 1;
		}
	}
}
int PGrid::getCell(int i){

	return grid[i].getState();
}
