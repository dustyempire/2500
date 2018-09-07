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

#include "MyVehicle.h"
#include "TrapPrism.h"
#include "RectPrism.h"
#include "TriPrism.h"
#include "Cylinder.h"
TestVehicle::TestVehicle() : Vehicle() {

	//links the private shapes to the vehicle shape vecotr
	//maybe unnecessary?
	Cylinder *LBWheel = new Cylinder(-1.5, 0.5, -2, 0.5, 1);
	Cylinder *RBWheel = new Cylinder(-1.5, 0.5, 2, 0.5, 1);
	TrapPrism *Body = new TrapPrism(0.75, 1, 0, 5.5, 3.5, 1, 0.5, 3);
	RectPrism *Top = new RectPrism(0.5, 2, 0, 2, 0.5, 2);
	TriPrism *Spoiler = new TriPrism(-1, 2, 0, 1, 0.5, 160, 3);
	Cylinder *LFWheel = new Cylinder(1.5, 0.5, -2, 0.5, 1);
	Cylinder *RFWheel = new Cylinder(1.5, 0.5, 2, 0.5, 1);

	addShape(LBWheel);
	addShape(RBWheel);
	addShape(LFWheel);
	addShape(RFWheel);
	addShape(Body);
	addShape(Top);
	addShape(Spoiler);

	//sets colors, helps to tell if constructor is called
	LBWheel->setColor(0.2, 0.2, 0.2);
	RBWheel->setColor(0.2, 0.2, 0.2);
	LFWheel->setColor(0.2, 0.2, 0.2);
	RFWheel->setColor(0.2, 0.2, 0.2);
	Body->setColor(0.7, 0.1, 0.2);
	Top->setColor(0.4, 0.4, 0.4);
	Spoiler->setColor(0.5, 0.1, 0.2);

	LFWheel->setSteer(TRUE);
	RFWheel->setSteer(TRUE);

	LFWheel->setSpin(TRUE);
	RFWheel->setSpin(TRUE);
	LBWheel->setSpin(TRUE);
	RBWheel->setSpin(TRUE);


	size = 1;
}

TestVehicle::~TestVehicle() {
}

void TestVehicle::draw() {

	//reset matrix
	glPushMatrix();
	//move to vehicle position
	positionInGL();
	//scale vehicle
	glScaled(size, size, size);

	//draw each shape and iterate through list
	for (int i = 0; i < shapes.size(); i++) {
		Cylinder *check = dynamic_cast <Cylinder*> (shapes[i]);

		if (check != nullptr && check->getSpin() == TRUE) {
			check->setSpinRotation(check->getSpinRotation() + 2 * speed); //changes spin orientation
		}


		if (check != nullptr && check->getSteer() == TRUE) {
			check->setRotation(check->originalRotation + getSteering()); //changes rotation of the cylinder
		}


		shapes[i]->draw();
	}


	glPopMatrix();
}

