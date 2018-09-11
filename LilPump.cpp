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

#include "LilPump.h"
#include "TrapPrism.h"
#include "RectPrism.h"
#include "TriPrism.h"
#include "Cylinder.h"


LilPump::~LilPump()
{
}

VehicleModel LilPump::getVM()
{
	return vm;
}

void LilPump::draw() {
	glPushMatrix();
	//move to vehicle position
	positionInGL();

	for (int i = 0; i < shapes.size(); i++) {
		shapes[i]->draw();
	}
	glPopMatrix();
}

void LilPump::init_vm() {
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

LilPump::LilPump() {
	TrapPrism *LeftFoot = new TrapPrism(0.2 * 2, 0 * 2, -1 * 2, 1.5 * 2, 1 * 2, 0.25 * 2, 0.25 * 2, 2 * 2, 90);
	LeftFoot->setColor(0.78, 0.59, 0.51);
	addShape(LeftFoot);
	TrapPrism *RightFoot = new TrapPrism(0.2 * 2, 0 * 2, 1 * 2, 1.5 * 2, 1 * 2, 0.25 * 2, 0.25 * 2, 2 * 2, 90);
	RightFoot->setColor(0.78, 0.59, 0.51);
	addShape(RightFoot);

	RectPrism *LeftLeg = new RectPrism(0 * 2, 0.25 * 2, -1 * 2, 1.5 * 2, 1.5 * 2, 1.75 * 2);
	LeftLeg->setColor(0.63, 0.47, 0.47);
	addShape(LeftLeg);
	RectPrism *RightLeg = new RectPrism(0 * 2, 0.25 * 2, 1 * 2, 1.5 * 2, 1.5 * 2, 1.75 * 2);
	RightLeg->setColor(0.63, 0.47, 0.47);
	addShape(RightLeg);

	RectPrism *Body = new RectPrism(0 * 2, 1.75 * 2, 0 * 2, 1.5 * 2, 2.75 * 2, 4 * 2);
	Body->setColor(0.44, 0.21, 0.21);
	addShape(Body);

	RectPrism *LeftArm = new RectPrism(0 * 2, 1.5 * 2, -2.5 * 2, 1.5 * 2, 3 * 2, 1 * 2);
	LeftArm->setColor(0.42, 0.19, 0.19);
	addShape(LeftArm);
	RectPrism *RightArm = new RectPrism(0 * 2, 1.5 * 2, 2.5 * 2, 1.5 * 2, 3 * 2, 1 * 2);
	RightArm->setColor(0.42, 0.19, 0.19);
	addShape(RightArm);

	RectPrism *Head = new RectPrism(-0.15 * 2, 4.5 * 2, 0 * 2, 0.6 * 2, 0.8 * 2, 0.6 * 2);
	Head->setColor(0.95, 0.75, 0.58);
	addShape(Head);

	Cylinder *LeftEye = new Cylinder(0.155 * 2, 5 * 2, -0.15 * 2, 0.05 * 2, 0.05 * 2, 90);
	LeftEye->setColor(0.1, 0.1, 0.1);
	addShape(LeftEye);
	Cylinder *RightEye = new Cylinder(0.155 * 2, 5 * 2, 0.15 * 2, 0.05 * 2, 0.05 * 2, 90);
	RightEye->setColor(0.1, 0.1, 0.1);
	addShape(RightEye);
	RectPrism *Mouth = new RectPrism(0.155 * 2, 4.7 * 2, 0 * 2, 0.05 * 2, 0.05 * 2, 0.4 * 2);
	Mouth->setColor(0.1, 0.1, 0.1);
	addShape(Mouth);

	TrapPrism *Hair = new TrapPrism(-0.15 * 2, 4.6 * 2, 0.4 * 2, 0.3 * 2, 0.25 * 2, 0.72 * 2, 0.25 * 2, 0.7 * 2, -90);
	Hair->setColor(0.32, 0.08, 0.23);
	addShape(Hair);

	RectPrism *Hair2 = new RectPrism(-0.15 * 2, 5.3 * 2, 0.0 * 2, 0.6 * 2, 0.05 * 2, 0.6 * 2);
	Hair2->setColor(0.32, 0.08, 0.23);
	addShape(Hair2);

	Cylinder *Piece = new Cylinder(0.8 * 2, 3 * 2, 0 * 2, 0.4 * 2, 0.2 * 2, 90);
	Piece->setColor(0.98, 0.93, 0.55);
	addShape(Piece);

	TrapPrism *LeftChain = new TrapPrism(0.8 * 2, 3.8 * 2, 0 * 2, 0.4 * 2, 0.4 * 2, 0.8 * 2, 0.65 * 2, 0.2 * 2, 90);
	LeftChain->setColor(0.98, 0.93, 0.55);
	addShape(LeftChain);

	TrapPrism *RightChain = new TrapPrism(0.8 * 2, 3.8 * 2, 0 * 2, 0.4 * 2, 0.4 * 2, 0.8 * 2, 0.65 * 2, 0.2 * 2, -90);
	RightChain->setColor(0.98, 0.93, 0.55);
	addShape(RightChain);

	init_vm();
}
