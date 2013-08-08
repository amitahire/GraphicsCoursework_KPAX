/******************************************************************************
Class:GameEntity
Implements:
Author:Rich Davison	<richard.davison4@newcastle.ac.uk> and Amit Ahire<amitahire@gmail.com>
Description: This is the base class for all of the objects in your game

-_-_-_-_-_-_-_,------,   
_-_-_-_-_-_-_-|   /\_/\   NYANYANYAN
-_-_-_-_-_-_-~|__( ^ .^) /
_-_-_-_-_-_-_-""  ""   

*//////////////////////////////////////////////////////////////////////////////

#pragma once

#include "../../nclgl/SceneNode.h"
#include "PhysicsNode.h"
#include "MoveSpherePhy.h"

class GameEntity	{
public:
	friend class GameClass;

	GameEntity(void);
	GameEntity(SceneNode* s, PhysicsNode* p);
	virtual ~GameEntity(void);

	virtual void	Update(float msec);

	SceneNode&		GetRenderNode()		{ return *renderNode;}
	PhysicsNode&	GetPhysicsNode()	{ return *physicsNode;}

	void			ConnectToSystems();
	void			DisconnectFromSystems();

protected:
	SceneNode*		renderNode;
	PhysicsNode*	physicsNode;
	MoveSpherePhy*	SpherePhy;
};

