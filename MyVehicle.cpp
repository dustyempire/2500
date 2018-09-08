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

#include "MyVehicle.h"
#include "TrapPrism.h"
#include "RectPrism.h"
#include "TriPrism.h"
#include "Cylinder.h"



TestVehicle::TestVehicle() : Vehicle() {

	//links the private shapes to the vehicle shape vecotr
	//maybe unnecessary?
	Cylinder *LBWheel = new Cylinder(-1.5, 0.5, -2, 0.5, 1);
	Cylinder *RBWheel = new Cylinder(-1.5, 0.5, 2, 0.5, 1);
	TrapPrism *Body = new TrapPrism(0.75, 1, 0, 5.5, 3.5, 1, 0.5, 3);
	RectPrism *Top = new RectPrism(0.5, 2, 0, 2, 0.5, 2);
	TriPrism *Spoiler = new TriPrism(-1, 2, 0, 1, 0.5, 160, 3);
	Cylinder *LFWheel = new Cylinder(1.5, 0.5, -2, 0.5, 1);
	Cylinder *RFWheel = new Cylinder(1.5, 0.5, 2, 0.5, 1);

	addShape(LBWheel);
	addShape(RBWheel);
	addShape(LFWheel);
	addShape(RFWheel);
	addShape(Body);
	addShape(Top);
	addShape(Spoiler);

	//sets colors, helps to tell if constructor is called
	LBWheel->setColor(0.2, 0.2, 0.2);
	RBWheel->setColor(0.2, 0.2, 0.2);
	LFWheel->setColor(0.2, 0.2, 0.2);
	RFWheel->setColor(0.2, 0.2, 0.2);
	Body->setColor(0.7, 0.1, 0.2);
	Top->setColor(0.4, 0.4, 0.4);
	Spoiler->setColor(0.5, 0.1, 0.2);

	LFWheel->setSteer(TRUE);
	RFWheel->setSteer(TRUE);

	LFWheel->setSpin(TRUE);
	RFWheel->setSpin(TRUE);
	LBWheel->setSpin(TRUE);
	RBWheel->setSpin(TRUE);


	size = 1;
	init_vm();
}

TestVehicle::~TestVehicle() {
}

void TestVehicle::draw() {

	//reset matrix
	glPushMatrix();
	//move to vehicle position
	positionInGL();
	//scale vehicle
	glScaled(size, size, size);

	//draw each shape and iterate through list
	for (int i = 0; i < shapes.size(); i++) {
		Cylinder *check = dynamic_cast <Cylinder*> (shapes[i]);

		if (check != nullptr && check->getSpin() == TRUE) {
			check->setSpinRotation(check->getSpinRotation() + 2 * speed); //changes spin orientation
		}


		if (check != nullptr && check->getSteer() == TRUE) {
			check->setRotation(check->originalRotation + getSteering()); //changes rotation of the cylinder
		}


		shapes[i]->draw();
	}

	/*for (int k = 0; k < vm.shapes.size(); k++) {
		if ((vm.shapes[k]).type == RECTANGULAR_PRISM) { //if rect
			ShapeParameter *params = &vm.shapes[k].params; //pointer for neatness and readability
			//copy properties over by constructing (position is 0, 0, 0, for now)
			Shape *copy = new RectPrism(vm.shapes[k].xyz[0], vm.shapes[k].xyz[1], vm.shapes[k].xyz[2], params->rect.xlen, params->rect.ylen, params->rect.zlen, vm.shapes[k].rotation);
			//add the newly created shape to the shape list of the vehicle 'other' is pointing to
			copy->setColor(vm.shapes[k].rgb[0], vm.shapes[k].rgb[1], vm.shapes[k].rgb[2]);
			copy->draw();
		}
		if ((vm.shapes[k]).type == TRIANGULAR_PRISM) {
			ShapeParameter *params = &vm.shapes[k].params;
			Shape *copy = new TriPrism(vm.shapes[k].xyz[0], vm.shapes[k].xyz[1], vm.shapes[k].xyz[2], params->tri.alen, params->tri.blen, params->tri.angle, params->tri.depth, vm.shapes[k].rotation);
			copy->setColor(vm.shapes[k].rgb[0], vm.shapes[k].rgb[1], vm.shapes[k].rgb[2]);
			copy->draw();
		}
		if ((vm.shapes[k]).type == TRAPEZOIDAL_PRISM) {
			ShapeParameter *params = &vm.shapes[k].params;
			Shape *copy = new TrapPrism(vm.shapes[k].xyz[0], vm.shapes[k].xyz[1], vm.shapes[k].xyz[2], params->trap.alen, params->trap.blen, params->trap.height, params->trap.aoff, params->trap.depth, vm.shapes[k].rotation);
			copy->setColor(vm.shapes[k].rgb[0], vm.shapes[k].rgb[1], vm.shapes[k].rgb[2]);
			copy->draw();
		}

		if ((vm.shapes[k]).type == CYLINDER) {
			ShapeParameter *params = &vm.shapes[k].params;
			Shape *copy = new Cylinder(vm.shapes[k].xyz[0], vm.shapes[k].xyz[1], vm.shapes[k].xyz[2], params->cyl.radius, params->cyl.depth, vm.shapes[k].rotation);
			//set up a dynamic cast which should succeed.
			Cylinder *dynamic = dynamic_cast<Cylinder *> (copy);
			//set steering and rolling properties
			dynamic->setSpin(params->cyl.isRolling);
			dynamic->setSteer(params->cyl.isSteering);
			dynamic->originalRotation = vm.shapes[k].rotation;
			copy->setColor(vm.shapes[k].rgb[0], vm.shapes[k].rgb[1], vm.shapes[k].rgb[2]);
			copy->draw();
		}
	}*/


	glPopMatrix();
}

