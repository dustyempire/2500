
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

	static const int MAX_FORWARD_SPEED_MPS = 100;
	static const int MAX_BACKWARD_SPEED_MPS = -50;
	static const int MAX_LEFT_STEERING_DEGS = 5;
	static const int MAX_RIGHT_STEERING_DEGS = -5;
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

	//void fillProperties(VehicleModel vm); 

private:
	double size;

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
	double size, altitude;

};

class Imported : public Vehicle {
	
public:
	Imported();
	~Imported();

	void draw();

private:


};
#endif // for MTRN3500_VEHICLE_H

