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

#include "TriPrism.h"
#include <math.h>

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
	point one = { -a / 2, 0, -depth / 2 };
	point two = { -(a / 2) + b*(cos(theta)), b*(sin(theta)), -depth / 2 };
	point three = { a / 2, 0, -depth / 2 };
	point four = { -a / 2, 0, depth / 2 };
	point five = { -(a / 2) + b*cos(theta), b*sin(theta), depth / 2 };
	point six = { a / 2, 0, depth / 2 };

	makeTri(&one, &two, &three); //front
	makeTri(&four, &five, &six); //back
	makeQuad(&one, &four, &six, &three); //bottom
	makeQuad(&one, &two, &five, &four); //left
	makeQuad(&three, &two, &five, &six); //right

	glPopMatrix();
}

void TriPrism::makeQuad(point *a, point *b, point *c, point *d) {
	glBegin(GL_QUADS);
	glVertex3d(a->x, a->y, a->z);
	glVertex3d(b->x, b->y, b->z);
	glVertex3d(c->x, c->y, c->z);
	glVertex3d(d->x, d->y, d->z);
	glEnd();
}
void TriPrism::makeTri(point *a, point *b, point *c) {
	glBegin(GL_TRIANGLES);
	glVertex3d(a->x, a->y, a->z);
	glVertex3d(b->x, b->y, b->z);
	glVertex3d(c->x, c->y, c->z);
	glEnd();
}