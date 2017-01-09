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
#include <fstream>
#include <sstream>

using namespace std;

PGrid::PGrid(int gSize) {
	// TODO Auto-generated constructor stub
	m_gSize = gSize;
	grid = new PCell[gSize * gSize]; //set new grid


}

void PGrid::populate(double pValue) {
	for (int i = 0; i < m_gSize * m_gSize; i++) {
		double rNum = ((double) rand() / (RAND_MAX));
		if (rNum < pValue) {
			grid[i].updateCell(1);
			map.push_back(i); //maps out live cells
		} else {
			grid[i].updateCell(0);
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
	int end = map.at(rand() % (map.size())); // picks random live cell from map
	grid[end].updateCell(2);
}

int PGrid::getCell(int i) {
	return grid[i].getState();

}

bool PGrid::process() {

	currentCell = map.at(rand() % (map.size())); //set start point from random live cell on map

//	iterations = 0;
	//Process connection
	while (true) {
		grid[currentCell].updateCell(4); //ensure cell isn't rechecked, mark as 4 to differentiate from simply empty cells if printing
		//check neighbours +update cells accordingly, if it reaches end return true.


		if (checkNeighbours()) {
			map.clear();
			return 1;

		}


		if (!move()) { //move, if you can't it fails
			map.clear();
			return 0;

		}
//		iterations++;
//		if (iterations % 10000 == 0 || iterations% 10000 == 1 || iterations% 10000 == 2){
//			expGrid();
//		}

	}
}

bool PGrid::checkNeighbours() {
	nextPicked = 0; //Indicates if next cell to move to has been picked yet

	//----------------for above and below---------------------
	//periodic boundaries
	int i = currentCell - m_gSize;
	for (int j = 1; j < 3; j++) { //for above and below
		if (i < 0) {
			i = i + (m_gSize * m_gSize);
		} else if (i > m_gSize * m_gSize) {
			i = i - (m_gSize * m_gSize);
		}
		//cout << i << ", ";
		switch (grid[i].getState()) {
		case 1: ///Mark and indicate the current cell has a branch
			grid[i].updateCell(3);
			if (!nextPicked) { //if the next cell hasn't been picked this is the next cell
				nextCell = i;
				nextPicked = 1;

			}
			break;
		case 2: //return as true therefore success
			return 1;
		case 3:
			if (!nextPicked) {
				nextCell = i;
				nextPicked = 1;
			}
			break;
		}
		i = currentCell + m_gSize;
	}

	//--------for left and right-----------------
	int cycle = 1; // Have to count if its the first or second iteration of the next loop to appropriately change boundary conditions
	i = currentCell - 1;
	for (int j = 1; j < 3; j++) {
		if (i % m_gSize == 0 && cycle == 2) { //if currentCell+1 is multiple of 0 it would have crossed rhs boundary
			i = i - m_gSize;
		} else if ((i + 1) % m_gSize == 0 && cycle == 1) { //if currentCell-1 is 1 less than a multiple of gridsize it would have crossed LHS boundary
			i = i + m_gSize;
		}

		switch (grid[i].getState()) {
		case 1:
			grid[i].updateCell(3);
			if (!nextPicked) {
				nextCell = i;
				nextPicked = 1;
			}
			break;
		case 2:
			return 1;
		case 3:
			if (!nextPicked) {
				nextCell = i;
				nextPicked = 1;
			}
			break;
		}
		cycle++;
		i = currentCell + 1;
	}
	//cout << endl << endl;
	return 0;
}

bool PGrid::move() {
	if (nextPicked) {
		currentCell = nextCell;
		return 1;
	} else {//if no possible rout scan all possible routs for unexplored ones (3's which havent been tirned into fours)
		for (int i = 0; i < map.size(); i++) {
			if (grid[map.at(i)].getState() == 3) { //if the mapped position in the grid is still 3
				currentCell = map.at(i);
				return 1;
			}
		}

	}
	return 0; //if no moves were found return as false
}

void PGrid::printGrid() {

	for (int i = 0; i < m_gSize; i++) {

		for (int j = 0; j < m_gSize; j++) {
			cout << grid[i * m_gSize + j].getState();
		}
		cout << endl;
	}
	cout << endl;

}

void PGrid::expGrid() {

	 ostringstream fn;
	 fn << "file" << iterations << ".csv";
	 ofstream gridout; //creating CSV to plot in matlab
	 gridout.open( fn.str().c_str());
    	for (int i = 0; i < m_gSize; i++) {

		for (int j = 0; j < m_gSize; j++) {
			gridout << grid[i * m_gSize + j].getState()<< ",";
		}
		gridout << "\n";
	}
	cout<< "gridout" << iterations << endl;
	gridout.close();
}
