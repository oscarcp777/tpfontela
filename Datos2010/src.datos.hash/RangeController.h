/*
 * RangeController.h
 *
 *  Created on: 29/04/2010
 *      Author: oscar
 */

#ifndef RANGECONTROLLER_H_
#define RANGECONTROLLER_H_
#include <vector>
using namespace std;
class RangeController {
private:
   int minumun;
   int maximun;
   bool modificate;
public:
	RangeController( int minumun, int maximun);
	virtual ~RangeController();
    bool isRangeValidator(int index);
    int getMaximun() const
    {
        return maximun;
    }

    int getMinumun()
    {
        return minumun;
    }

    bool isModificate() const
    {
        return modificate;
    }

    void setMaximun(int maximun)
    {
        this->maximun = maximun;
    }

    void setMinumun(int minumun)
    {
        this->minumun = minumun;
    }

    void setModificate(bool modificate)
    {
        this->modificate = modificate;
    }

};

#endif /* RANGECONTROLLER_H_ */
