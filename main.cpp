
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <map>

#ifdef __APPLE__
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
	#include <GLUT/glut.h>
	#include <unistd.h>
	#include <sys/time.h>
#elif defined(WIN32)
	#include <Windows.h>
	#include <tchar.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
	#include <GL/glut.h>
#else
	#include <GL/gl.h>
	#include <GL/glu.h>
	#include <GL/glut.h>
	#include <unistd.h>
	#include <sys/time.h>
#endif


#include "Camera.hpp"
#include "Ground.hpp"
#include "KeyManager.hpp"

#include "Shape.hpp"
#include "Vehicle.hpp"

#include "RemoteDataManager.hpp"
#include "Messages.hpp"
#include "HUD.hpp"
#include "ObstacleManager.hpp"

#include "RectPrism.h"
#include "TriPrism.h"
#include "TrapPrism.h"
#include "Cylinder.h"

#include "MyVehicle.h"
#include "ImportedVehicle.h"
#include "Gender.h"
#include "LilPump.h"
#include "Kanye.h"

#include "XBoxController.h"
#include "XinputWrapper.h"



void display();
void reshape(int width, int height);
void idle();

void keydown(unsigned char key, int x, int y);
void keyup(unsigned char key, int x, int y);
void special_keydown(int keycode, int x, int y);
void special_keyup(int keycode, int x, int y);

void mouse(int button, int state, int x, int y);
void dragged(int x, int y);
void motion(int x, int y);

using namespace std;
using namespace scos;

// Used to store the previous mouse location so we
//   can calculate relative mouse movement.
int prev_mouse_x = -1;
int prev_mouse_y = -1;

// vehicle control related variables
Vehicle * vehicle = NULL;
double speed = 0;
double steering = 0;

// default goal location
std::deque<GoalState> goals;

std::map<int, Vehicle *> otherVehicles;

int frameCounter = 0;

XInputWrapper xinput;
GamePad::XBoxController controller(&xinput, 0);

//int _tmain(int argc, _TCHAR* argv[]) {
int main(int argc, char ** argv) {

	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;

	glutInit(&argc, (char**)(argv));
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("MTRN3500 - GL");

	Camera::get()->setWindowDimensions(WINDOW_WIDTH, WINDOW_HEIGHT);

	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);

	glutKeyboardFunc(keydown);
	glutKeyboardUpFunc(keyup);
	glutSpecialFunc(special_keydown);
	glutSpecialUpFunc(special_keyup);

	glutMouseFunc(mouse);
	glutMotionFunc(dragged);
	glutPassiveMotionFunc(motion);

	// -------------------------------------------------------------------------
	// Please uncomment the following line of code and replace 'MyVehicle'
	//   with the name of the class you want to show as the current 
	//   custom vehicle.
	// -------------------------------------------------------------------------

	//vehicle = new TestVehicle();
	//vehicle = new Gender();
	//vehicle = new LilPump();
	vehicle = new Kanye();

		/* xbox controller connection*/

	if (controller.IsConnected() == true)
	{
		std::cout << "plugged in " << std::endl;
	}

	// add test obstacles
	ObstacleManager::get()->addObstacle(Obstacle(10,10, 1));
	ObstacleManager::get()->addObstacle(Obstacle(10,-10, 1));
	ObstacleManager::get()->addObstacle(Obstacle(-10,10, 1));
	ObstacleManager::get()->addObstacle(Obstacle(-10,-10, 1));

	// add test goal
	GoalState g;
	g.x = 25;
	g.z = 0;
	goals.push_back(g);


	glutMainLoop();

	if (vehicle != NULL) {
		delete vehicle;
	}

	return 0;
}

void drawGoals()
{
	for (int i = 0; i < goals.size(); ++i) {
		GoalState goal = goals[i];

		glPushMatrix();
		glTranslatef(goal.x, 0, goal.z);
		glRotated(90, -1, 0, 0);
		static GLUquadric * quad = gluNewQuadric();

		// make first goal purple
		if (i == 0)
			glColor3f(1, .3, 1);
		else
			glColor3f(1, 1, 1);

		gluCylinder(quad, .5, .5, 10, 5, 1);
		glPopMatrix();
	}
}

void testDraw() {
	
}

