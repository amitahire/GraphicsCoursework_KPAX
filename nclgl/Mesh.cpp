#include "Mesh.h"

Mesh :: Mesh ( void ) {
	for( int i = 0; i < MAX_BUFFER ; ++i) {
		bufferObject [i] = 0;
	}
	glGenVertexArrays (1, &arrayObject );
//	cout << "TEST:" << arrayObject << endl;


	numVertices = 0;
	vertices = NULL ;
	colours = NULL ;
	type = GL_TRIANGLES ; //GL_TRIANGLE_STRIP

	//Adding Texture component.
	texture			= 0;
	textureCoords	= NULL;

	// Tutorial 8 - Index buffer.
	indices			= NULL;
	numIndices		=0;

	//Tutorial 11 A - Lighting.
	normal = NULL;

	//TUT-11B
	tangents		= NULL;
	bumpTexture		= 0;

}

Mesh ::~ Mesh ( void ) {
	glDeleteVertexArrays (1, &arrayObject );
	glDeleteBuffers ( MAX_BUFFER , bufferObject );
	delete [] vertices ;
	delete [] colours ;

	//Deleting Texture components.
	glDeleteTextures(1,&texture);
	delete[] textureCoords;

	// Tutorial 8 - Index buffer.
	delete[] indices;

	//Tutorial 11 A - Lighting.
	delete[] normal;
	

	//TUT 11 B
	delete[] tangents;
//	glDeleteTextures(1, &bumpTexture); -- TODO - search bumpTex.



}

Mesh * Mesh :: GenerateTriangle () {

	Mesh *m = new Mesh ();
	m-> numVertices = 4;
	m-> vertices = new Vector3 [m-> numVertices ];

	//m-> vertices [0] = Vector3 (0.0f, 0.5f, 0.0f);
	//m-> vertices [1] = Vector3 (0.5f, -0.5f, 0.0f);
	//m-> vertices [2] = Vector3 ( -0.5f, -0.5f, 0.0f);
	//m->vertices[3] = Vector3( -0.5f, 0.5f, 0.0f);

	//
	m-> vertices [0] = Vector3 (0.5f, 0.5f, 0.0f);
	m-> vertices [1] = Vector3 (-0.5f, 0.5f, 0.0f);
	m-> vertices [2] = Vector3 ( 0.5f, -0.5f, 0.0f);
	m->vertices[3] = Vector3( -0.5f, -0.5f, 0.0f);
	//
	// Full screen co-ordinates.
	/*m-> vertices [0] = Vector3 ( -1.0f , -1.0f, 0.0f);
	m-> vertices [1] = Vector3 ( -1.0f, 1.0f, 0.0f);
	m-> vertices [2] = Vector3 ( 1.0f , -1.0f, 0.0f);
	m-> vertices [3] = Vector3 ( 1.0f, 1.0f, 0.0f);*/
	//

	//Texture components.
	m->textureCoords	= new Vector2[m->numVertices];
	m->textureCoords[0]	= Vector2(0.0f,0.0f);
	m->textureCoords[1] = Vector2(1.0f, 0.0f);
	m->textureCoords[2] = Vector2(0.0f,1.0f);
	m->textureCoords[3] = Vector2(1.0f,1.0f);

	/*
	m->textureCoords[0]	= Vector2(0.0f,0.0f);
	m->textureCoords[1] = Vector2(10.0f, 0.0f);
	m->textureCoords[2] = Vector2(0.0f,10.0f);
	m->textureCoords[3] = Vector2(10.0f,10.0f);
	*/

	m-> colours = new Vector4 [m->numVertices ];

	m-> colours[0] = Vector4 (1.0f, 0.0f, 0.0f ,1.0f);
	m-> colours[1] = Vector4 (0.0f, 1.0f, 0.0f ,1.0f);
	m-> colours[2] = Vector4 (1.0f, 0.0f, 0.0f ,1.0f);
	m-> colours[3] = Vector4(1.0f, 1.0f, 1.0f, 1.0f);

	m-> BufferData ();
	return m;
}

