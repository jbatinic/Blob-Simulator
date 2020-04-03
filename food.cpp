#include "food.h"

food::food(void){
	foodPosx = 0;
	foodPosy = 0;
}

food::food(double posx_, double posy_)
{
	foodPosx = posx_;
	foodPosy = posy_;
}

//setters
void food::setPosx_f(double foodPosx_)
{
	foodPosx = foodPosx_;
}

void food::setPosy_f(double foodPosy_)
{
	foodPosy = foodPosy_;
}


//getters
unsigned int food::getfoodRadius(void) { return foodRadius; }
unsigned int food::getfoodTotal(void) { return foodTotalCount; }
double food::getPosx_f(void) { return foodPosx; }
double food::getPosy_f(void) { return foodPosy;  }