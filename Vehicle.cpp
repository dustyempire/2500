
#include "Vehicle.hpp"
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

#include <math.h>

Vehicle::Vehicle() {
	speed = steering = 0;
};

Vehicle::~Vehicle()
{ 
	// clean-up added shapes
	for(int i = 0; i < shapes.size(); i++) {
		delete shapes[i];
	}
}

void Vehicle::update(double dt)
{
	speed = clamp(MAX_BACKWARD_SPEED_MPS, speed, MAX_FORWARD_SPEED_MPS);
	steering = clamp(MAX_LEFT_STEERING_DEGS, steering, MAX_RIGHT_STEERING_DEGS);

	// update position by integrating the speed
	x += speed * dt * cos(rotation * 3.1415926535 / 180.0);
	z += speed * dt * sin(rotation * 3.1415926535 / 180.0);

	// update heading
	rotation += dt * steering * speed;

	while (rotation > 360) rotation -= 360;
	while (rotation < 0) rotation += 360;


	if(fabs(speed) < .1)
		speed = 0;
	if(fabs(steering) < .1)
		steering = 0;

}

void Vehicle::update(double speed_, double steering_, double dt) 
{
	speed = speed + ((speed_) - speed)*dt*4;
	steering = steering + (steering_ - steering)*dt * 6;

	update(dt);
}

void Vehicle::addShape(Shape * shape) 
{
	shapes.push_back(shape);
}

double clamp(double a, double n, double b) {

	if (a < b) {
		if (n < a) n = a;
		if (n > b) n = b;
	} else {
		if (n < b) n = b;
		if (n > a) n = a;
	}
	
	return n;

};

TestVehicle::TestVehicle(): Vehicle() {

	//links the private shapes to the vehicle shape vecotr
	//maybe unnecessary?
	Cylinder *LBWheel = new Cylinder(-1.5, 0.5, -2, 0.5, 1);
	Cylinder *RBWheel = new Cylinder(-1.5, 0.5, 2, 0.5, 1);
	TrapPrism *Body = new TrapPrism(0.75, 1, 0, 5.5, 3.5, 1, 1.5, 3);
	RectPrism *Top = new RectPrism(0.5, 2, 0, 2, 0.5, 2);
	TriPrism *Spoiler = new TriPrism(-1, 2, 0, 1, 1.5, 15, 3);
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
			if (check->getSpinRotation() > 360) {
				check->setSpinRotation(check->getSpinRotation() - 360);
			}
			if (check->getSpinRotation() < -360) {
				check->setSpinRotation(check->getSpinRotation() + 360);
			}

			check->setSpinRotation(check->getSpinRotation() + 2*speed); //changes spin orientation
		}


		if (check != nullptr && check->getSteer() == TRUE) {
			check->setRotation(check->originalRotation + getSteering()); //changes rotation of the cylinder
		}


		shapes[i]->draw();
	}


	glPopMatrix();
}



Gender::~Gender() {
}

