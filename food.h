#ifndef FOOD_H
#define FOOD_H

class food
{
public:
	food();
	food(double posx_, double posy_);

	//Getters
	int getfoodRadius();
	int getfoodPosx();
	int getfoodPosy();
	int getfoodTotal();

	//Setters
	void setPosx_f(double foodPosx_);
	void setPosy_f(double foodPosy_);

protected:
	double foodPosx;
	double foodPosy;
	int foodRadius;
	int foodTotalCount;
};

#endif