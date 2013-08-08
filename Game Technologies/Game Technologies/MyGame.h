/******************************************************************************
Class:MyGame
Implements:GameEntity
Author:Rich Davison	<richard.davison4@newcastle.ac.uk> and Amit Ahire <amitahire@gmail.com>
Description: This is an example of a derived game class - all of your game 
specific things will go here. 


-_-_-_-_-_-_-_,------,   
_-_-_-_-_-_-_-|   /\_/\   NYANYANYAN
-_-_-_-_-_-_-~|__( ^ .^) /
_-_-_-_-_-_-_-""  ""   

*//////////////////////////////////////////////////////////////////////////////



#pragma once
#include "GameEntity.h"
#include "GameClass.h"
#include "../nclgl/Camera.h"
#include "../nclgl/CubeRobot.h"
#include "FirstProjectile.h"
#include "MoveCube.h"
#include "MoveSphere.h"
#include "Cube.h"
#include "CubeBox0.h"
#include "CubeBox1.h"
#include "MoveSpherePhy.h"
#include "KPAXPhysicsNode.h"
#include "../../nclgl/HeightMap.h"
#include "../../nclgl/KPAXNode.h"


class MyGame : public GameClass	{
public:
	MyGame();
	~MyGame(void);

	virtual void UpdateGame(float msec);

protected:
	GameEntity*		BuildRobotEntity();

	GameEntity*		BuildCubeEntity(float size);

	GameEntity*		BuildCube2(float size);

	GameEntity*		BuildSphereEntity(float radius);

	GameEntity*		BuildQuadEntity(float size);
	
	GameEntity*		BuildQuadEntity2(float size);


	GameEntity*		DrawMyAnything();
	GameEntity*		ShotProjectile(float msec);

	GameEntity*		BuildHeightMap();
	GameEntity*		BuildSpaceShip(Vector3 pos);

	GameEntity*		BackFire(Vector3 pos);




	MoveCube*	cubeObj;
	//MoveCube*	cubeObj2;							// Check if using.

	CubeBox0*	cB0;
	CubeBox1*	cB1;

	MoveSphere*	sphereObj;
	//MoveSphere*	spObj[10];

	Mesh*	heightMap2;
	Vector3		position;

	Mesh* cube;
	Mesh* quad;
	Mesh* sphere;
	Mesh* sphere2;
	Mesh* missile1;
};

