#pragma once


#include <Windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "Shape.hpp"
#include "Vehicle.hpp"

class car : public Vehicle {

public:

	car();

	~car();

	virtual void draw();
};