#pragma once
#include "PhysicsNode.h"

class MoveSpherePhy : public PhysicsNode
{
public:
	MoveSpherePhy(void);
	~MoveSpherePhy(void);
	MoveSpherePhy(Quaternion orientation, Vector3 position);

	void			lessG(float dt);

	virtual void	Update(float msec);

	//PhysicsSystem*	psys;

};