void display() {
	frameCounter++;
	// -------------------------------------------------------------------------
	//  This method is the main draw routine. 
	// -------------------------------------------------------------------------

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if(Camera::get()->isPursuitMode() && vehicle != NULL) {
		double x = vehicle->getX(), y = vehicle->getY(), z = vehicle->getZ();
		double dx = cos(vehicle->getRotation() * 3.141592765 / 180.0);
		double dy = sin(vehicle->getRotation() * 3.141592765 / 180.0);
		Camera::get()->setDestPos(x + (-20 * dx), y + 15, z + (-20 * dy));
		Camera::get()->setDestDir(dx, -0.25, dy);
	}
	Camera::get()->updateLocation();
	Camera::get()->setLookAt();

	Ground::draw();
	
	// draw other vehicles
	for(std::map<int, Vehicle *>::iterator iter = otherVehicles.begin(); iter != otherVehicles.end(); ++iter) 
		iter->second->draw();

	// draw my vehicle
	if (vehicle != NULL) {
		vehicle->draw();

	}

	// draw obstacles
	ObstacleManager::get()->drawAll();

	// draw goals
	drawGoals();

	// draw HUD
	HUD::Draw();

	testDraw();

	glutSwapBuffers();
};

void reshape(int width, int height) {

	Camera::get()->setWindowDimensions(width, height);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
};

void remoteDriver(Vehicle * vehicle, double x, double z, double r, double speed_, double steering_)
{
	// filter 
	const double kSmoothingFactor = 0.5;
	vehicle->setX(vehicle->getX() * kSmoothingFactor + x * (1 - kSmoothingFactor));
	vehicle->setZ(vehicle->getZ() * kSmoothingFactor + z * (1 - kSmoothingFactor));

	vehicle->setRotation(r);
	vehicle->steering = steering_;
	vehicle->speed = speed_;
}

double getTime()
{
#if defined(WIN32)
	LARGE_INTEGER freqli;
	LARGE_INTEGER li;
	if(QueryPerformanceCounter(&li) && QueryPerformanceFrequency(&freqli)) {
		return double(li.QuadPart) / double(freqli.QuadPart);
	}
	else {
		static ULONGLONG start = GetTickCount64();
		return (GetTickCount64() - start) / 1000.0;
	}
#else
	struct timeval t;
	gettimeofday(&t, NULL);
	return t.tv_sec + (t.tv_usec / 1000000.0);
#endif
}

