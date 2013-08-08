#pragma once;

#include <string>
#include <iostream>
#include <fstream>

#include "../nclgl/Mesh.h"


#define RAW_WIDTH 257
#define RAW_HEIGHT 257

#define HEIGHT_X 16.0f
#define HEIGHT_Z 16.0f
#define HEIGHT_Y 1.25f
#define HEIGHTMAP_TEX_X 1.0f/16.0f
#define HEIGHTMAP_TEX_Z 1.0f/16.0f

class SeaMap : public Mesh {

public:
	SeaMap(std::string name);
	~SeaMap(void){};

};


