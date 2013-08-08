#pragma once
#include "GameEntity.h"
#include "PhysicsSystem.h"

class MoveSphere : public GameEntity
{
public:
	MoveSphere(void);
	~MoveSphere(void);

	MoveSphere(SceneNode* s, MoveSpherePhy* p);
	//bool isSphere;


	virtual void Update(float msec);
	
};

