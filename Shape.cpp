
#include "Shape.hpp"
#include <math.h>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#elif defined(WIN32)
#include <Windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#define PI 3.1415926

Shape::Shape() {
	x = y = z = 0.0;
	rotation = 0.0;
	red = green = blue = 1.0;
};

Shape::Shape(double x_, double y_, double z_) {
	x = x_;
	y = y_;
	z = z_;

	rotation = 0.0;
	red = green = blue = 1.0;
};

Shape::Shape(double x_, double y_, double z_, double rotation_) {

	x = x_;
	y = y_;
	z = z_;

	rotation = rotation_;
	red = green = blue = 1.0;
};

Shape::~Shape() {
}

double Shape::getX() {
	return x;
};

double Shape::getY() {
	return y;
};

double Shape::getZ() {
	return z;
};

double Shape::getRotation() {
	return rotation;
};

void Shape::setX(double x_) {
	x = x_;
};

void Shape::setY(double y_) {
	y = y_;
};

void Shape::setZ(double z_) {
	z = z_;
};

void Shape::setRotation(double rotation_) {
	rotation = rotation_;
};


void Shape::setPosition(double x_, double y_, double z_) {
	x = x_;
	y = y_;
	z = z_;
};

void Shape::positionInGL() {
	glTranslated(x, y, z);
	glRotated(-rotation, 0, 1, 0);
};

void Shape::setColorInGL() {
	glColor3f(red, green, blue);
};

double Shape::getRed() {
	return red;
};

double Shape::getGreen() {
	return green;
};

double Shape::getBlue() {
	return blue;
};

void Shape::setColor(float red_, float green_, float blue_) {
	red = red_;
	green = green_;
	blue = blue_;
};

//draws quad in gl for neatness
void makeQuad(point *a, point *b, point *c, point *d) {
	glBegin(GL_QUADS);
	glVertex3d(a->x, a->y, a->z);
	glVertex3d(b->x, b->y, b->z);
	glVertex3d(c->x, c->y, c->z);
	glVertex3d(d->x, d->y, d->z);
	glEnd();
}
void makeTri(point *a, point *b, point *c) {
	glBegin(GL_TRIANGLES);
	glVertex3d(a->x, a->y, a->z);
	glVertex3d(b->x, b->y, b->z);
	glVertex3d(c->x, c->y, c->z);
	glEnd();
}

//rectangular prism
RectPrism::~RectPrism() {
}

double RectPrism::getXLength() {
	return xLength;
}

double RectPrism::getYLength() {
	return yLength;
}

double RectPrism::getZLength() {
	return zLength;
}

void RectPrism::setXLength(double x_) {
	xLength = x_;
}

void RectPrism::setYLength(double y_) {
	xLength = y_;
}

void RectPrism::setZLength(double z_) {
	xLength = z_;
}

RectPrism::RectPrism() : Shape() {
	xLength = 0.0;
	yLength = 0.0;
	zLength = 0.0;
}

RectPrism::RectPrism(double x_, double y_, double z_, double x_length, double y_length, double z_length): Shape(x_, y_, z_) {
	xLength = x_length;
	yLength = y_length;
	zLength = z_length;
}

RectPrism::RectPrism(double x_, double y_, double z_, double x_length, double y_length, double z_length, double rotation_) : Shape(x_, y_, z_, rotation_) {
	xLength = x_length;
	yLength = y_length;
	zLength = z_length;
}

void RectPrism::draw() {

	glPushMatrix();
	positionInGL();
	setColorInGL();
	//positionInGL();

	point one = { xLength / 2, 0, -zLength / 2 };
	point two = { xLength / 2, yLength, -zLength / 2 };
	point three = { -xLength / 2, yLength, -zLength / 2 };
	point four = { -xLength / 2, 0, -zLength / 2 };

	point five = { xLength / 2, 0, zLength / 2 };
	point six = { xLength / 2, yLength, zLength / 2 };
	point seven = { -xLength / 2, yLength, zLength / 2 };
	point eight = { -xLength / 2, 0, zLength / 2 };

	makeQuad(&one, &two, &three, &four); //front
	makeQuad(&five, &six, &seven, &eight); //back
	makeQuad(&one, &five, &eight, &four); //bottom
	makeQuad(&two, &six, &four, &three); //top
	makeQuad(&two, &six, &five, &one); //Lside
	makeQuad(&three, &seven, &eight, &four); //Rside

	glPopMatrix();

	
}

//triangular prism
TriPrism::~TriPrism() {
}

double TriPrism::getA()
{
	return a;
}

double TriPrism::getB()
{
	return b;
}

double TriPrism::getDepth()
{
	return depth;
}

double TriPrism::getTheta()
{
	return theta;
}

void TriPrism::setA(double a_)
{
	a = a_;
}

void TriPrism::setB(double b_)
{
	b = b_;
}

void TriPrism::setDepth(double depth_)
{
	depth = depth_;
}

void TriPrism::setTheta(double theta_)
{
	theta = theta_;
}

TriPrism::TriPrism() : Shape() {
	a = 0;
	b = 0;
	depth = 0;
	theta = 0;
}

