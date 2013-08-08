#pragma once

#include "../../nclgl/SceneNode.h"
#include "../../nclgl/OBJMesh.h"

class Cube : public SceneNode
{

public:
	Cube(void);
	~Cube(void);
	virtual void Update(float msec);

	static void CreateCube() {
		OBJMesh* m	= new OBJMesh();
		m->LoadOBJMesh(MESHDIR"hellfiremissile.obj");
		
		cube = m;
	}

	static void DeleteCube()	{delete cube;}

protected:
	static Mesh*  cube;
	

};

