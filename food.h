#ifndef FOOD_H
#define FOOD_H

class food
{
public:
	//Constructores
	food(void);
	food(double posx_, double posy_);

	//Getters
	unsigned int getfoodRadius();
	double getPosx_f();
	double getPosy_f();
	unsigned int getfoodTotal();

	//Setters
	void setPosx_f(double foodPosx_);
	void setPosy_f(double foodPosy_);

protected:
	double foodPosx;
	double foodPosy;
	unsigned int foodRadius;
	unsigned int foodTotalCount;
};

#endif