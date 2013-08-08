#pragma once
#include "GameEntity.h"

class CubeBox1 : public GameEntity
{
public:
	CubeBox1(void);
	~CubeBox1(void);

	CubeBox1(SceneNode* s, PhysicsNode* p);

	virtual void Update(float msec);

	PhysicsSystem*	psys;
	Plane*			pla;
};

