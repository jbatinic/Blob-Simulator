#include "food.h"

unsigned int food::foodTotalCount = 0;

food::food(void){
	foodPosx = 0;
	foodPosy = 0;
	foodRadius = 0;
}

food::food(double posx_, double posy_)
{
	foodPosx = posx_;
	foodPosy = posy_;
	foodRadius = FOODRADIUS;
}

//setters
void food::setPosx_f(double foodPosx_){	foodPosx = foodPosx_;}
void food::setPosy_f(double foodPosy_){	foodPosy = foodPosy_;}
void food::setfoodRadius() { foodRadius = FOODRADIUS; }

//getters
unsigned int food::getfoodRadius(void) { return foodRadius; }
unsigned int food::getfoodTotal(void) { return foodTotalCount; }
double food::getPosx_f(void) { return foodPosx; }
double food::getPosy_f(void) { return foodPosy; }