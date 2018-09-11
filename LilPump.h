#pragma once
#include "Vehicle.hpp"
#include "Messages.hpp"

class LilPump : public Vehicle {
public:
	LilPump();
	~LilPump();
	VehicleModel getVM();
	void draw();

private:
	VehicleModel vm;

protected:
	void init_vm();
};