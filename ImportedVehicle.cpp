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

#include "ImportedVehicle.h"
#include "TrapPrism.h"
#include "RectPrism.h"
#include "TriPrism.h"
#include "Cylinder.h"

ImportedVehicle::ImportedVehicle() : Vehicle() {
}

ImportedVehicle::~ImportedVehicle() {
}

void ImportedVehicle::draw() {

	glPushMatrix();

	positionInGL();

	//draw each shape and iterate through list
	for (int i = 0; i < shapes.size(); i++) {
		Cylinder *check = dynamic_cast <Cylinder*> (shapes[i]);

		if (check != nullptr && check->getSpin() == TRUE) {
			if (check->getSpinRotation() > 360) {
				check->setSpinRotation(check->getSpinRotation() - 360);
			}
			if (check->getSpinRotation() < -360) {
				check->setSpinRotation(check->getSpinRotation() + 360);
			}

			check->setSpinRotation(check->getSpinRotation() + 2 * speed); //changes spin orientation
		}

		if (check != nullptr && check->getSteer() == TRUE) {
			check->setRotation(check->originalRotation + getSteering()); //changes rotation of the cylinder
		}

		shapes[i]->draw();
	}

	glPopMatrix();
}