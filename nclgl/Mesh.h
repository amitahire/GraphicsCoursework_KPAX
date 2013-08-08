#pragma once
#include "OGLRenderer.h"

 enum MeshBuffer {
 VERTEX_BUFFER, COLOUR_BUFFER, TEXTURE_BUFFER, INDEX_BUFFER, NORMAL_BUFFER, TANGENT_BUFFER,  MAX_BUFFER
 };

 class Mesh {
 public :
	 Mesh ( void );
	 ~ Mesh ( void );

	 virtual void Draw ();
	 static Mesh * GenerateTriangle ();

	 static Mesh* GenerateQuad();

	 static Mesh* GenerateCube();

	 //static Mesh* triangle2();

	 //static Mesh* Quad2();

	 //static Mesh* BigQ();


	 //Adding Texture Components.
	 void SetTexture(GLuint tex)	{texture = tex;}
	 GLuint GetTexture()			{return texture;}

	 //Tutorial - 11B Bump Maps.
	 void	SetBumpMap(GLuint tex)	{bumpTexture = tex;}
	 GLuint GetBumpMap()			{return bumpTexture;}

protected :
	 void BufferData ();

	 GLuint arrayObject ;
	 GLuint bufferObject [ MAX_BUFFER ];
	 GLuint numVertices ;
	 GLuint type ;

	 //Tutorial 3 - Adding texture components.
	 GLuint texture;
	 Vector2* textureCoords;

	 Vector3 * vertices ;
	 Vector4 * colours ;

	 // Tutorial 8 - Adding bit of Index buffer.
	 GLuint	numIndices;
	 unsigned int* indices;

	 //Tutorial 11 A - Lighting.
	 void GenerateNormals();
	 Vector3* normal;

	 //Tutorial 11B Bump Maps
	 void GenerateTangents();
	 Vector3 GenerateTangent(const Vector3 &a, const Vector3 &b, const Vector3 &c,
							const Vector2 &ta, const Vector2 &tb, const Vector2 &tc);

	 Vector3*	tangents;
	 GLuint bumpTexture;



 };