/* DSA1 10a OpenGL Buffers */
#include <iostream>
#include "shaderHelpers.h"
#include "Shape.h"
#include "Entity.h"
using namespace std;
using namespace glm;

// GLEW is "required" to use newer versions of OpenGL
#include <GL\glew.h>

// This example uses FreeGLUT for windowing
#include <GL\freeglut.h>

#include <GL\glut.h>

//GLM
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>

// Global constants for data size
const GLsizei numVertices = 3;
const GLsizei moreVertices = 6; 
const GLsizei hexVert = 7;
const GLsizei numComponents = numVertices * 6; // x & y, r, g, b, & a
const GLsizei numInTheBum = moreVertices * 6;
const GLsizei lastPair = hexVert * 6;

const GLsizei someNumber = 12;

//shapes
Shape* triangle;
Shape* square;
Shape* hexagon;

//Entities
Entity* mover;
Entity* karl;
Entity* bigguy;
//Entity* drop;

GLuint sProgram;

// Other various initialization logic, so we don't bloat the main method
void init()
{
	sProgram = loadShaderProgram("Shaders/vertexShader.glsl", "Shaders/fragmentShader.glsl");
	
	// Just for testing - remove later!
	cout << "Initializing" << endl; 

	//load a shader PROGRAM
	//cout << "shader? " << loadShader("Shaders/vertexShader.glsl", GL_VERTEX_SHADER) << endl;
	//If the return value from loadShaderProgram( ) is not zero, then
	//everything was loaded, compiled and linked correctly.
	if (sProgram != 0)
	{
		//Call glUseProgram( ) to tell OpenGL to activate your shaders.
		glUseProgram(sProgram);
	}


	GLfloat vertices[numComponents] =
	{	// x	y	r	g	b	a
		0.0f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
		0.7f, -0.7f, 0.0f, 0.0f, 1.0f, 1.0f
	};

	GLfloat verticesTwo[numInTheBum] =
	{	// x	y	r	g	b	a
		-0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, //Top-left
		0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, //Top-right
		0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f, //Bottom-right
		
		//0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f //Bottom-right, do we need to repeat this?
		-0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, //Bottom-left
		//-0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, //Top-left, do we need to repeat this?

	};

	GLfloat verticesFlat[lastPair] = {
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,    //center
		-0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,   // left top
		0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,  // right top
		1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,  // right
		0.5f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f,  // right bottom (notice sign)
		-0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,  // left bottom
		-1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f  // left
	};



	triangle = new Shape(vertices, numVertices, sProgram);

	square = new Shape(verticesTwo, 4, sProgram); 

	hexagon = new Shape(verticesFlat, hexVert, sProgram);

	mover = new Entity(triangle);

	karl = new Entity(square);

	bigguy = new Entity(hexagon);

	//drop = new Entity(triangle);

	// Cornflower blue – For you XNA fans
	glClearColor(0.392f, 0.584f, 0.929f, 1.0f);

}

// The "Update" part of our game loop that handles movement and rotation
void update()
{
	
     // Tells GLUT to redraw the window the next time
	// through the game loop
	glutPostRedisplay();

	mover->Update();

	bigguy->Shrink();

	//drop->Up();

}

// Basically the "Draw" part of our game loop
void draw()
{
	//Just call this for every moving thing ("mover" is name of an Entity):
	//mover->Draw();

	// Clear the "color" portion of the screen
	glClear(GL_COLOR_BUFFER_BIT);

	//triangle->Draw(0.4, 0.5, 1, 2);
	//triangle->Draw(0, -0.5, 0.5, 0.5);
	//square->Draw(0.1, 0.1, 1, 1); 
	//square->Draw(0.2, 0.3, 0.5, 0.5);
	mover->Draw();
	karl->Draw();
	bigguy->Draw();
	//drop->Draw();
	
	//Tell OpenGL to process queued commands
	glFlush();

}

void mouseMove(int x, int y)
{

	//call entity shake
	mover->shakeIt(x, y);

}

void pressKeys(int button, int a, int b)
{

	//Will this work, ladies and gentlemen?
	karl->keySpecial(button, a, b);

}

// Main - with command line stuff, since glut wants it
int main(int argc, char** argv)
{
	// Set up open gl via glut
	glutInit(&argc, argv);						// Pass args to glut
	glutInitDisplayMode(GLUT_RGBA);				// Set up the window display mode
	glutInitWindowSize(800, 600);				// Set up the window size
	glutInitContextVersion(4, 3);				// Which version of OpenGL to use (4.3 is what the book covers)
	glutInitContextProfile(GLUT_CORE_PROFILE);	// Core since we don't need backwards compatibility
	glutCreateWindow("Based on a Dream I Had");		// Create the window with a specific title
	
	// Initialize GLEW and exit if it fails
	glewExperimental = GL_TRUE;
	if(glewInit() != GLEW_OK) // GLEW_OK is a #define (which equals 0)
	{
		return -1;
	}

	// Handle any other initialization logic
	init();

	// Tell glut which functions to call as part
	// of the main loop
	glutIdleFunc(update);
	glutDisplayFunc(draw);
	glutPassiveMotionFunc(mouseMove); //mouse movement
	glutSpecialFunc(pressKeys); //key input

	// Run the main loop
	glutMainLoop();


	
}