#pragma once
#include "Shape.hpp"

class Cylinder : public Shape {

public:
	Cylinder();
	~Cylinder();
	Cylinder(double x_, double y_, double z_, double r_, double depth_);
	Cylinder(double x_, double y_, double z_, double r_, double depth_, double rotation_);

	double getR();
	double getDepth();

	void setR(double r_);
	void setDepth(double depth_);

	void draw();


	//determins whether the cylinder acts as a wheel or not
	void setSteer(bool state);
	void setSpin(bool state);

	bool getSteer();
	bool getSpin();

	//sets the rotation amount of the wheels in degrees
	double getSpinRotation();
	void setSpinRotation(double spin_);

	double originalRotation; //original orientation for vehicles with wheels that aren't face on?

	void setRims(bool state);
	bool getRims();

private:
	double r, depth;

	double spinRotation;

	bool isSteer;
	bool isSpin;

	bool rims;
};

struct point { //defines vertices points
	double x;
	double y;
	double z;
};
