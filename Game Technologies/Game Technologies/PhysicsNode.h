/******************************************************************************
Class:PhysicsNode
Implements:
Author:Rich Davison	<richard.davison4@newcastle.ac.uk> and Amit Ahire <amitahire@gmail.com>
Description: This class represents the physical properties of game's
entities 

-_-_-_-_-_-_-_,------,   
_-_-_-_-_-_-_-|   /\_/\   NYANYANYAN
-_-_-_-_-_-_-~|__( ^ .^) /
_-_-_-_-_-_-_-""  ""   

*//////////////////////////////////////////////////////////////////////////////


#pragma once

#include "../../nclgl/Quaternion.h"
#include "../../nclgl/Vector3.h"
#include "../../nclgl/Matrix4.h"
#include "../../nclgl/SceneNode.h"
#include "../../nclgl/Plane.h"
//
#include "PhysicsSystem.h"

class PhysicsSystem;

class PhysicsNode	{
public:
	PhysicsNode(void);
	PhysicsNode(Quaternion orientation, Vector3 position);
	~PhysicsNode(void);

	void				SetPosition(Vector3 pos)			{ m_position = pos;}
	Vector3				GetPosition()						{ return m_position;}

	void				SetLinearVelocity(Vector3 l_vel)	{ m_linearVelocity = l_vel;} 
	Vector3				GetLinearVelocity()					{ return m_linearVelocity;}
	
	void				SetInverseMass(float m)				{ m_invMass = m; }
	float				GetInverseMass()					{ return m_invMass;}

	void				SetOrientation(Quaternion q)		{ m_orientation = q;}
	Quaternion			GetOrientation()					{ return m_orientation;}


	void				SetAngularVelocity(Vector3 a_vel)	{ m_angularVelocity = a_vel; }
	Vector3				GetAngularVelocity()				{ return m_angularVelocity;}

	Matrix4				BuildTransform();

	virtual void		Update(float msec);

	void				SetTarget(SceneNode *s)				{ target = s;}
	void				IntergrateGravity(float dt);

	void				AddForce(Vector3 f) 				{ m_force	+= f;}
	Vector3				GetForce()							{ return m_force;}

	void				AddTorque(Vector3 t)				{ m_torque	+= t;}
	Vector3				GetTorque()							{ return m_torque;}

	//SPHERE
	void				SetSphereRadius(float r)			{ radius = r;}
	float				GetSphereRadius()					{return radius;}

	Matrix4				GetInvInertia()						{ return m_invInertia;}
	
	// A New Plane.
	float				GetYaw()							{ return yaw; }
	float				GetPitch()							{ return pitch;}

	Vector3				GetDimension()						{ return m_dimension;}
	void				SetDimension(Vector3 d)				{ m_dimension = d; }
	
	bool				isPlane;
	bool				isMissile;
	bool				isShip;
	bool				isHit;
	bool				m_HasHit;
	bool				isBackFire;
	

	SceneNode*		target;

protected:
	//<---------LINEAR-------------->
	Vector3		m_position;
	Vector3		m_linearVelocity;
	Vector3		m_force;
	Vector3		m_acce;
	float		m_invMass;

	//<----------ANGULAR--------------->
	Quaternion  m_orientation;
	Vector3		m_angularVelocity;
	Vector3		m_angularAcce; 
	Vector3		m_torque;
	Matrix4     m_invInertia;

	bool isLinear;
	bool isSphere;
	bool isCuboid;



	 
	PhysicsSystem*	psys;
	Plane*			pla;

	// Change it and add it above.
	float radius;
	float yaw;
	float pitch;

	Vector3		m_dimension;
};

