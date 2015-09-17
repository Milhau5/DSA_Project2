#version 330
//uniform vec4 tint; //from C++

//color passed from vertex shader
in vec4 colorFromVS;
void main()
{
	//gl_FragColor = vec4(1, 0, 0, 1);
	//gl_FragColor = tint;
	gl_FragColor = colorFromVS;
	//weak Photoshop "multiply" impression
	//gl_FragColor = colorFromVS * tint;
	
}
