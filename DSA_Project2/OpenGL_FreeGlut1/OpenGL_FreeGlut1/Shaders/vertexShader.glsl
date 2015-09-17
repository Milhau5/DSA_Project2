#version 330
//position of a vertex
layout (location = 0) in vec2 position;
//color of a vertex
layout (location = 1) in vec4 vcolor;

//color info sent to fragment shader
out vec4 colorFromVS;

//two more variables
//uniform vec2 offset;
uniform mat4 worldMatrix;
uniform vec2 scale;

void main()
{
	//gl_Position = vec4(position, 0, 1);
        //gl_Position = vec4(position + offset, 0, 1);
        gl_Position = worldMatrix * vec4(position, 0, 1);
	//pass color to the fragment shader
	colorFromVS = vcolor;
}
