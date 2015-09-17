#include "Shape.h"
#include "shaderHelpers.h" 
#include <iostream>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>

using namespace std;
using namespace glm;


Shape::Shape(GLfloat* vert, int v, GLuint in)
{
	// Local constants for data size
	numVertices = v;

	index = in;
	// Generate & bind VAO index
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	// Now that a VAO is bound, it will
	// remember which buffers become bound
	// and which vertex attribs are enabled

	//generate vertex buffer index
	glGenBuffers(1, &vbo);
	//set this vertex buffer as active
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//Copies specified data into currently bound buffer
	glBufferData(
		GL_ARRAY_BUFFER,  // Which target
		sizeof(GL_FLOAT) * (numVertices * 6), // How many bytes to copy (sizeof(float) * numComponents of Array
		vert,	      // The actual data
		GL_STATIC_DRAW);  // Usage hint to OpenGL

	//Set up the attribute to describe COMPLEX buffer layout
	// 1 of 2 is Position
	glVertexAttribPointer(
		0,        // Attribute index (0 because first)
		2,        // Number of components (x & y)
		GL_FLOAT, // Type of data
		GL_FALSE, // Don't normalize this data
		sizeof(GL_FLOAT) * 6,  // Stride (bytes between attributes)
		0);       // Offset to 1st element of attribute

	//Set up the attribute to describe COMPLEX buffer layout
	// 2 of 2 is Color
	glVertexAttribPointer(
		1,        // Attribute index (1 because second)
		4,        // Number of components (r, g, b, a)
		GL_FLOAT, // Type of data
		GL_FALSE, // Don't normalize this data
		sizeof(GL_FLOAT) * 6,  // Stride (move over six spaces)
		(void*)(sizeof(GL_FLOAT) * 2) );       // get x and y from previous item

	

	//Enable the POSITION attribute we just created
	glEnableVertexAttribArray(0); // 0 is the index

	//Enable the COLOR attribute we just created
	glEnableVertexAttribArray(1); // 1 is the index
	
	//Get and save offest and scale in the shader program
	o = glGetUniformLocation(in, "offset");
	//glProgramUniform2f(in, o, 0, 0);
	
	s = glGetUniformLocation(in, "scale");
	//glProgramUniform2f(in, s, 1, 1); //dx, dy
	
}

void Shape::Draw(glm::mat4 coords, float r, float g, float b) //float x, float y, float xscale, float yscale
{

		//glProgramUniform2f(index, o, x, y);
		//glProgramUniform2f(index, s, xscale, yscale);
		setShaderMatrix(index, "worldMatrix", coords); //IS NOW TIME TO USE SHADER MATRIX

		//Then simply bind the vao and draw it
		//glBindVertexArray(o, &vao);
		glBindVertexArray(vao);

		//Issue an OpenGL draw command:
		glDrawArrays(
			GL_TRIANGLE_FAN, // Rendering mode
			0,            // Offset to the first vertex
			numVertices); // How many vertices to draw
	
	//----------------------------------------------------------------------
		if (numVertices > 4)
		{

			//Issue an OpenGL draw command:
			glDrawArrays(
				GL_POLYGON, // Rendering mode
				0,            // Offset to the first vertex
				numVertices); // How many vertices to draw

		}

}


Shape::~Shape()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
}
