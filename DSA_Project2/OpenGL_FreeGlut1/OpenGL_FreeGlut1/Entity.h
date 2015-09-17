#pragma once
/* DSA 1 - ICE 11a
Shader Helpers.h */
// GLEW is "required" to use newer versions of OpenGL
#include <GL\glew.h>
// This example uses FreeGLUT for windowing
#include <GL\freeglut.h>
//stuff for GLM
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>

//Need this anyway if the constructor is taking a Shape parameter
#include "Shape.h"


class Entity
{
public:
	Entity();
	Entity(Shape* bob);
	void Update();
	void Draw();
	void shakeIt(int x, int y); //mouse movement
	void keySpecial(int key, int x, int y); //keyboard input
	void Shrink(); //this will shrink a shape, just because
	~Entity();
private: 
	int storePos; //in case we need to store position
	int prevFrameTime;
	glm::vec3 currentPos;
	glm::vec3 scaler; //scale, essentially
	glm::vec3 rotAxis;
	glm::vec3 acceleration;
	float rotAmount; //rotation amount
	glm::vec3 position;
	glm::vec3 velocity;
	//
	glm::vec3 mousePos; //mouse position
	glm::mat4 worldMatrix;
	Shape* bill;
	int dt;
    
	//making some new stuff just because
	float equationTime;
	glm::vec3 gravity;
	glm::vec3 posEquation;
	glm::vec3 startVelocity;
	//we have currentPos, or startPosition
	//we have velocity
	glm::vec3 posPerFrame;
};

