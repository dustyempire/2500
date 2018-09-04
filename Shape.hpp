
#ifndef MTRN3500_SHAPE_H
#define MTRN3500_SHAPE_H

// Abstract class
class Shape {

public:
	Shape();
	Shape(double x_, double y_, double z_);
	Shape(double x_, double y_, double z_, double rotation_);
	virtual ~Shape();

	virtual void draw() = 0;

	double getX();
	double getY();
	double getZ();
	double getRotation();

	void setX(double x_);
	void setY(double y_);
	void setZ(double z_);
	void setRotation(double rotation_);

	void setPosition(double x_, double y_, double z_);

	void positionInGL();
	void setColorInGL();

	double getRed();
	double getGreen();
	double getBlue();
	void setColor(float red_, float green_, float blue_);

protected:
	double x, y, z;               // position
	double rotation;              // heading of the object in the horizontal plane (degrees)
	float red, green, blue;       // colour of object

};

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

private:
	double xLength, yLength, zLength;
};

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

private:
	double a, b, depth;
	double theta;
};

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
	void setH (double h_);
	void setDepth(double depth_);

	void draw();

private:
	double a, b, h, off, depth;
};

class Cylinder : public Shape {

public:
	Cylinder();
	~Cylinder();
	Cylinder(double x_, double y_, double z_, double r_, double depth_);
	Cylinder(double x_, double y_, double z_, double r_, double depth_, double rotation_);

	double getR();
	double getDepth();

	void setR(double r_);
	void setDepth(double depth_);

	void draw();

private:
	double r, depth;
};

struct point { //defines vertices points
	double x;
	double y;
	double z;
};

void makeQuad(point *a, point *b, point *c, point *d); //draws quad in gl
void makeTri(point *a, point *b, point *c);

#endif // for MTRN3500_SHAPE_H