void idle() {

	if (KeyManager::get()->isAsciiKeyPressed('a')) {
		Camera::get()->strafeLeft();
	}

	if (KeyManager::get()->isAsciiKeyPressed('c')) {
		Camera::get()->strafeDown();
	}

	if (KeyManager::get()->isAsciiKeyPressed('d')) {
		Camera::get()->strafeRight();
	}

	if (KeyManager::get()->isAsciiKeyPressed('s')) {
		Camera::get()->moveBackward();
	}

	if (KeyManager::get()->isAsciiKeyPressed('w')) {
		Camera::get()->moveForward();
	}

	if (KeyManager::get()->isAsciiKeyPressed(' ')) {
		Camera::get()->strafeUp();
	}

	speed = 0;
	steering = 0;

	if (controller.IsConnected() == TRUE) {
		if (controller.PressedUpDpad())
		{
			std::cout << "^ ";
			speed = Vehicle::MAX_FORWARD_SPEED_MPS;
		}
		double percent = double(double(controller.LeftThumbLocation().GetY()) / 32768);
		speed = Vehicle::MAX_FORWARD_SPEED_MPS * percent;
		double steerpercent = double(double(controller.LeftThumbLocation().GetX()) / 32768);
		steering = Vehicle::MAX_LEFT_STEERING_DEGS * steerpercent;
	}
	else {
		if (KeyManager::get()->isSpecialKeyPressed(GLUT_KEY_LEFT)) {
			steering = Vehicle::MAX_LEFT_STEERING_DEGS * -1;
		}

		if (KeyManager::get()->isSpecialKeyPressed(GLUT_KEY_RIGHT)) {
			steering = Vehicle::MAX_RIGHT_STEERING_DEGS * -1;
		}

		if (KeyManager::get()->isSpecialKeyPressed(GLUT_KEY_UP)) {
			speed = Vehicle::MAX_FORWARD_SPEED_MPS;
		}

		if (KeyManager::get()->isSpecialKeyPressed(GLUT_KEY_DOWN)) {
			speed = Vehicle::MAX_BACKWARD_SPEED_MPS;
		}

	}
	
	
		// Xbox inputs
	

	// attempt to do data communications every 4 frames if we've created a local vehicle
	if(frameCounter % 4 == 0 && vehicle != NULL) {

		// if not connected, attempt to connect every 2 seconds
		if(!RemoteDataManager::IsConnected()) {
			if(frameCounter % 120 == 0) {
		
				// erase other vehicles
				for(std::map<int, Vehicle*>::iterator iter = otherVehicles.begin(); iter  != otherVehicles.end(); ++iter) {
					delete iter->second;
				}
				otherVehicles.clear();

				// uncomment this line to connect to the robotics server.
				RemoteDataManager::Connect("www.robotics.unsw.edu.au","18081");
				//RemoteDataManager::Connect("192.168.1.1", "18081");

				// on connect, let's tell the server what we look like
				if (RemoteDataManager::IsConnected()) {
					ObstacleManager::get()->removeAll();

					VehicleModel vm;
					

					//
					// student code goes here
					//
					//TestVehicle *cast = dynamic_cast<TestVehicle *> (vehicle);
					//vm = dynamic_cast<TestVehicle*>(vehicle)->getVM();
					//vm = dynamic_cast<Gender*>(vehicle)->getVM();
					//vm = dynamic_cast<LilPump*>(vehicle)->getVM();
					vm = dynamic_cast<Kanye*>(vehicle)->getVM();
					vm.remoteID = 0;
					RemoteDataManager::Write(GetVehicleModelStr(vm));
				}
			}
		}

		// if we're connected, send our vehicle state to the server
		if (RemoteDataManager::IsConnected()) {
			VehicleState vs;
			vs.remoteID = 0;
			vs.x = vehicle->getX();
			vs.z = vehicle->getZ();
			vs.rotation = vehicle->getRotation();
			vs.speed = vehicle->getSpeed();
			vs.steering = vehicle->getSteering();
			RemoteDataManager::Write(GetVehicleStateStr(vs));
		}

		// if we're still connected, receive and handle response messages from the server
		if (RemoteDataManager::IsConnected()) {
			std::vector<RemoteMessage> msgs = RemoteDataManager::Read();
			for(unsigned int i = 0; i < msgs.size(); i++ ) {

				RemoteMessage msg = msgs[i];
				//cout << msg.payload << endl;

				switch(msg.type) {
					// new models
					case 'M':
						{
							std::vector<VehicleModel> models = GetVehicleModels(msg.payload);
							for(unsigned int i = 0; i < models.size(); i++) {
								VehicleModel vm = models[i];
								
								// uncomment the line below to create remote vehicles
								otherVehicles[vm.remoteID] = new ImportedVehicle();
								Vehicle *other = otherVehicles[vm.remoteID]; //pointer at our end

								//cycling through all created 'import' class vehicles
								for (int k = 0; k < vm.shapes.size(); k++) {

									//for each vm, we check the shape list inside
									//based on the type, we make new shapes andd add those shapes to the 
									//list in *other 

									if ((vm.shapes[k]).type == RECTANGULAR_PRISM) { //if rect
										ShapeParameter *params = &vm.shapes[k].params; //pointer for neatness and readability
										//copy properties over by constructing (position is 0, 0, 0, for now)
										Shape *copy = new RectPrism(vm.shapes[k].xyz[0], vm.shapes[k].xyz[1], vm.shapes[k].xyz[2], params->rect.xlen, params->rect.ylen, params->rect.zlen, vm.shapes[k].rotation);
										//add the newly created shape to the shape list of the vehicle 'other' is pointing to
										copy->setColor(vm.shapes[k].rgb[0], vm.shapes[k].rgb[1], vm.shapes[k].rgb[2]);
										other->addShape(copy);
									}

									if ((vm.shapes[k]).type == TRIANGULAR_PRISM) {
										ShapeParameter *params = &vm.shapes[k].params;
										Shape *copy = new TriPrism(vm.shapes[k].xyz[0], vm.shapes[k].xyz[1], vm.shapes[k].xyz[2], params->tri.alen, params->tri.blen, params->tri.angle, params->tri.depth, vm.shapes[k].rotation);
										copy->setColor(vm.shapes[k].rgb[0], vm.shapes[k].rgb[1], vm.shapes[k].rgb[2]);
										other->addShape(copy);
									}

									if ((vm.shapes[k]).type == TRAPEZOIDAL_PRISM) {
										ShapeParameter *params = &vm.shapes[k].params;
										Shape *copy = new TrapPrism(vm.shapes[k].xyz[0], vm.shapes[k].xyz[1], vm.shapes[k].xyz[2], params->trap.alen, params->trap.blen, params->trap.height, params->trap.aoff, params->trap.depth, vm.shapes[k].rotation);
										copy->setColor(vm.shapes[k].rgb[0], vm.shapes[k].rgb[1], vm.shapes[k].rgb[2]);
										other->addShape(copy);
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
										//copy over
										other->addShape(copy);
									}

									//setting the position, colour and rotation of each shape
									//other->setPosition(vm.shapes[k].xyz[0], vm.shapes[k].xyz[1], vm.shapes[k].xyz[2]);
									//other->setColor(vm.shapes[k].rgb[0], vm.shapes[k].rgb[1], vm.shapes[k].rgb[2]);
									//other->setRotation(vm.shapes[k].rotation);
								}
							}
							break;
						}

					// vehicle states
					case 'S': 
						{
							std::vector<VehicleState> states = GetVehicleStates(msg.payload);
							for(unsigned int i = 0; i < states.size(); i++) {
								VehicleState vs = states[i];

								std::map<int, Vehicle*>::iterator iter = otherVehicles.find(vs.remoteID);
								if(iter != otherVehicles.end()) {
									Vehicle * veh = iter->second;
									remoteDriver(veh, vs.x, vs.z, vs.rotation, vs.speed, vs.steering);
								}
							}
							break;
						}

					// goal state
					case 'G':
						{
							goals = GetGoals(msg.payload);
							break;
						}

					// obstacle state
					case 'O':
						{
							std::vector<ObstacleState> obs = GetObstacles(msg.payload);
							for(unsigned int i = 0; i < obs.size(); i++) {
								Obstacle o(obs[i].x, obs[i].z, obs[i].radius);
								ObstacleManager::get()->addObstacle(o);
							}
							break;
						}

					// disconnect list
					case 'D':
						{
							std::vector<int> disconnectedIDs = GetVehicleDisconnects(msg.payload);
							for(unsigned int i = 0; i < disconnectedIDs.size(); i++) {
								int id = disconnectedIDs[i];
								std::map<int, Vehicle*>::iterator iter = otherVehicles.find(id);
								if(iter != otherVehicles.end()) {
									delete iter->second;
									otherVehicles.erase(iter);
								}
							}
							break;
						}

					// error message
					case 'E':
						{
							cerr << "Server error: " << msg.payload << endl;
							break;
						}

				}
			} 
		}
	}


	const float sleep_time_between_frames_in_seconds = 0.025;

	static double previousTime = getTime();
	const double currTime = getTime();
	const double elapsedTime = currTime - previousTime;
	previousTime = currTime;

	// do a simulation step
	if (vehicle != NULL) {
		vehicle->update(speed, steering, elapsedTime);
	}
	for(std::map<int, Vehicle*>::iterator iter = otherVehicles.begin(); iter  != otherVehicles.end(); ++iter) {
		iter->second->update(elapsedTime);
	}

	display();

#ifdef _WIN32 
	Sleep(sleep_time_between_frames_in_seconds * 1000);
#else
	usleep(sleep_time_between_frames_in_seconds * 1e6);
#endif
};

