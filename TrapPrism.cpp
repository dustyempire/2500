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

#include "TrapPrism.h"

//Trap Prism
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
	Shape::shapeType = 2;
	a = 0;
	b = 0;
	h = 0;
	off = 0;
}

TrapPrism::TrapPrism(double x_, double y_, double z_, double a_, double b_, double h_, double off_, double depth_) : Shape(x_, y_, z_) {
	Shape::shapeType = 2;
	a = a_;
	b = b_;
	h = h_;
	off = off_;
	depth = depth_;
}

TrapPrism::TrapPrism(double x_, double y_, double z_, double a_, double b_, double h_, double off_, double depth_, double rotation_) : Shape(x_, y_, z_, rotation_) {
	Shape::shapeType = 2;
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

	point one = { -a / 2, 0, -depth / 2 };
	point two = { -a / 2 + off, h, -depth / 2 };
	point three = { -a / 2 + off + b, h, -depth / 2 };
	point four = { a / 2, 0, -depth / 2 };

	point five = { -a / 2, 0, depth / 2 };
	point six = { -a / 2 + off, h, depth / 2 };
	point seven = { -a / 2 + off + b, h, depth / 2 };
	point eight = { a / 2, 0, depth / 2 };

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

void TrapPrism::makeQuad(point *a, point *b, point *c, point *d) {
	glBegin(GL_QUADS);
	glVertex3d(a->x, a->y, a->z);
	glVertex3d(b->x, b->y, b->z);
	glVertex3d(c->x, c->y, c->z);
	glVertex3d(d->x, d->y, d->z);
	glEnd();
}

void TrapPrism::makeTri(point *a, point *b, point *c) {
	glBegin(GL_TRIANGLES);
	glVertex3d(a->x, a->y, a->z);
	glVertex3d(b->x, b->y, b->z);
	glVertex3d(c->x, c->y, c->z);
	glEnd();
}