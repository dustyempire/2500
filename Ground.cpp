<<<<<<< HEAD
#include "Ground.hpp"
=======
#include "Ground.hpp"
>>>>>>> 25209d78e463649de116709b156b6a4ad60004ec

#ifdef __APPLE__
	#include <OpenGL/gl.h>
#elif defined(WIN32)
	#include <Windows.h>
	#include <GL/gl.h>
#else
	#include <GL/gl.h>
<<<<<<< HEAD
#endif


void Ground::draw() {
  
  glBegin(GL_LINES);
  
  for (int i = -1000; i <= 1000; i += 25) {

    glColor3f(i == 0 ? 0.0f : 0.5f, 0.5f, 0.5f);

    glVertex3f(i, 0, -1000);
    glVertex3f(i, 0, 1000);

    glVertex3f(-1000, 0, i);
    glVertex3f(1000, 0, i);
  }
  
  glEnd();

};

=======
#endif


void Ground::draw() {
  
  glBegin(GL_LINES);
  
  for (int i = -1000; i <= 1000; i += 25) {

    glColor3f(i == 0 ? 0.0f : 0.5f, 0.5f, 0.5f);

    glVertex3f(i, 0, -1000);
    glVertex3f(i, 0, 1000);

    glVertex3f(-1000, 0, i);
    glVertex3f(1000, 0, i);
  }
  
  glEnd();

};

>>>>>>> 25209d78e463649de116709b156b6a4ad60004ec