void keydown(unsigned char key, int x, int y) {

	// keys that will be held down for extended periods of time will be handled
	//   in the idle function
	KeyManager::get()->asciiKeyPressed(key);

	// keys that react ocne when pressed rather than need to be held down
	//   can be handles normally, like this...
	switch (key) {
	case 27: // ESC key
		exit(0);
		break;      
	case '0':
		Camera::get()->jumpToOrigin();
		break;
	case 'p':
		Camera::get()->togglePursuitMode();
		break;
	}

};

void keyup(unsigned char key, int x, int y) {
	KeyManager::get()->asciiKeyReleased(key);
};

void special_keydown(int keycode, int x, int y) {

	KeyManager::get()->specialKeyPressed(keycode);

};

void special_keyup(int keycode, int x, int y) {  
	KeyManager::get()->specialKeyReleased(keycode);  
};

void mouse(int button, int state, int x, int y) {

};

void dragged(int x, int y) {

	if (prev_mouse_x >= 0) {

		int dx = x - prev_mouse_x;
		int dy = y - prev_mouse_y;

		Camera::get()->mouseRotateCamera(dx, dy);
	}

	prev_mouse_x = x;
	prev_mouse_y = y;
};

void motion(int x, int y) {

	prev_mouse_x = x;
	prev_mouse_y = y;
};


