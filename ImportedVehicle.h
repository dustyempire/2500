#pragma once
#include "Vehicle.hpp"

class ImportedVehicle : public Vehicle {

public:

	ImportedVehicle();
	~ImportedVehicle();
	void draw();
	//void fillProperties(VehicleModel vm); 

private:
	double size;

};
