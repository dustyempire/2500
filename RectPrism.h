#pragma once
#include "Shape.hpp"

class RectPrism : public Shape {

public:
	RectPrism();
	~RectPrism();
	RectPrism(double x_, double y_, double z_, double x_length, double y_length, double z_length);
	RectPrism(double x_, double y_, double z_, double x_length, double y_length, double z_length, double rotation_);

	double getXLength();
	double getYLength();
	double getZLength();

	void setXLength(double x_);
	void setYLength(double y_);
	void setZLength(double z_);

	void draw();

	void setSteer(bool state);
	void setSpin(bool state);

	bool getSteer();
	bool getSpin();

	struct point { //defines vertices points
		double x;
		double y;
		double z;
	};

	void makeQuad(point *a, point *b, point *c, point *d); //draws quad in gl


private:
	double xLength, yLength, zLength;

	bool isSteer;
	bool isSpin;

};

