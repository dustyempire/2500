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

#include "RectPrism.h"

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

RectPrism::RectPrism(double x_, double y_, double z_, double x_length, double y_length, double z_length) : Shape(x_, y_, z_) {
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

	point one = { -xLength / 2, 0, -zLength / 2 };
	point two = { -xLength / 2, yLength, -zLength / 2 };
	point three = { xLength / 2, yLength, -zLength / 2 };
	point four = { xLength / 2, 0, -zLength / 2 };

	point five = { -xLength / 2, 0, zLength / 2 };
	point six = { -xLength / 2, yLength, zLength / 2 };
	point seven = { xLength / 2, yLength, zLength / 2 };
	point eight = { xLength / 2, 0, zLength / 2 };

	makeQuad(&one, &two, &three, &four); //front
	makeQuad(&five, &six, &seven, &eight); //back
	makeQuad(&one, &five, &eight, &four); //bottom
	makeQuad(&two, &six, &seven, &three); //top
	makeQuad(&two, &six, &five, &one); //Lside
	makeQuad(&three, &seven, &eight, &four); //Rside

	glPopMatrix();

}

void RectPrism::setSteer(bool state) {
	isSteer = state;
}

void RectPrism::setSpin(bool state) {
	isSpin = state;
}

bool RectPrism::getSteer()
{
	return isSteer;
}

bool RectPrism::getSpin()
{
	return isSpin;
}

//draws quad in gl for neatness
void RectPrism::makeQuad(point *a, point *b, point *c, point *d) {
	glBegin(GL_QUADS);
	glVertex3d(a->x, a->y, a->z);
	glVertex3d(b->x, b->y, b->z);
	glVertex3d(c->x, c->y, c->z);
	glVertex3d(d->x, d->y, d->z);
	glEnd();
}