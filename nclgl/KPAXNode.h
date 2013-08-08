#pragma once

#include "../../nclgl/SceneNode.h"
#include "../../nclgl/OBJMesh.h"



class KPAXNode : public SceneNode {
public:
	KPAXNode(void);
	~KPAXNode(void){};
	virtual void Update(float msec);

	static void DeployShips() {

		OBJMesh* MS = new OBJMesh(); // MS = MotherShip :p
		MS->LoadOBJMesh(MESHDIR"Spaceship-B.obj");
		MotherShip	= MS;

		//OBJMesh* cube = new OBJMesh();
		//cube->LoadOBJMesh("../../Meshes/cube.obj");
		//fume = cube;


	}

	static void DeleteMotherShip()		{delete MotherShip;}
	static void		SetPos(Vector3 p)	{pos = p;}
	static void		GetPos();
	float f_track;

protected:
	static Mesh*	MotherShip;
//	static Mesh*	fume;

	static Vector3			pos;
	SceneNode*		helperShip1;
	SceneNode*		helperShip2;
	SceneNode*		helperShip3;
	SceneNode*		helperShip4;

	//SceneNode*		lg1;
	//SceneNode*		lg2;
	//SceneNode*		lg3;



	//SceneNode*		helper1;
	//SceneNode*		helper2;

};

