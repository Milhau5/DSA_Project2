#include "Entity.h"
#include "shaderHelpers.h" 

using namespace std;
using namespace glm;



Entity::Entity()
{

}


Entity::Entity(Shape* bob)
{

	bill = bob;

	currentPos = vec3(0, 0, 0);
	scaler = vec3(0.5, 0.5, 0.5);
	rotAxis = vec3(0, 0, 1); //2D shape rotates around Z-axis for propter rotation
	position = vec3(0, 0, 0);
	velocity = vec3(0, 0, 0);

}


void Entity::Update()
{
	
	//get dt
	int currentTime = glutGet(GLUT_ELAPSED_TIME);
	dt = currentTime - prevFrameTime; //why was dt a float? Doesn't matter, it's also a class property now
	float dtScaled = dt * 0.01f;
	prevFrameTime = currentTime; //save for next frame

	float k = 5;
	float damp = 0.95f;
	float mass = 2;
	vec3 displacement = position - mousePos; //currentPos <-> position, switch if there's a problem and see if it fixes it
	vec3 springForce = (-k) * displacement;
	//
	springForce -= (damp * velocity);
	acceleration = springForce / mass;

	velocity += springForce * dtScaled;
	vec3 jamesFranco = displacement + (velocity * dtScaled);

	//position = currentPos + (velocity * currentTime) + (0.5f * acceleration * currentTime * currentTime);

	//currentPos.x += dt * 0.0001f;
	scaler.x += 0.000001f;
	rotAmount += 0.1f;

	worldMatrix = (scale(scaler)) * (translate(jamesFranco)) * (rotate(rotAmount, rotAxis));

}



void Entity::Draw()
{

	//just call "shape->Draw(___);
	bill->Draw(worldMatrix, 1, 0, 1);
}

void Entity::shakeIt(int x, int y)
{

	//The calculations are based on window size
	mousePos.x = -(((x / (float)glutGet(GLUT_WINDOW_WIDTH)) * 2.0f) - 1.0f);
	mousePos.y = ((y / (float)glutGet(GLUT_WINDOW_HEIGHT)) * 2.0f) - 1.0f;

}

void Entity::keySpecial(int key, int x, int y)
{
	//get dt
	int currentTime = glutGet(GLUT_ELAPSED_TIME);
	dt = currentTime - prevFrameTime; //why was dt a float? Doesn't matter, it's also a class property now
	float dtScaled = dt * 0.01f;
	prevFrameTime = currentTime; //save for next frame
	
	//for use with glutSpecialFunc() in Source.cpp
	if (key == GLUT_KEY_LEFT)
	{
		currentPos.x -= dt * 0.0001f;
	}
	if (key == GLUT_KEY_RIGHT)
	{
		currentPos.x += dt * 0.0001f;
	}

	//update matrix with this info
	worldMatrix = (scale(scaler)) * (translate(currentPos)) * (rotate(0.0f, rotAxis));

}


void Entity::Shrink()
{
	currentPos = vec3(-1, 0.8, 0);
	
	scaler.x -= 0.000001f;
	scaler.y -= 0.000001f;
	
	//will just incrementally grow
	worldMatrix = (scale(scaler)) * (translate(currentPos)) * (rotate(0.0f, rotAxis));

	

}


Entity::~Entity()
{
}
