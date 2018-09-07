#pragma once
#include "Shape.hpp"
#define PI 3.1415926
class TriPrism : public Shape {

public:
	TriPrism();
	~TriPrism();
	TriPrism(double x_, double y_, double z_, double a_, double b_, double theta_, double depth_);
	TriPrism(double x_, double y_, double z_, double a_, double b_, double theta_, double depth_, double rotation_);

	double getA();
	double getB();
	double getDepth();
	double getTheta();

	void setA(double a_);
	void setB(double b_);
	void setDepth(double depth_);
	void setTheta(double theta_);

	void draw();


	struct point { //defines vertices points
		double x;
		double y;
		double z;
	};

	void makeQuad(point *a, point *b, point *c, point *d); //draws quad in gl
	void makeTri(point *a, point *b, point *c);

private:
	double a, b, depth;
	double theta;
};