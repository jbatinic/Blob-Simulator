#ifndef FOOD_H
#define FOOD_H

#define FOODRADIUS 4

class food
{
public:
	//Constructores
	food(void);
	food(double posx_, double posy_);

	//static
	static unsigned int foodTotalCount;

	//Getters
	unsigned int getfoodRadius();
	double getPosx_f();
	double getPosy_f();
	unsigned int getfoodTotal();

	//Setters
	void setPosx_f(double foodPosx_);
	void setPosy_f(double foodPosy_);
	void setfoodRadius(void);


protected:
	double foodPosx;
	double foodPosy;
	unsigned int foodRadius;
	
};
#endif