/******************************************************************************
Class:PhysicsSystem
Implements: Physics Engine Class.
Author:Rich Davison	<richard.davison4@newcastle.ac.uk> and Amit Ahire <amitahire@gmail.com>


-_-_-_-_-_-_-_,------,   
_-_-_-_-_-_-_-|   /\_/\   NYANYANYAN
-_-_-_-_-_-_-~|__( ^ .^) /
_-_-_-_-_-_-_-""  ""   

*//////////////////////////////////////////////////////////////////////////////


#pragma once

#include "PhysicsNode.h"
#include "../../nclgl/Vector3.h"
#include <vector>


using std::vector;


class c_Sphere {
public:
	c_Sphere(){};
	c_Sphere(const Vector3& p, float r) //Position and radius.
	{
		m_pos = p;
		m_radius = r;
	}
	Vector3 m_pos;
	float m_radius;

	//More elements.#
	float	m_mass;
	Vector3 m_c;			//Centre.
	Matrix4	m_invInertia;	
	Vector3 m_linVelocity;
	Vector3 m_angVelocity;

};

class Line_c{
public:
	Line_c(const Vector3& p0, const Vector3& p1){
		m_p0 = p0;
		m_p1 = p1;
	}
	Vector3 m_p0;
	Vector3 m_p1;
};


class cubeAABB {
public:
	cubeAABB(){}; //Temp.
	cubeAABB(const Vector3& p, const Vector3& dimen){
		pos = p;
		halfdims = dimen / 2;
	}
	Vector3 pos;
	Vector3	halfdims;

	float	m_mass;
	
	Vector3 m_c;			//Centre.
	Matrix4	m_invInertia;	
	Vector3 m_linVelocity;
	Vector3 m_angVelocity;


};

class CollisionData {
public:
	Vector3		m_point;
	Vector3		m_normal;
	float		m_penetration;
};


class PhysicsSystem	{
public:
	friend class GameClass;
	friend class PhysicsNode;
	Plane*			pla;
	c_Sphere		cs0;
	c_Sphere		cs1;
	CollisionData	cd;
	cubeAABB		cAB0;
	cubeAABB		cAB1;
	//For Impulse.
	cubeAABB		c0;
	cubeAABB		c1;


	void		Update(float msec);

	void		BroadPhaseCollisions();
	void		NarrowPhaseCollisions();
	void		DeleteCollided();

	//Statics
	static void Initialise() {
		instance = new PhysicsSystem();
	}

	static void Destroy() {
		delete instance;
	}

	static PhysicsSystem& GetPhysicsSystem() {
		return *instance;
	}

	void	AddNode(PhysicsNode* n);

	void	RemoveNode(PhysicsNode* n);

	static inline Vector3 Transform(const Vector3 v, const Matrix4 m){ return m * v; }

	//An array to delete the things off.
	PhysicsNode*	delArray[8];


protected:
	PhysicsSystem(void);
	~PhysicsSystem(void);

	bool SphereSphereCollision(const c_Sphere &s0, const c_Sphere &s1, CollisionData *collisionData = NULL) const;
	bool AABBCollision(const cubeAABB &cube0, const cubeAABB &cube1) const;

	bool SphereInPlane(const Vector3 &position, float radius, c_Sphere &s0, CollisionData* collData) const;

	//bool SphereAABBCollision(const CollisionSphere &sphere, const CollisionAABB &cube, CollisionData *collisionData = NULL) const; //Research!!!! :-)

	bool PointInConvexPolygon(const Vector3 testPosition, Vector3 * convexShapePoints, int numPointsL) const;

	bool LineLineIntersection(const Line_c& l0, const Line_c& l1, float* t0 = NULL, float* t1 = NULL, float* t2 = NULL);

	bool InsideConcaveShape(const Vector3* shapePoints, const int numPoints, const Vector3& testPoint);

	//Collision Method - Impulse Method.

	//Was static. Why?
	void AddCollisionImpulse( PhysicsNode* c0, PhysicsNode* c1, const CollisionData& cd);

	void AddCollImpulse2( PhysicsNode* c0, const CollisionData& cd);

	
	float	LengthSq(Vector3 d) const		{
			float x = d.x;
			float y = d.y;
			float z = d.z;
			return (x*x)+(y*y)+(z*z);	
	} 
	//Statics
	static PhysicsSystem* instance;

	vector<PhysicsNode*> allNodes;
};

