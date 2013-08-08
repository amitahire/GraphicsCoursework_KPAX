#pragma once
#include "Vector3.h"

//c_Sphere is required for SphereInPlane - but defined twice - think. 
//Renaming for now - but see about it later - Plane.h - c_Sphere
class c_Sphere1 {
public:
	c_Sphere1(){};
	c_Sphere1(const Vector3& p, float r){
		m_pos = p;
		m_radius = r;
	}
	Vector3 m_pos;
	float m_radius;
};

class CollisionData_c{
public:
	Vector3		m_point;
	Vector3		m_normal;
	float		m_penetration;
};



class Plane {
public:
	Plane(void){};
	Plane(const Vector3 &normal, float distance, bool normalise= false);
	~Plane(void){};

	c_Sphere1			sp;
	CollisionData_c		cd;

	void SetNormal(const Vector3 &normal)		{this->normal = normal;}
	Vector3 GetNormal() const					{return normal;}

	void SetDistance(float dist)				{distance = dist;}
	float GetDistance()	const					{return distance;}

	bool SphereInPlane(const Vector3 &position, float radius) const;
	bool SphereInPlane(const Vector3 &position, float radius,  c_Sphere1 &s0, CollisionData_c* collData = NULL)	const;
	
	/////////////New Set//////////////


protected:
	Vector3 normal;
	float distance;

};
