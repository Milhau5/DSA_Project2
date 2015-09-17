#pragma once
/* DSA 1 - ICE 11a
Shader Helpers.h */
// GLEW is "required" to use newer versions of OpenGL
#include <GL\glew.h>
// This example uses FreeGLUT for windowing
#include <GL\freeglut.h>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>

char* loadTextFile(const char* fileName);
GLuint loadShader(const char* fileName, GLenum shaderType);
GLuint loadShaderProgram(const char* vertexFile, const char* fragmentFile);
void setShaderVec2(GLuint index, const char* name, glm::vec2 vecToSend);
void setShaderMatrix(GLuint index, const char* name, glm::mat4 stuff);
