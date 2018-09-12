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

#include "Cylinder.h"

//cylinder
Cylinder::Cylinder() : Shape() {
	Shape::shapeType = 3;
	r = 0;
	depth = 0;
	isSteer = FALSE;
	isSpin = FALSE;
	spinRotation = 0;
	originalRotation = getRotation();
	rims = FALSE;
}

Cylinder::~Cylinder() {
}

Cylinder::Cylinder(double x_, double y_, double z_, double r_, double depth_) : Shape(x_, y_, z_) {
	Shape::shapeType = 3;
	r = r_;
	depth = depth_;
	isSteer = FALSE;
	isSpin = FALSE;
	spinRotation = 0;
	originalRotation = getRotation();
	rims = FALSE;
}

Cylinder::Cylinder(double x_, double y_, double z_, double r_, double depth_, double rotation_) : Shape(x_, y_, z_, rotation_) {
	Shape::shapeType = 3;
	r = r_;
	depth = depth_;
	isSteer = FALSE;
	isSpin = FALSE;
	spinRotation = 0;
	originalRotation = getRotation();
	rims = FALSE;
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
	positionInGL(); //for general location and rotation
	//takes into account steering changes
	setColorInGL();

	glTranslated(0, r, -depth / 2); //moves so cylinder centre will be at origin

	glRotated(-spinRotation, 0, 0, 1); //rotates for spinning effect

	GLUquadric* sides;
	sides = gluNewQuadric();
	gluCylinder(sides, r, r, depth, 20, 1); //makes cylinder sides


	//makes alternating colored sections if the cylinders spin with vehicle, 
	//otherwise just makes disk faces
	if (rims == TRUE) {
		int split = 6; //number of different partial disks made
		double angle = 360 / split;
		bool bright = TRUE; //alternates colours
		for (int k = 0; k < split; k++) {

			if (bright == TRUE) {
				glColor3d(Cylinder::red, Cylinder::green, Cylinder::blue); //color 1
			}
			else {
				glColor3d(0.2, 0.2, 0.2); //color 2
			}

			GLUquadric* rim;
			rim = gluNewQuadric();
			gluPartialDisk(rim, 0, r, 20, 1, k * angle, angle);
			bright = !bright;
		}
		setColorInGL();
	}
	else {
		setColorInGL();
		GLUquadric* endF; //makes plain disk
		endF = gluNewQuadric();
		gluDisk(endF, 0, r, 10, 1);
	}

	glTranslated(0, 0, depth); //moves making point to other side of cylinder

	if (rims == TRUE) {
		int split = 6;
		double angle = 360 / split;
		bool bright = TRUE;
		for (int k = 0; k < split; k++) {

			if (bright == TRUE) {
				glColor3d(Cylinder::red, Cylinder::green, Cylinder::blue);
			}
			else {
				glColor3d(0.2, 0.2, 0.2);
			}

			GLUquadric* rim;
			rim = gluNewQuadric();
			gluPartialDisk(rim, 0, r, 20, 1, k * angle, angle);
			bright = !bright;
		}
		setColorInGL();
	}
	else {
		GLUquadric* endF; //makes plain disk
		endF = gluNewQuadric();
		gluDisk(endF, 0, r, 10, 1);
	}


	glPopMatrix(); //resets to last matrix
}

void Cylinder::setSteer(bool state) {
	isSteer = state;
}

void Cylinder::setSpin(bool state) {
	isSpin = state;
	if (isSpin == TRUE) {
		rims = TRUE;
	}
}

bool Cylinder::getSteer()
{
	return isSteer;
}

bool Cylinder::getSpin()
{
	return isSpin;
}

double Cylinder::getSpinRotation() {
	return spinRotation;
}

void Cylinder::setSpinRotation(double spin_) {
	spinRotation = spin_;
}

void Cylinder::setRims(bool state) {
	rims = state;
}

bool Cylinder::getRims() {
	return rims;
}