TriPrism::TriPrism(double x_, double y_, double z_, double a_, double b_, double theta_, double depth_) : Shape(x_, y_, z_) {
	a = a_;
	b = b_;
	depth = depth_;
	theta = (theta_* PI) / 180;
}

TriPrism::TriPrism(double x_, double y_, double z_, double a_, double b_, double theta_, double depth_, double rotation_) : Shape(x_, y_, z_, rotation_) {
	a = a_;
	b = b_;
	depth = depth_;
	theta = (theta_* PI) / 180;
}

void TriPrism::draw(){

	glPushMatrix();
	positionInGL();
	setColorInGL();

	//points below take poisitve x to the left
	point one = { a / 2, 0, -depth / 2 };
	point two = { (a / 2) - b*(cos(theta)), b*(sin(theta)), -depth / 2 };
	point three = { -a / 2, 0, -depth / 2 };
	point four = { a / 2, 0, depth / 2 };
	point five = { (a / 2) - b*cos(theta), b*sin(theta), depth / 2 };
	point six = { -a / 2, 0, depth / 2 };

	makeTri(&one, &two, &three); //front
	makeTri(&four, &five, &six); //back
	makeQuad(&one, &four, &six, &three); //bottom
	makeQuad(&one, &two, &five, &four); //left
	makeQuad(&three, &two, &five, &six); //right

	glPopMatrix();
}



TrapPrism::~TrapPrism() {
}

double TrapPrism::getA()
{
	return a;
}

double TrapPrism::getB()
{
	return b;
}

double TrapPrism::getOffset()
{
	return off;
}

double TrapPrism::getH()
{
	return h;
}

double TrapPrism::getDepth()
{
	return depth;
}

void TrapPrism::setA(double a_)
{
	a = a_;
}

void TrapPrism::setB(double b_)
{
	b = b_;
}

void TrapPrism::setOffset(double off_)
{
	off = off_;
}

void TrapPrism::setH(double h_)
{
	h = h_;
}

void TrapPrism::setDepth(double depth_)
{
	depth = depth_;
}

TrapPrism::TrapPrism() : Shape() {
	a = 0;
	b = 0;
	h = 0;
	off = 0;
}

TrapPrism::TrapPrism(double x_, double y_, double z_, double a_, double b_, double h_, double off_, double depth_) : Shape(x_, y_, z_) {
	a = a_;
	b = b_;
	h = h_;
	off = off_;
	depth = depth_;
}

TrapPrism::TrapPrism(double x_, double y_, double z_, double a_, double b_, double h_, double off_, double depth_, double rotation_) : Shape(x_, y_, z_, rotation_) {
	a = a_;
	b = b_;
	h = h_;
	off = off_;
	depth = depth_;
}

void TrapPrism::draw() {
	glPushMatrix();
	positionInGL();
	setColorInGL();

	point one = { a / 2, 0, -depth / 2 };
	point two = { a / 2 - off, h, -depth / 2 };
	point three = { a / 2 - off - b, h, -depth / 2 };
	point four = { -a / 2, 0, -depth / 2 };

	point five = { a / 2, 0, depth / 2 };
	point six = { a / 2 - off, h, depth / 2 };
	point seven = { a / 2 - off - b, h, depth / 2 };
	point eight = { -a / 2, 0, depth / 2 };

	makeTri(&one, &two, &four); //front L
	makeTri(&two, &three, &four); //front R
	makeTri(&five, &six, &eight); //back L
	makeTri(&six, &seven, &eight); //back R;

	makeQuad(&one, &five, &eight, &four); //bottom
	makeQuad(&two, &six, &seven, &three); //top
	makeQuad(&one, &two, &six, &five); //left
	makeQuad(&four, &three, &seven, &eight); //right

	glPopMatrix();
}

Cylinder::Cylinder(): Shape() {
	r = 0;
	depth = 0;
}

Cylinder::~Cylinder() {
}

Cylinder::Cylinder(double x_, double y_, double z_, double r_, double depth_): Shape(x_, y_, z_) {
	r = r_;
	depth = depth_;
}

Cylinder::Cylinder(double x_, double y_, double z_, double r_, double depth_, double rotation_): Shape(x_, y_, z_, rotation_) {
	r = r_;
	depth = depth_;
}

double Cylinder::getR() {
	return r;
}

double Cylinder::getDepth() {
	return depth;
}

void Cylinder::setR(double r_) {
	r = r_;
}

void Cylinder::setDepth(double depth_) {
	depth = depth_;
}

void Cylinder::draw()
{
	glPushMatrix();
	positionInGL();
	setColorInGL();

	glTranslated(0, r, -depth / 2); //moves so cylinder centre will be at origin
	GLUquadric* sides;
	sides = gluNewQuadric();
	gluCylinder(sides, r, r, depth, 20, 1); //makes cylinder sides
	
	GLUquadric* endF; //makes front end at where cylinsed side start is
	endF = gluNewQuadric();
	gluDisk(endF, 0, r, 20, 1);

	glTranslated(0, 0, depth); //moves making point to end of cylinder
	GLUquadric* endB;
	endB = gluNewQuadric();
	gluDisk(endB, 0, r, 20, 1); //makes cylinder back end

	glPopMatrix(); //resets to last matrix
}
