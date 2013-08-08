# version 150 core

uniform sampler2D diffuseTex ;
uniform samplerCube cubeTex ;

uniform vec4 lightColour ;
uniform vec3 lightPos ;
uniform vec3 cameraPos ;
uniform float lightRadius ;

in Vertex {
	vec4 colour ;
	vec2 texCoord ;
	vec3 normal ;
	vec3 worldPos ;
} IN;

out vec4 gl_FragColor ;
void main ( void ) {
	vec4 diffuse = texture ( diffuseTex , IN. texCoord );
	vec3 incident = normalize (IN. worldPos - cameraPos );
	float dist = length ( lightPos - IN. worldPos );
	float atten = 1.0 - clamp ( dist / lightRadius , 0.0 , 1.0);


	float alpha = 1 - atten;
	atten = max(atten, 0.2);


	vec4 reflection = texture ( cubeTex ,
	reflect ( incident , normalize (IN. normal )));

	gl_FragColor = ( lightColour * diffuse * atten )*( diffuse + reflection * 0.3 );

	//gl_FragColor = diffuse;

	//gl_FragColor.rgb = vec3(reflect ( incident , normalize (IN. normal )));


	gl_FragColor.a = alpha * 0.4;

	gl_FragColor = diffuse ;

	//gl_FragColor.r = 1.0;

	//gl_FragColor.a = 1.0;
}