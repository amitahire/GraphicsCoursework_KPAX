#pragma once
#include "PhysicsNode.h"

class KPAXPhysicsNode : public PhysicsNode

{
public:
	KPAXPhysicsNode(void);
	~KPAXPhysicsNode(void);
	KPAXPhysicsNode(Quaternion orientation, Vector3 position);
	
	virtual void Update(float msec);
};

