#pragma once

#include "../../nclgl/SceneNode.h"
#include "../../nclgl/OBJMesh.h"



class CubeRobot : public SceneNode {
public:
	CubeRobot(void);
	~CubeRobot(void){};
	virtual void Update(float msec);

	static void CreateCube() {
		OBJMesh* m = new OBJMesh();
		m->LoadOBJMesh("../../Meshes/cube.obj");
		cube = m;
	}

	//static void CreateSphere() {
	//	OBJMesh* s = new OBJMesh();
	//	s->LoadOBJMesh("../../Meshes/sphere.obj");
	//	sphere2 = s;
	//}

	static void DeleteCube() {delete cube;}
	//static void DeleteSphere() {delete sphere2;}

	void MySphere();

protected:
	static Mesh*	cube;
	//static Mesh*	sphere2;

	SceneNode*		head;
	SceneNode*		leftArm;
	SceneNode*		rightArm;

};

