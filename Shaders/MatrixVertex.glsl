#version 150 core

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

uniform mat4 modelMatrixCube;
uniform mat4 modelMatrixtri2;
uniform mat4 modelMatrixquad2;
uniform mat4 modelMatrixbigq;



in vec3 position;
in vec4 colour;

out Vertex {
	vec4 colour;
} OUT;

void main(void) {
	mat4 mvp		= projMatrix * viewMatrix * modelMatrix;
	// My code.
	mat4 mvpCube		= projMatrix * viewMatrix * modelMatrixCube;
	gl_Position		= mvp * vec4(position, 1.0);
	//gl_Position	= mvp * vec4(position, 1.0);
	OUT.colour		= colour;
}