Gender::Gender() {
	size = 1;
	altitude = 0;

	TrapPrism *Bottom = new TrapPrism(0.2, 0.2, 0, 2, 2.8, 0.2, -0.1, 0.5);
	TrapPrism *Mid = new TrapPrism(-0.1, 0.4, 0, 2.4, 1.2, 0.3, 0.6, 0.4);
	TrapPrism *Top = new TrapPrism(-0.1, 0.7, 0, 1, 0.45, 0.1, 0.05, 0.2);
	TrapPrism *Tail = new TrapPrism(-1.5, 0.4, 0, 0.4, 1.3, 0.1, -0.3, 0.15);
	TrapPrism *Fin = new TrapPrism(-2.05, 0.5, 0, 0.3, 0.25, 0.55, 0.45, 0.1);
	//RectPrism *BBlade1 = new RectPrism(-2.3, 0.55, -0.075, 0.07, 0.7, 0.02);
		//BBlade1->setSpin(TRUE);
	Cylinder *BBlade2 = new Cylinder(-2.3, 0.6, -0.075, 0.3, 0.02);
		BBlade2->setSpin(TRUE);
	RectPrism *Shaft = new RectPrism(0, 0.8, 0, 0.1, 0.1, 0.1);
	RectPrism *TBlade1 = new RectPrism(0, 0.9, 0, 3.6, 0.03, 0.2);
		TBlade1->setSteer(TRUE);
	RectPrism *TBlade2 = new RectPrism(0, 0.9, 0, 0.2, 0.03, 3.6);
		TBlade2->setSteer(TRUE);
	RectPrism *Topper = new RectPrism(0, 0.93, 0, 0.05, 0.05, 0.05);
	Cylinder *LFWheel = new Cylinder(0.3, 0, -0.2, 0.08, 0.1);
	Cylinder *RFWheel = new Cylinder(0.3, 0, 0.2, 0.08, 0.1);
	TrapPrism *LStrut = new TrapPrism(0.3, 0.05, -0.13, 0.04, 0.3, 0.15, -0.25, 0.04);
	TrapPrism *RStrut = new TrapPrism(0.3, 0.05, 0.13, 0.04, 0.3, 0.15, -0.25, 0.04);
	Cylinder *BackWheel1 = new Cylinder(-1.1, 0, -0.04, 0.06, 0.05);
	Cylinder *BackWheel2 = new Cylinder(-1.1, 0, 0.04, 0.06, 0.05);
	TrapPrism *BackStrut = new TrapPrism(-1.1, 0.08, 0, 0.1, 0.15, 0.2, -0.14, 0.03);
	TriPrism *BackWing = new TriPrism(-2, 0.42, 0, 0.2, 0.1, 160, 0.6);
	TrapPrism *Wings = new TrapPrism(0, 0.35, 0, 0.65, 0.2, 0.11, 0.1, 2);
	RectPrism *hangL1 = new RectPrism(0, 0.3, -0.45, 0.3, 0.05, 0.05);
	RectPrism *hangL2 = new RectPrism(0, 0.3, -0.7, 0.3, 0.05, 0.05);
	TrapPrism *hangL3 = new TrapPrism(0.1, 0.2, -0.45, 0.5, 0.8, 0.1, 0, 0.12);
	TrapPrism *hangL4 = new TrapPrism(0.1, 0.2, -0.7, 0.5, 0.8, 0.1, 0, 0.12);
	RectPrism *hangR1 = new RectPrism(0, 0.3, 0.45, 0.3, 0.05, 0.05);
	RectPrism *hangR2 = new RectPrism(0, 0.3, 0.7, 0.3, 0.05, 0.05);
	TrapPrism *hangR3 = new TrapPrism(0.1, 0.2, 0.45, 0.5, 0.8, 0.1, 0, 0.12);
	TrapPrism *hangR4 = new TrapPrism(0.1, 0.2, 0.7, 0.5, 0.8, 0.1, 0, 0.12);

	addShape(Bottom);	//0
	addShape(Mid);		//1
	addShape(Top);		//2
	addShape(Tail);		//3
	addShape(Fin);		//4
	//addShape(BBlade1);	
	addShape(BBlade2);	//6
	addShape(Shaft);	//7
	addShape(TBlade1);	//8
	addShape(TBlade2);	//9
	addShape(Topper);	//10
	addShape(LFWheel);	//11
	addShape(RFWheel);	//12
	addShape(LStrut);	//13
	addShape(RStrut);	//14
	addShape(BackWheel1);//15
	addShape(BackWheel2);//16
	addShape(BackStrut);//17
	addShape(BackWing);	//18
	addShape(Wings);	//19
	addShape(hangL1);	//20
	addShape(hangL2);	//21
	addShape(hangL3);	//22
	addShape(hangL4);	//23
	addShape(hangR1);	//24
	addShape(hangR2);	//25
	addShape(hangR3);	//26
	addShape(hangR4);	//27

	for (int i = 0; i < shapes.size(); i++) {
		if (i >= 0 && i <= 4)
			shapes[i]->setColor(0.6, 0.6, 0.6); //body
		if (i == 1)
			shapes[i]->setColor(0.2, 0.2, 0.2); //mid

		if (i == 5 || i == 7 || i == 8)
			shapes[i]->setColor(0.4, 0.4, 0.4); //blades
												
		if (i == 10 || i == 11 || i == 14 || i==15)
			shapes[i]->setColor(0.05, 0.05, 0.05); //wheels

		if (i == 6 || i == 9 || i == 12 || i == 13 || i == 16)
			shapes[i]->setColor(0.1, 0.1, 0.1); //struts and supports

		if (i == 18 || i == 17)
			shapes[i]->setColor(0.8, 0.8, 0.8); //wings

		if (i == 20 || i == 19 || i == 24 || i == 23)
			shapes[i]->setColor(0.8, 0.8, 0.8); //holders

		if (i == 22 || i == 21 || i == 26 || i == 25)
			shapes[i]->setColor(0.2, 0.2, 0.2); //holders
			
	}
}

void Gender::update(double dt)
{
	speed = clamp(MAX_BACKWARD_SPEED_MPS, speed, MAX_FORWARD_SPEED_MPS);
	steering = clamp(MAX_LEFT_STEERING_DEGS, steering, MAX_RIGHT_STEERING_DEGS);

	// update position by integrating the speed
	x += speed * dt * cos(rotation * 3.1415926535 / 180.0);
	z += speed * dt * sin(rotation * 3.1415926535 / 180.0);


	while (rotation > 360) rotation -= 360;
	while (rotation < 0) rotation += 360;


	if (fabs(speed) < .1)
		speed = 0;
	if (fabs(steering) < .1)
		steering = 0;

	// update heading
	rotation += dt * steering * 20;
}

void Gender::update(double speed_, double steering_, double dt)
{
	speed = speed + ((speed_)-speed)*dt * 4;
	steering = steering + (steering_ - steering)*dt * 6;

	update(dt);

}

void Gender::draw() {

	double rateSpeed = double(speed / MAX_FORWARD_SPEED_MPS);
	double rateSteer = double(steering / MAX_LEFT_STEERING_DEGS);

	glPushMatrix();
	positionInGL();
	glTranslated(0, altitude, 0);
	glScaled(size, size, size);
	glRotated(-30 * rateSpeed, 0, 0, 1);
	glRotated(rateSteer * rateSpeed * 15, 1, 0, 0);


	for (int i = 0; i < shapes.size(); i++) {
		RectPrism *check = dynamic_cast <RectPrism*> (shapes[i]);

		if (check != nullptr && check->getSteer() == TRUE) {
			if (check->getRotation() > 360) {
				check->setRotation(check->getRotation() - 360);
			}

			check->setRotation(check->getRotation() + 10 * (1 + 2 * abs(rateSpeed)));
		}

		Cylinder *check2 = dynamic_cast <Cylinder*> (shapes[i]);
		if (check2 != nullptr && check2->getSpin() == TRUE) {
			
			if (check2->getSpinRotation() > 360) {
				check2->setSpinRotation(check2->getSpinRotation() - 360);
			}
			if (check2->getSpinRotation() < -360) {
				check2->setSpinRotation(check2->getSpinRotation() + 360);
			}

			check2->setSpinRotation(check2->getSpinRotation() + 10 * (1+ rateSteer));

		}
		
		shapes[i]->draw();

		
	}

	glPopMatrix();
}