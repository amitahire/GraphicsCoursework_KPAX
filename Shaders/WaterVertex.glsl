#version 150 core
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;
uniform mat4 textureMatrix;
uniform float timeWave;

in vec3 position;
in vec4 colour;
in vec3 normal;
in vec2 texCoord;

out Vertex{
vec4 colour;
vec2 texCoord;
vec3 normal;
vec3 worldPos;
}OUT;

void main( void ){

OUT.colour = colour;
OUT.texCoord = ( textureMatrix * vec4( texCoord , 0.0 , 1.0)).xy;

mat3 normalMatrix = transpose( inverse( mat3( modelMatrix )));

OUT.normal = normalize( normalMatrix * normalize( normal ));

vec3 wp = ( modelMatrix * vec4( position ,1)).xyz;

wp.y += 30*sin(0.01*(wp.x + wp.z) + timeWave) * cos(0.01*(wp.x + wp.z) + timeWave) * sin(0.01*(wp.x + wp.z) + timeWave) * cos(0.01*(wp.x + wp.z) + timeWave);

OUT.worldPos = wp;

gl_Position = ( projMatrix * viewMatrix ) *
vec4( wp, 1.0);
}