#pragma once
#include "Vehicle.hpp"

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
