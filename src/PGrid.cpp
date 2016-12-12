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

PGrid::PGrid(int gSize) {
	// TODO Auto-generated constructor stub
	m_gSize = gSize;
	grid = new PCell[gSize * gSize]; //set new grid


}

void PGrid::populate(double pValue){
	for (int i = 0; i < m_gSize * m_gSize; i++) {
			double rNum = ((double) rand() / (RAND_MAX));
			if (rNum < pValue) {
				grid[i].updateCell(1);
				map.push_back(i); //maps out live cells
			}
			else {
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

	//Process connection
	while (true) {
		grid[currentCell].updateCell(4); //ensure cell isn't rechecked, mark as 4 to differentiate from simply empty cells if printing
		//check neighbours +update cells accordingly, if it reaches end return true.


		if (checkNeighbours()) {
			map.clear();
			return 1;

		}
		//printGrid();
		if (!move()) { //move, if you can't it fails
			map.clear();
			return 0;
		}

	}
}

bool PGrid::checkNeighbours() {
	// cout << currentCell << ", ";
	possRout = 0; //Indicates if possible branches surround current cell, reset each check
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
			possRout = 1;
			break;
		case 2: //return as true therefore success
			return 1;
		case 3:
			possRout = 1;
			break;
		}
		i = currentCell + m_gSize;
	}
	//cout << currentCell << ", ";

	int cycle = 1; // Have to count if its the first or second iteration of the next loop to appropriately change boundary conditions
	i = currentCell - 1;
	for (int j = 1; j < 3; j++) { //for left and right
		if (i % m_gSize == 0 && cycle == 2) { //if currentCell+1 is multiple of 0 it would have crossed rhs boundary
			i = i - m_gSize;
		} else if ((i + 1) % m_gSize == 0 && cycle == 1) { //if currentCell-1 is 1 less than a multiple of gridsize it would have crossed LHS boundary
			i = i + m_gSize;
		}
		//cout << i << ", ";

		switch (grid[i].getState()) {
		case 1:
			grid[i].updateCell(3);
			possRout = 1;
			break;
		case 2:
			return 1;
		case 3:
			possRout = 1;
			break;
		}
		cycle++;
		i = currentCell + 1;
	}
	//cout << endl << endl;
	return 0;
}

bool PGrid::move() {
	int i = currentCell - m_gSize;
	if (possRout) {//if currentCell has possible branch scan neighbours for it and move
		for (int j = 1; j < 3; j++) { //up and down
			if (i < 0) { // periodic conditions
				i = i + (m_gSize * m_gSize);
			} else if (i > m_gSize * m_gSize) {
				i = i - (m_gSize * m_gSize);
			}
			if (grid[i].getState() == 3) {
				currentCell = i;
				return 1;
			}
			i = currentCell + m_gSize;
		}
		int cycle = 1; // Have to count if its the first or second iteration of the next loop to appropriately change boundary conditions
		i = currentCell - 1;
		for (int j = 1; j < 3; j++) { //for left and right
			if (i % m_gSize == 0 && cycle == 2) { //if currentCell+1 is multiple of 0 it would have crossed rhs boundary
				i = i - m_gSize;
			} else if ((i + 1) % m_gSize == 0 && cycle == 1) { //if currentCell-1 is 1 less than a multiple of gridsize it would have crossed LHS boundary
				i = i + m_gSize;
			}
			if (grid[i].getState() == 3) {
				currentCell = i;
				return 1;
			}
			cycle++;
			i = currentCell + 1;
		}
	} else {//if no possible rout scan entire grid for previously marked routs
		for (int i = 0; i < m_gSize * m_gSize; i++) {
			if (grid[i].getState() == 3) {
				currentCell = i;
				return 1;
			}
		}

	}
	return 0; //if no moves were found return as false
}

void PGrid::printGrid() {

	for (int i = 0; i < m_gSize; i++) {
		cout << i << ":  ";
		for (int j = 0; j < m_gSize; j++) {
			cout << grid[i * m_gSize + j].getState();
		}
		cout << endl;
	}
	cout << endl;

}