Mesh* Mesh::GenerateCube(){

	Mesh* m				= new Mesh();
	m->numVertices		=36;
	m->type				=GL_TRIANGLES;

	m->vertices			= new Vector3[m->numVertices];
	m->colours			= new Vector4[m->numVertices];
	m->textureCoords	= new Vector2[m->numVertices];

	m->vertices[0]		= Vector3 (1.0f, 1.0f, -1.0f);
	m->vertices[1]		= Vector3 (-1.0f, 1.0f, -1.0f);
	m->vertices[2]		= Vector3 (1.0f, -1.0f, -1.0f);
	m->vertices[3]		= Vector3 (-1.0f, 1.0f, -1.0f);
	m->vertices[4]		= Vector3 (1.0f, -1.0f, -1.0f);
	m->vertices[5]		= Vector3 (-1.0f, -1.0f, -1.0f);

	m->vertices[6]			= Vector3 (-1.0f, 1.0f, -1.0f);
	m->vertices[7]			= Vector3 (-1.0f, 1.0f, 1.0f);
	m->vertices[8]			= Vector3 (-1.0f, -1.0f, -1.0f);
	m->vertices[9]			= Vector3 (-1.0f, 1.0f, 1.0f);
	m->vertices[10]			= Vector3 (-1.0f, -1.0f, -1.0f);
	m->vertices[11]			= Vector3 (-1.0f, -1.0f, 1.0f);

	m->vertices[12]			= Vector3 (-1.0f, 1.0f, 1.0f);
	m->vertices[13]			= Vector3 (1.0f, 1.0f, 1.0f);
	m->vertices[14]			= Vector3 (-1.0f, -1.0f, 1.0f);
	m->vertices[15]			= Vector3 (1.0f, 1.0f, 1.0f);
	m->vertices[16]			= Vector3 (-1.0f, -1.0f, 1.0f);
	m->vertices[17]			= Vector3 (1.0f, -1.0f, 1.0f);

	m->vertices[18]			= Vector3 (1.0f, 1.0f, 1.0f);
	m->vertices[19]			= Vector3 (1.0f, 1.0f, -1.0f);
	m->vertices[20]			= Vector3 (1.0f, -1.0f, 1.0f);
	m->vertices[21]			= Vector3 (1.0f, 1.0f, -1.0f);
	m->vertices[22]			= Vector3 (1.0f, -1.0f, 1.0f);
	m->vertices[23]			= Vector3 (1.0f, -1.0f, -1.0f);

	m->vertices[24]			= Vector3 (1.0f, 1.0f, 1.0f);
	m->vertices[25]			= Vector3 (-1.0f, 1.0f, 1.0f);
	m->vertices[26]			= Vector3 (1.0f, 1.0f, -1.0f);
	m->vertices[27]			= Vector3 (-1.0f, 1.0f, 1.0f);
	m->vertices[28]			= Vector3 (1.0f, 1.0f, -1.0f);
	m->vertices[29]			= Vector3 (-1.0f, 1.0f, -1.0f);

	m->vertices[30]			= Vector3 (1.0f, -1.0f, -1.0f);
	m->vertices[31]			= Vector3 (-1.0f, -1.0f, -1.0f);
	m->vertices[32]			= Vector3 (1.0f, -1.0f, 1.0f);
	m->vertices[33]			= Vector3 (-1.0f, -1.0f, -1.0f);
	m->vertices[34]			= Vector3 (1.0f, -1.0f, 1.0f);
	m->vertices[35]			= Vector3 (-1.0f, -1.0f, 1.0f);


	////Defining vertices
	//m->vertices[0]		= Vector3 (-1.0f, -1.0f, -1.0f); //fbl
	//m->vertices[1]		= Vector3 (-1.0f, -1.0f, 1.0f);
	//m->vertices[2]		= Vector3 (-1.0f, 1.0f, 1.0f);
	//m->vertices[3]		= Vector3 (1.0f, 1.0f, -1.0f); //ftr
	//m->vertices[4]		= Vector3 (-1.0f, -1.0f, -1.0f); //fbl
	//m->vertices[5]		= Vector3 (-1.0f, 1.0f, -1.0f); //ftl

	// //1.0f,-1.0f, 1.0f, 
 // //  -1.0f,-1.0f,-1.0f,
 // //  1.0f,-1.0f,-1.0f,
 // //  1.0f, 1.0f,-1.0f,
 // //  1.0f,-1.0f,-1.0f,
 // //  -1.0f,-1.0f,-1.0f,

	//m->vertices[6]		= Vector3 (1.0f, -1.0f, 1.0f);
	//m->vertices[7]		= Vector3 (-1.0f, -1.0f, -1.0f); //fbl
	//m->vertices[8]		= Vector3 (1.0f, -1.0f, -1.0f); //fbr
	//m->vertices[9]		= Vector3 (1.0f, 1.0f, -1.0f);//ftr
	//m->vertices[10]		= Vector3 (1.0f, -1.0f, -1.0f);//fbr
	//m->vertices[11]		= Vector3 (-1.0f, -1.0f, -1.0f); //fbl

	////-1.0f,-1.0f,-1.0f,
 ////   -1.0f, 1.0f, 1.0f,
 ////   -1.0f, 1.0f,-1.0f,
 ////   1.0f,-1.0f, 1.0f,
 ////   -1.0f,-1.0f, 1.0f,
 ////   -1.0f,-1.0f,-1.0f,

	//m->vertices[12]		= Vector3 (-1.0f, -1.0f, -1.0f); //fbl
	//m->vertices[13]		= Vector3 (-1.0f, 1.0f, 1.0f);
	//m->vertices[14]		= Vector3 (-1.0f, 1.0f, -1.0f); //ftl
	//m->vertices[15]		= Vector3 (1.0f, -1.0f, 1.0f);
	//m->vertices[16]		= Vector3 (-1.0f, -1.0f, 1.0f);
	//m->vertices[17]		= Vector3 (-1.0f, -1.0f, -1.0f); //fbl

	// //-1.0f, 1.0f, 1.0f,
 // //  -1.0f,-1.0f, 1.0f,
 // //  1.0f,-1.0f, 1.0f,
 // //  1.0f, 1.0f, 1.0f,
 // //  1.0f,-1.0f,-1.0f,
 // //  1.0f, 1.0f,-1.0f,


	//m->vertices[18]		= Vector3 (-1.0f, 1.0f, 1.0f);
	//m->vertices[19]		= Vector3 (-1.0f, -1.0f, 1.0f);
	//m->vertices[20]		= Vector3 (1.0f, -1.0f, 1.0f);
	//m->vertices[21]		= Vector3 (1.0f, 1.0f, 1.0f);
	//m->vertices[22]		= Vector3 (1.0f, -1.0f, -1.0f);//fbr
	//m->vertices[23]		= Vector3 (1.0f, 1.0f, -1.0f);//ftr

	///*1.0f,-1.0f,-1.0f,
 //   1.0f, 1.0f, 1.0f,
 //   1.0f,-1.0f, 1.0f,
 //   1.0f, 1.0f, 1.0f,
 //   1.0f, 1.0f,-1.0f,
 //   -1.0f, 1.0f,-1.0f,*/

	//m->vertices[24]		= Vector3 (1.0f, -1.0f, -1.0f);//fbr
	//m->vertices[25]		= Vector3 (1.0f, 1.0f, 1.0f);
	//m->vertices[26]		= Vector3 (1.0f, -1.0f, 1.0f);
	//m->vertices[27]		= Vector3 (1.0f, 1.0f, 1.0f);
	//m->vertices[28]		= Vector3 (1.0f, 1.0f, -1.0f); //ftr
	//m->vertices[29]		= Vector3 (-1.0f, 1.0f, -1.0f); //ftl

	//   // 1.0f, 1.0f, 1.0f,
 //   //-1.0f, 1.0f,-1.0f,
 //   //-1.0f, 1.0f, 1.0f,
 //   //1.0f, 1.0f, 1.0f,
 //   //-1.0f, 1.0f, 1.0f,
 //   //1.0f,-1.0f, 1.0f

	//m->vertices[30]		= Vector3 (1.0f, 1.0f, 1.0f);
	//m->vertices[31]		= Vector3 (-1.0f, 1.0f, -1.0f); //ftl
	//m->vertices[32]		= Vector3 (-1.0f, 1.0f, 1.0f);
	//m->vertices[33]		= Vector3 (1.0f, 1.0f, 1.0f);
	//m->vertices[34]		= Vector3 (-1.0f, 1.0f, 1.0f);
	//m->vertices[35]		= Vector3 (1.0f, -1.0f, 1.0f);
	
	for ( int i = 0; i < 36; ++i){
		m->colours[i]		= Vector4(0.0f, 0.0f, 0.0f, 1.0f);
	}

	//Testing colour.
	m->colours[0]		= Vector4(1.0f, 0.0f, 0.0f, 1.0f);
	m->colours[3]		= Vector4(1.0f, 0.0f, 0.0f, 1.0f);
	m->colours[4]		= Vector4(1.0f, 0.0f, 0.0f, 1.0f);
	m->colours[5]		= Vector4(1.0f, 0.0f, 0.0f, 1.0f);

	m->colours[7]		= Vector4(1.0f, 0.0f, 0.0f, 1.0f);
	m->colours[8]		= Vector4(1.0f, 0.0f, 0.0f, 1.0f);
	m->colours[9]		= Vector4(1.0f, 0.0f, 0.0f, 1.0f);
	m->colours[10]		= Vector4(1.0f, 0.0f, 0.0f, 1.0f);

	m->colours[11]		= Vector4(1.0f, 0.0f, 0.0f, 1.0f);
	m->colours[12]		= Vector4(1.0f, 0.0f, 0.0f, 1.0f);
	m->colours[14]		= Vector4(1.0f, 0.0f, 0.0f, 1.0f);
	m->colours[17]		= Vector4(1.0f, 0.0f, 0.0f, 1.0f);

	m->colours[22]		= Vector4(1.0f, 0.0f, 0.0f, 1.0f);
	m->colours[23]		= Vector4(1.0f, 0.0f, 0.0f, 1.0f);
	m->colours[24]		= Vector4(1.0f, 0.0f, 0.0f, 1.0f);
	m->colours[28]		= Vector4(1.0f, 0.0f, 0.0f, 1.0f);


	m->colours[29]		= Vector4(1.0f, 0.0f, 0.0f, 1.0f);
	m->colours[31]		= Vector4(1.0f, 0.0f, 0.0f, 1.0f);

	// 0 3 4 5 7 8 9 10 11 12 14 17 22 23 24 28 29 31

	//Texture.

	m-> textureCoords [0] = Vector2 (0.0f, 1.0f);
	m-> textureCoords [1] = Vector2 (0.0f, 0.0f);
	m-> textureCoords [2] = Vector2 (1.0f, 1.0f);
	m-> textureCoords [3] = Vector2 (1.0f, 0.0f);
	//m-> textureCoords [4] = Vector2 (1.0f, 1.0f);
	//m-> textureCoords [5] = Vector2 (1.0f, 0.0f);


	m->BufferData();

	return m;


}

