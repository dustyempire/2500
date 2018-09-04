
#ifndef MTRN3500_VEHICLE_H
#define MTRN3500_VEHICLE_H

#include <iostream>
#include "Shape.hpp"
#include "VectorMaths.hpp"
#include <vector>

class Vehicle : public Shape {
	friend void remoteDriver(Vehicle * vehicle, double x, double z, double r, double speed_, double steering_);
public:

	Vehicle();
	virtual ~Vehicle();

	virtual void update(double dt);
	virtual void update(double speed_, double steering_, double dt);

	virtual void draw() = 0;

	static const int MAX_FORWARD_SPEED_MPS = 40;
	static const int MAX_BACKWARD_SPEED_MPS = -10;
	static const int MAX_LEFT_STEERING_DEGS = 15;
	static const int MAX_RIGHT_STEERING_DEGS = -15;
	static const int VEHICLE_BOUNDS = 3;

	double getSpeed() const { return speed; }
	double getSteering() const { return steering; }

	void addShape(Shape * shape);
protected:
	double speed;     // m/s
	double steering;  // degrees

	std::vector<Shape *> shapes;
};

double clamp(double a, double n, double b);

class TestVehicle : public Vehicle {

public:
	TestVehicle();
	~TestVehicle();
	TestVehicle(double size_) : TestVehicle() { size = size_; }

	void draw();

private:
	//location of shapes in here? 
	double size;

	// shapes that make up the vehicle are permanently stored in the object
	/* tried to make them in the constructor and linking it to shape vector 
	but once the constructor closed the address of the shapes were reset.
	not quite sure how else to implement this aside from making static objects in the constructor
	or adding shapes in main.
	also doing this breaks the destructor because you can't delete the shapes in here*/
	/*
	Cylinder LBWheel = Cylinder(0.5, 0.5, -2, 0.5, 1);
	Cylinder RBWheel = Cylinder(0.5, 0.5, 2, 0.5, 1);
	TrapPrism Body = TrapPrism(2.75, 1, 0, 5.5, 3.5, 1, 1.5, 3);
	RectPrism Top = RectPrism(2.5, 2, 0, 2, 0.5, 2);
	TriPrism Spoiler = TriPrism(1, 2, 0, 1, 1.5, 15, 3);
	Cylinder LFWheel = Cylinder(3.5, 0.5, -2, 0.5, 1);
	Cylinder RFWheel = Cylinder(3.5, 0.5, 2, 0.5, 1);
	*/
};

class Gender : public Vehicle {

public:
	Gender();
	~Gender();
	Gender(double size_, double alt_) : Gender() { size = size_; altitude = alt_; }

	void update(double dt);
	void update(double speed_, double steering_, double dt);

	void draw();

private:
	int counter;
	double size, altitude;

};
#endif // for MTRN3500_VEHICLE_H

