#include "SeaMap.h"
#include <math.h>
#include <time.h>


SeaMap::SeaMap(std::string name) {

	std::ifstream file(name.c_str(), ios::binary);
	if(!file) {
		return;
	}

	type = GL_TRIANGLES ;

	numVertices = RAW_WIDTH*RAW_HEIGHT;
	numIndices = (RAW_WIDTH-1)*(RAW_HEIGHT-1)*6;
	vertices = new Vector3[numVertices];
	textureCoords = new Vector2[numVertices];
	indices = new GLuint[numIndices];

	unsigned char* data = new unsigned char[numVertices];
	file.read((char*)data,numVertices*sizeof(unsigned char));
	file.close();

	// Adding some
	float Min = 1096162876;
	float Max = FLT_MIN;
	//Adding an rand with sin() - For waves.
	//srand((unsigned)time(0)); 
	//int r = rand();




	//int flag = 0;
	// Min = 0 --- Max = 66048
	for(int x = 0; x < RAW_WIDTH; ++x){
		for(int z = 0; z < RAW_HEIGHT; ++z) {
			int offset = (x * RAW_WIDTH) +z;
			//if(flag == 0){Min = offset;flag++;}


			float height =  data[offset] * HEIGHT_Y;

			//vertices[offset] = Vector3(x * HEIGHT_X, data[offset] * HEIGHT_Y, z * HEIGHT_Z);
			vertices[offset] = Vector3(x * HEIGHT_X, 100 * HEIGHT_Y + 100.0f, z * HEIGHT_Z);
			//cout << height << endl;
			//if(height < 90){
			textureCoords[offset] = Vector2(x * HEIGHTMAP_TEX_X, z * HEIGHTMAP_TEX_Z);


			//if (height > Max)
			//	Max = height;
			//
			//if (height < Min)	
			//	Min = height;
			//

		}

	}

	//cout << "MIN : " << Min << "\t MAX: " << Max << endl;

	delete data;

	numIndices = 0;

	for(int x = 0; x < RAW_WIDTH-1; ++x){
		for(int z =0; z < RAW_HEIGHT-1; ++z){
			int a = (x * (RAW_WIDTH)) + z;
			int b = ((x+1) * (RAW_WIDTH)) + z;
			int c = ((x+1) * (RAW_WIDTH)) + (z+1);
			int d = (x * (RAW_WIDTH)) + (z+1);

			indices[numIndices++] = c;
			indices[numIndices++] = b;
			indices[numIndices++] = a;

			indices[numIndices++] = a;
			indices[numIndices++] = d;
			indices[numIndices++] = c;

		}
	}
	//Tutorial 11 A - Lighting
	GenerateNormals();
	GenerateTangents();
	BufferData();
}