//Mesh* Mesh::triangle2() {
//
//	Mesh* m				= new Mesh();
//	m->numVertices		= 3;
//	m->type				= GL_TRIANGLES;
//
//	m->vertices			= new Vector3[m->numVertices];
//	m->vertices[0]		= Vector3 (-0.5f, 0.5f, 0.0f);
//	m->vertices[1]		= Vector3 (-0.5f, -0.5f, 0.0f);
//	m->vertices[2]		= Vector3 (0.75f, -0.5f, 0.0f);
//
//	//colours
//	m->colours			= new Vector4[m->numVertices];
//	for( int i = 0; i < 3; ++i){
//		m->colours[i]		= Vector4 (1.0f, 1.0f, 1.0f, 1.0f);
//	}
//
//}
//
//Mesh* Mesh::Quad2() {
//
//	Mesh* m				= new Mesh();
//	m->numVertices		= 4;
//	m->type				= GL_QUADS;
//
//	m->vertices			= new Vector3[m->numVertices];
//	m->vertices[0]		= Vector3 (0.5f, 0.5f, 0.0f);
//	m->vertices[1]		= Vector3 (-0.5f, 0.5f, 0.0f);
//	m->vertices[2]		= Vector3 (-0.5f, -0.5f, 0.0f);
//	m->vertices[3]		= Vector3 (0.5f, -0.5f, 0.0f);
//
//	m->colours			= new Vector4[m->numVertices];
//	for( int i = 0; i < 4; ++i){
//		m->colours[i]		= Vector4 (1.0f, 1.0f, 0.0f, 1.0f);
//	}
//
//}
//
//Mesh* Mesh::BigQ() {
//
//	Mesh* m				= new Mesh();
//	m->numVertices		= 7;
//	m->type				= GL_TRIANGLE_STRIP;
//
//	m->vertices			= new Vector3[m->numVertices];
//	m->vertices[0]		= Vector3 (-0.5f, 0.5f, 0.0f);
//	m->vertices[1]		= Vector3 (-0.5f, -0.5f, 0.0f);
//	m->vertices[2]		= Vector3 (0.5f, -0.5f, 0.0f);
//
//	//
//	m->vertices[3]		= Vector3 (0.5f, -0.5f, 0.5f);
//	m->vertices[4]		= Vector3 (-0.5f, 0.5f, 0.5f);
//	//m->vertices[5]		= Vector3 (-0.5f, 0.5f, 0.0f);
//	m->vertices[5]		= Vector3 (-0.5f, 0.5f, 0.5f);
//
//
//	m->vertices[6]		= Vector3 (-0.5f, 0.5f, 0.0f);
//	m->vertices[7]		= Vector3 (-0.5f, -0.5f, 0.0f);
//
//	m->colours			= new Vector4[m->numVertices];
//	for( int i = 0; i < 7; ++i){
//		m->colours[i]		= Vector4 (1.0f, 0.0f, 1.0f, 1.0f);
//	}
//
//}

