/*
 * PCell.cpp
 *
 *  Created on: 4 Dec 2016
 *      Author: user
 */

#include "PCell.h"

PCell::PCell(): state(0) {
	// TODO Auto-generated constructor stub

}

PCell::~PCell() {
	// TODO Auto-generated destructor stub
}

void PCell::updateCell(int value){//set cell state to inpud values
	state = value;
}

int PCell::getState(){
	return state;
}
