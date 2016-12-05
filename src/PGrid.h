/*
 * PGrid.h
 *
 *  Created on: 4 Dec 2016
 *      Author: user
 */

#ifndef PGRID_H_
#define PGRID_H_
#include"PCell.h"


class PGrid {
private:
	int m_gSize;
	PCell *grid;
public:
	PGrid(int, double);
	virtual ~PGrid();
	void init();
	void setFinish();
	int getCell(int);

};

#endif /* PGRID_H_ */