void TestVehicle::init_vm() {
	for (int i = 0; i < shapes.size(); i++) {
		Shape *it = dynamic_cast <Shape*> (shapes[i]);
		if (it != nullptr && it->getShapeType() == RECT_PRISM) {
			RectPrism *it = dynamic_cast <RectPrism*>(shapes[i]);
			ShapeInit newShape;
			newShape.type = RECTANGULAR_PRISM;
			newShape.xyz[0] = it->getX();
			newShape.xyz[1] = it->getY();
			newShape.xyz[2] = it->getZ();
			newShape.params.rect.xlen = it->getXLength();
			newShape.params.rect.ylen = it->getYLength();
			newShape.params.rect.zlen = it->getZLength();
			newShape.rotation = it->getRotation();
			newShape.rgb[0] = it->getRed();
			newShape.rgb[1] = it->getGreen();
			newShape.rgb[2] = it->getBlue();

			vm.shapes.push_back(newShape);
		}
		else if (it->getShapeType() == TRI_PRISM) {
			TriPrism *it = dynamic_cast <TriPrism*>(shapes[i]);
			ShapeInit newShape;
			newShape.type = TRIANGULAR_PRISM;
			newShape.xyz[0] = it->getX();
			newShape.xyz[1] = it->getY();
			newShape.xyz[2] = it->getZ();
			newShape.params.tri.alen = it->getA();
			newShape.params.tri.blen = it->getB();
			newShape.params.tri.angle = it->getTheta();
			newShape.params.tri.depth = it->getDepth();
			newShape.rotation = it->getRotation();
			newShape.rgb[0] = it->getRed();
			newShape.rgb[1] = it->getGreen();
			newShape.rgb[2] = it->getBlue();
			vm.shapes.push_back(newShape);
		}
		else if (it->getShapeType() == TRAP_PRISM) {
			TrapPrism *it = dynamic_cast <TrapPrism*>(shapes[i]);
			ShapeInit newShape;
			newShape.type = TRAPEZOIDAL_PRISM;
			newShape.xyz[0] = it->getX();
			newShape.xyz[1] = it->getY();
			newShape.xyz[2] = it->getZ();
			newShape.params.trap.alen = it->getA();
			newShape.params.trap.blen = it->getB();
			newShape.params.trap.aoff = it->getOffset();
			newShape.params.trap.depth = it->getDepth();
			newShape.params.trap.height = it->getH();
			newShape.rotation = it->getRotation();
			newShape.rgb[0] = it->getRed();
			newShape.rgb[1] = it->getGreen();
			newShape.rgb[2] = it->getBlue();
			vm.shapes.push_back(newShape);
		}
		else if (it->getShapeType() == CYL) {
			Cylinder *it = dynamic_cast <Cylinder*>(shapes[i]);
			ShapeInit newShape;
			newShape.type = CYLINDER;
			newShape.xyz[0] = it->getX();
			newShape.xyz[1] = it->getY();
			newShape.xyz[2] = it->getZ();
			newShape.params.cyl.depth = it->getDepth();
			newShape.params.cyl.radius = it->getR();
			newShape.rgb[0] = it->getRed();
			newShape.rgb[1] = it->getGreen();
			newShape.rgb[2] = it->getBlue();
			newShape.params.cyl.isRolling = it->getSpin();
			newShape.params.cyl.isSteering = it->getSteer();
			newShape.rotation = it->getRotation();
			vm.shapes.push_back(newShape);
		}
	}
}

VehicleModel TestVehicle::getVM() {
	return vm;
}