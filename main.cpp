#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>  
#include <cstdio>  
#include <cstdlib>
#include <iostream>
#include <RENDERER.h>          
                                       
using namespace::std; 

int windowWidth;
int windowHeight;
RENDERER* renderer; 
  
void display()
{ 
  glClearColor(0,0,0,0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glDrawPixels(windowWidth, windowHeight, GL_RGB, GL_FLOAT, renderer->image());
 
  glutSwapBuffers();      
}    
////////////////////////////////////////////////////////////////////////////////// 
// Handles keyboard events  
//////////////////////////////////////////////////////////////////////////////////
void keyboard(unsigned char k, int x, int y) {   
  switch (k)
  {    
    // the escape key and 'q' quit the program
    case 'w':
      renderer->writePPM("output.ppm");
      break;
    case 27:
    case 'q':     
      delete renderer;
      exit(0); 
      break;   
  }
  glutPostRedisplay();
}  

//////////////////////////////////////////////////////////////////////////////////
// Called occasionally to see if anything's happening
//////////////////////////////////////////////////////////////////////////////////
void idle() {
  glutPostRedisplay();    
}        
 
//////////////////////////////////////////////////////////////////////////////////
// Called if a mouse button is pressed
//////////////////////////////////////////////////////////////////////////////////
void mouseButton(int button, int state, int x, int y) {   
}     

//////////////////////////////////////////////////////////////////////////////////
// Called if the mouse moves 
//////////////////////////////////////////////////////////////////////////////////
void mouseMotion(int x, int y) {      
} 

//main function!
int main(int argc, char* argv[]) 
{
  windowWidth = 600;
  windowHeight = 450;

  SCENE scene;
  scene.setup2();
  renderer = new RENDERER(windowWidth, windowHeight);
  renderer->render(scene);

  glutInit(&argc, argv);
  glutInitWindowSize(windowWidth, windowHeight);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("CMPSC 180, Homework 4");
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

  glutDisplayFunc(display); 
  glutMotionFunc(mouseMotion);
  glutMouseFunc(mouseButton);
  glutMotionFunc(mouseMotion);
  glutKeyboardFunc(keyboard);  
  // glutIdleFunc(idle); 
  glutMainLoop();

  return 0;  
}