Mesh* Mesh::GenerateQuad(){

	Mesh* m				= new Mesh();
	m->numVertices		= 4;
	m->type				= GL_TRIANGLE_STRIP;

	m->vertices			= new Vector3[m->numVertices];
	m-> textureCoords = new Vector2 [m-> numVertices ];
	m-> colours = new Vector4 [m-> numVertices ];
	m-> normal			= new Vector3[m->numVertices];
	m-> tangents		= new Vector3[m->numVertices];

	m-> vertices [0] = Vector3 ( -1.0f , -1.0f, 0.0f);
	m-> vertices [1] = Vector3 ( -1.0f, 1.0f, 0.0f);
	m-> vertices [2] = Vector3 ( 1.0f , -1.0f, 0.0f);
	m-> vertices [3] = Vector3 ( 1.0f, 1.0f, 0.0f);

	m-> textureCoords [0] = Vector2 (0.0f, 1.0f);
	m-> textureCoords [1] = Vector2 (0.0f, 0.0f);
	m-> textureCoords [2] = Vector2 (1.0f, 1.0f);
	m-> textureCoords [3] = Vector2 (1.0f, 0.0f);

	for (int i = 0; i < 4; ++i) {
		m-> colours [i] = Vector4 (1.0f, 1.0f ,1.0f ,1.0f);
		m-> normal [i] = Vector3 (0.0f, 0.0f, -1.0f);
		m-> tangents[i] = Vector3(1.0f, 0.0f, 0.0f);

	}
	m-> BufferData ();
	return m;
}


