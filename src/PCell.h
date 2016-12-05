/*
 * PCell.h
 *
 *  Created on: 4 Dec 2016
 *      Author: user
 */

#ifndef PCELL_H_
#define PCELL_H_

class PCell {
private:
	int state;
public:
	PCell();
	virtual ~PCell();
	void updateCell(int value);
	int getState();
};

#endif /* PCELL_H_ */
