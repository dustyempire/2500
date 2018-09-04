#include "myVehicle.h"
#include "Shape.hpp"


car::car() {
	
}


car::~car() {

}

void car::draw() {

	glPushMatrix();
	positionInGL();
	RectPrism Rect(0, 0, 0, 5, 5, 5);
	Rect.draw();

	glPushMatrix();
	TriPrism Tri(-5.1, 0, 0, 5, 5, 90, 5);
	Tri.setColor(1,0,0);
	Tri.draw();
	glPopMatrix();

	glPushMatrix();
	Cylinder wheel(1, 0, 2.5, 1, 1);
	wheel.setColor(0, 1, 0);
	wheel.draw();
	glPopMatrix();

	glPushMatrix();
	Cylinder wheel2(1, 0, -2.5, 1, 1);
	wheel2.setColor(0, 1, 0);
	wheel2.draw();
	glPopMatrix();


	glPushMatrix();
	TrapPrism sign(0, 5, 0, 3, 3, 4, 1 , 2);
	sign.setColor(0, 0, 1);
	sign.draw();
	glPopMatrix();

}