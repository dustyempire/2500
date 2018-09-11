#pragma once
#include "Vehicle.hpp"
#include "Messages.hpp"


class Kanye : public Vehicle {
public:
	Kanye();
	~Kanye();
	VehicleModel getVM();
	void draw();

private:
	VehicleModel vm;

protected:
	void init_vm();
};