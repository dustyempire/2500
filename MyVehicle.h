#pragma once
#include "Vehicle.hpp"
#include "Messages.hpp"

class TestVehicle : public Vehicle {

public:
	TestVehicle();
	~TestVehicle();
	TestVehicle(double size_) : TestVehicle() { size = size_; }
	VehicleModel getVM();
	void draw();
	//void fillProperties(VehicleModel vm); 

private:
	double size;
	VehicleModel vm;

protected:
	void init_vm();
};
