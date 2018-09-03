
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


Vehicle::Vehicle() {
	speed = steering = 0;
};

Vehicle::~Vehicle()
{ 
	// clean-up added shapes
	//for(int i = 0; i < shapes.size(); i++) {
	//	delete shapes[i];
	//}
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

	addShape(&LBWheel);
	addShape(&RBWheel);
	addShape(&LFWheel);
	addShape(&RFWheel);
	addShape(&Body);
	addShape(&Top);
	addShape(&Spoiler);

	 //sets colors, helps to tell if constructor is called
	LBWheel.setColor(0.2, 0.2, 0.2);
	RBWheel.setColor(0.2, 0.2, 0.2);
	LFWheel.setColor(0.2, 0.2, 0.2);
	RFWheel.setColor(0.2, 0.2, 0.2);
	Body.setColor(0.7, 0.1, 0.2);
	Top.setColor(0.4, 0.4, 0.4);
	Spoiler.setColor(0.5, 0.1, 0.2);

	size = 1;
}

TestVehicle::~TestVehicle() {
}
/*
TestVehicle::TestVehicle(double size_): Vehicle(): {
	TestVehicle();
	size = size_;
}
*/
void TestVehicle::draw() {

	//for (int i = 0; i < shapes.size(); i++) {
		//Shape *temp = shapes[i];
		//temp->draw();
	//}

	//Shape *temp = shapes.at(2);
	//reset matrix
	glPushMatrix();
	//move to vehicle position
	positionInGL();\
	//scale vehicle
	glScaled(size, size, size);

	//draw vehicle areas. could do a pointer actually

	
	for (int i = 0; i < shapes.size(); i++) {
		shapes[i]->draw();
	}
	/*
	LBWheel.draw();
	RBWheel.draw();
	RFWheel.draw();
	LFWheel.draw();
	Body.draw();
	Top.draw();
	Spoiler.draw();
	*/

	glPopMatrix();
}