void Mesh :: BufferData () {
	glBindVertexArray ( arrayObject );
	glGenBuffers (1, & bufferObject [ VERTEX_BUFFER ]);
	glBindBuffer ( GL_ARRAY_BUFFER , bufferObject [ VERTEX_BUFFER ]);
	glBufferData ( GL_ARRAY_BUFFER , numVertices * sizeof ( Vector3 ), vertices ,GL_STATIC_DRAW );
	glVertexAttribPointer( VERTEX_BUFFER , 3, GL_FLOAT , GL_FALSE , 0, 0);
	glEnableVertexAttribArray ( VERTEX_BUFFER );


	if ( colours ) { // Just in case the data has no colour attribute ...
		glGenBuffers (1, & bufferObject [ COLOUR_BUFFER ]);
		glBindBuffer ( GL_ARRAY_BUFFER , bufferObject [ COLOUR_BUFFER ]);
		glBufferData ( GL_ARRAY_BUFFER , numVertices * sizeof ( Vector4 ), colours , GL_STATIC_DRAW );
		glVertexAttribPointer ( COLOUR_BUFFER , 4, GL_FLOAT , GL_FALSE ,0 ,0);
		glEnableVertexAttribArray ( COLOUR_BUFFER );
	}

	//Tutorial 3 - Adding for Texture.
	if(textureCoords) {
		glGenBuffers(1, &bufferObject[TEXTURE_BUFFER]);
		glBindBuffer( GL_ARRAY_BUFFER, bufferObject[TEXTURE_BUFFER]);
		glBufferData( GL_ARRAY_BUFFER, numVertices *sizeof(Vector2), textureCoords, GL_STATIC_DRAW);
		glVertexAttribPointer(TEXTURE_BUFFER, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(TEXTURE_BUFFER);

	}

	// Tutorial 8 - Index buffer.
	if(indices){
		glGenBuffers(1, &bufferObject[INDEX_BUFFER]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferObject[INDEX_BUFFER]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices*sizeof(GLuint), indices, GL_STATIC_DRAW);

	}

	//Tutorial 11 A - Lighting (Normals)
	if(normal){
		glGenBuffers(1, &bufferObject[NORMAL_BUFFER]);
		glBindBuffer(GL_ARRAY_BUFFER, bufferObject[NORMAL_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, numVertices*sizeof(Vector3), normal, GL_STATIC_DRAW);
		glVertexAttribPointer(NORMAL_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(NORMAL_BUFFER);
	}

	//TUT - 11 B
	if(tangents){
		glGenBuffers(1, &bufferObject[TANGENT_BUFFER]);
		glBindBuffer(GL_ARRAY_BUFFER, bufferObject[TANGENT_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, numVertices*sizeof(Vector3), tangents, GL_STATIC_DRAW);
		glVertexAttribPointer(TANGENT_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(TANGENT_BUFFER);
	}



	glBindVertexArray (0);
}

void Mesh :: Draw () {

	//Binding texture to texture units.
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, bumpTexture);

	glBindVertexArray ( arrayObject );
	//type = GL_TRIANGLES;
	// Tutorial 8 - Index buffer.
	if(bufferObject[INDEX_BUFFER]) {
		glDrawElements(type, numIndices, GL_UNSIGNED_INT, 0);
	}
	else{
		glDrawArrays (type , 0, numVertices );

	}
	glBindVertexArray (0);

}


void Mesh::GenerateNormals(){

	if(!normal) {
		normal = new Vector3[numVertices];
	}

	for(GLuint i = 0; i < numVertices; ++i) {
		normal[i] = Vector3();
	}
	//Generate per-vertex normals.
	if(indices) {
		for(GLuint i = 0; i < numIndices; i += 3){
			unsigned int a = indices[i];
			unsigned int b = indices[i+1];
			unsigned int c = indices[i+2];

			Vector3 n = Vector3::Cross((vertices[b] - vertices[a]),(vertices[c] - vertices[a]));

			normal[a]	+= n;
			normal[b]	+= n;
			normal[c]	+= n;

		}
	}
	else{ //Its's just a list of triangles, so generate face normals.
		for(GLuint i = 0; i < numVertices; i+=3){
			Vector3 &a	= vertices[i];
			Vector3 &b	= vertices[i+2];
			Vector3 &c	= vertices[i+3];

			Vector3 n = Vector3::Cross(b-a,c-a);

			normal[i]	= n;
			normal[i+2]	= n;
			normal[i+3] = n;

		}
	}

	for(GLuint i = 0; i < numVertices; ++i) {
		normal[i].Normalise();
	}

}


void Mesh::GenerateTangents(){
	if(!tangents){
		tangents = new Vector3[numVertices];
	}

	for(GLuint i =0; i < numVertices; ++i){
		tangents[i] = Vector3();
	}

	if(indices){

		for(GLuint i =0; i < numIndices; i+=3){
			int a = indices[i];
			int b = indices[i+1];
			int c = indices[i+2];

			Vector3 tangent = GenerateTangent(vertices[a], vertices[b], vertices[c], textureCoords[a], textureCoords[b], textureCoords[c]);

			tangents[a] += tangent;
			tangents[b] += tangent;
			tangents[c] += tangent;

		}
	}
	else{
		for(GLuint i =0; i < numVertices; i+=3){

			Vector3 tangent = GenerateTangent(vertices[i], vertices[i+1], vertices[i+2], textureCoords[i], textureCoords[i+1], textureCoords[i+2]);

			tangents[i]		+=tangent;
			tangents[i+1]	+=tangent;
			tangents[i+2]	+=tangent;

		}
	}

	for(GLuint i = 0; i < numVertices; ++i){
		tangents[i].Normalise();
	}
}


Vector3 Mesh::GenerateTangent(const Vector3 &a, const Vector3 &b, const Vector3 &c, const Vector2 &ta, const Vector2 &tb, const Vector2 &tc) {
	Vector2 coord1 = tb-ta;
	Vector2 coord2 = tc-ta;

	Vector3 vertex1 = b-a;
	Vector3 vertex2 = c-a;

	Vector3 axis = Vector3(vertex1 * coord2.y - vertex2 * coord1.y);

	float factor = 1.0f/(coord1.x * coord2.y - coord2.x * coord1.y);

	return axis * factor;

}
