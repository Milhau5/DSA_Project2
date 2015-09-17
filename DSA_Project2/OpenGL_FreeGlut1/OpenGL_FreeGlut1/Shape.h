#pragma once
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
class Shape
{
public:
	Shape(GLfloat* vert, int v, GLuint in);
	void Draw(glm::mat4 coords, float r, float g, float b);
	~Shape();
private: 
	GLuint vbo; //vertex buffer objects
	GLuint vao; //vertex array objects
	GLuint index; //holds the index
	GLint o; //offset
	GLint s; //scale
	float dx;
	float dy;
	int numVertices;
};

