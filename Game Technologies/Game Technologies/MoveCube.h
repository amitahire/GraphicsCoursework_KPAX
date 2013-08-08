#pragma once
#include "GameEntity.h"
class MoveCube : public GameEntity
{
public:
	MoveCube(void);

	MoveCube(SceneNode* s, PhysicsNode* p);
	~MoveCube(void);

	bool isCuboid;

	virtual void Update(float msec);

	PhysicsSystem*	psys;
	Plane*			pla;

};

