/*
 * PGrid.h
 *
 *  Created on: 4 Dec 2016
 *      Author: user
 */

#ifndef PGRID_H_
#define PGRID_H_
#include"PCell.h"
#include <vector>


class PGrid {
private:
	int m_gSize;
	int currentCell;
	PCell *grid;
	bool possRout;
	std::vector<int> map;
public:
	PGrid(int);
	void populate(double pValue);
	virtual ~PGrid();
	void init();
	void setFinish();
	int getCell(int);
	bool process();
	bool checkNeighbours();
	bool move();
	void printGrid();
};

#endif /* PGRID_H_ */
