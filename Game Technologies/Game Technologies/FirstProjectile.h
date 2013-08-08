#pragma once

#include "../../nclgl/SceneNode.h"
#include "../../nclgl/OBJMesh.h"



class FirstProjectile : public SceneNode {
public:
	FirstProjectile(void);
	~FirstProjectile(void);
	virtual void Update(float msec);

	static void CreateCube() {
		OBJMesh* m = new OBJMesh();
		m->LoadOBJMesh(MESHDIR"sphere.obj");
		cube = m;
	}

	static void DeleteCube() {delete cube;}
	//static void DeleteSphere() {delete sphere2;}

	void MySphere();

protected:
	static Mesh*	cube;
	//static Mesh*	sphere2;

	SceneNode*		head;


};

