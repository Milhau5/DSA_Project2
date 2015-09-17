/* DSA 1 - ICE 11a
Shader Helpers.cpp */
#include "shaderHelpers.h"
#include <iostream>
#include <fstream>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>

using namespace std;


/* Open the specified file in binary format,
load its text into a null-terminated array of characters
and return that array (reference week 10's File IO work).
If there is a problem opening the file, return 0.
*/
char* loadTextFile(const char* fileName)
{
	/* open in BINARY MODE */
	ifstream inFile(fileName, ios::binary);
	if (inFile.is_open())
	{
		// Handle file I/O here
		// Seek & get the length
		inFile.seekg(0, ios::end);
		int length = (int)inFile.tellg();

		// Seek back to the beginning
		inFile.seekg(0, ios::beg);

		// Make an array to hold the file
		char* fileContents = new char[length + 1];

		// Read the file & set null pointer
		inFile.read(fileContents, length);
		fileContents[length] = 0;

		// Done with the file
		inFile.close();

		//return array from this function
		return fileContents;
	}
	else { //couldn't open the file
		cout << "Couldn't open " << fileName << endl;
		return 0;
	}
}
GLuint loadShader(const char* fileName, GLenum shaderType)
{
	GLuint shader;
	const char* fileContents = loadTextFile(fileName);
	//double check contents in console
	if (fileContents != 0) {
		cout << fileContents << endl;
		//Create the shader
		shader = glCreateShader(shaderType);

		/* Set source code. Parameters
		1: Shader object index
		2 : How many strings make up the shader file code
		3 : Address of one or more strings(the code)
		4 : Array of string sizes – 0 means strings are null terminated
		*/
		glShaderSource(shader, 1, &fileContents, 0);

		//compilation may or may not succeed,
		//so we need to get shader info to confirm
		glCompileShader(shader);
		//clean up file contents either way
		delete[] fileContents;

		/* Get compilation results
		Param 1: the shader object index
		Param 2 : Which info to get ? GL_COMPILE_STATUS
		Param 3 : Address of integer(GLint) variable to store result
		*/
		GLint result;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
		if (result == GL_TRUE)
		{
			return shader; //YESSSSS
		}
		else
		{ //BOOOOO
			//Get length of compilation info log array
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &result);
			//Make a char array of that (result) length for log
			char* logArr = new char[result];

			/* Get The Log. Param 1: Shader object index
			Param 2 : Number of characters to retrieve
			Param 3 : Address of int variable where log length will be stored(use zero – we already have length)
			Param 4 : Character array to hold the log data
			*/
			glGetShaderInfoLog(shader, result, 0, logArr);
			//dump log to console
			cout << logArr << endl;
			delete[] logArr; //clean up
			//report failure back
			glDeleteShader(shader);
			return 0;
		}
	}
	else
	{
		cout << "Couldn't load " << fileName << endl;
		return 0;
	}
}
GLuint loadShaderProgram(const char* vertexFile, const char* fragmentFile)
{
	//Call loadShader( ), passing in the vertex shader file path
	// and GL_VERTEX_SHADER. Save the resulting shader index in a
	// GLuint.  If the result was zero, there was an error, so 
	// also return zero here.
	GLuint vshader = loadShader(vertexFile, GL_VERTEX_SHADER);
	if (vshader == 0) {
		cout << "vshader load failed\n";
		return 0;
	}
	//Call loadShader( ) again, passing in the fragment shader
	// file path and GL_FRAGMENT_SHADER. Save the resulting
	// shader index in another GLuint, and if it was zero also
	// return zero here.
	GLuint fshader = loadShader(fragmentFile, GL_FRAGMENT_SHADER);
	if (fshader == 0) {
		cout << "fshader load failed\n";
		return 0;
	}
	//Create a shader program with glCreateProgram(),
	GLuint sProgram = glCreateProgram();

	//then use glAttachShader() twice to attach both shaders you loaded.
	glAttachShader(sProgram, vshader);
	glAttachShader(sProgram, fshader);

	//Finally, link the program with glLinkProgram().
	glLinkProgram(sProgram);

	//Determine if the program linked correctly by calling
	// glGetProgramiv().If it linked, return the index of the shader program
	GLint result;
	glGetProgramiv(sProgram, GL_LINK_STATUS, &result);
	if (result == GL_TRUE)
	{
		return sProgram; //YESSSSSS
	}
	else
	{ //BOOOOO
		//Get length of compilation info log array
		glGetProgramiv(sProgram, GL_INFO_LOG_LENGTH, &result);
		//Make a char array of that (result) length for log
		char* logArr = new char[result];

		/* Get The Log. Param 1: sProgram object index
		Param 2 : Number of characters to retrieve
		Param 3 : Address of int variable where log length will be stored(use zero – we already have length)
		Param 4 : Character array to hold the log data
		*/
		glGetProgramInfoLog(sProgram, result, 0, logArr);
		//dump log to console
		cout << logArr << endl;
		delete[] logArr; //clean up
		//report failure back
		glDeleteProgram(sProgram);
		return 0;
	}

}

void setShaderVec2(GLuint index, const char* name, glm::vec2 vecToSend)
{

	GLint varIndex = glGetUniformLocation(index, name);
	//send to shader
	glProgramUniform2fv(index, varIndex, 1, &vecToSend[0]);

}

void setShaderMatrix(GLuint index, const char* name, glm::mat4 stuff)
{

	GLuint varIndex = glGetUniformLocation(index, name); //could be a GLint
	//send to shader
	glProgramUniformMatrix4fv(index, varIndex, 1, GL_FALSE, &stuff[0][0]);

}