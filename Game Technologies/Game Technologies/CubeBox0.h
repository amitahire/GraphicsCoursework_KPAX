#pragma once
#include "GameEntity.h"

class CubeBox0 : public GameEntity
{
public:
	CubeBox0(void);
	~CubeBox0(void);

	CubeBox0(SceneNode* s, PhysicsNode* p);

	virtual void Update(float msec);

	//PhysicsSystem*	psys;
	Plane*			pla;
};

