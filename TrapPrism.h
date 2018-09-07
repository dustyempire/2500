#pragma once

#include "Shape.hpp"

class TrapPrism : public Shape {

public:
	TrapPrism();
	~TrapPrism();
	TrapPrism(double x_, double y_, double z_, double a_, double b_, double h_, double off_, double depth_);
	TrapPrism(double x_, double y_, double z_, double a_, double b_, double h_, double off_, double depth_, double rotation_);

	double getA();
	double getB();
	double getOffset();
	double getH();
	double getDepth();

	void setA(double a_);
	void setB(double b_);
	void setOffset(double off_);
	void setH(double h_);
	void setDepth(double depth_);

	void draw();

	struct point { //defines vertices points
		double x;
		double y;
		double z;
	};

	void makeQuad(point *a, point *b, point *c, point *d); //draws quad in gl
	void makeTri(point *a, point *b, point *c);


private:
	double a, b, h, off, depth;
};