/*
 * RangeController.cpp
 *
 *  Created on: 29/04/2010
 *      Author: oscar
 */

#include "RangeController.h"

RangeController::RangeController( int minumun, int maximun){
  this->maximun=maximun;
  this->minumun=minumun;
  this->modificate=false;
	// TODO Auto-generated constructor stub

}

RangeController::~RangeController() {
	// TODO Auto-generated destructor stub
}
bool RangeController::isRangeValidator(int index){
      return (index >= this->minumun && index <= this->maximun);
}
