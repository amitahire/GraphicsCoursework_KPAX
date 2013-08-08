#include "Plane.h"

Plane::Plane(const Vector3 &normal, float distnace, bool normalise) {
	if(normalise) {
		float lenght			= sqrt(Vector3::Dot(normal,normal));


		this->normal			= normal	/	lenght;
		this->distance			= distnace	/	lenght;

	}
	else{

		this->normal			= normal;
		this->distance			= distance;

	}
}

bool Plane::SphereInPlane(const Vector3 &position, float radius) const {

	if(Vector3::Dot(position, normal)+distance <= -radius) {
		return false;
	}

	return true;

}

bool Plane::SphereInPlane(const Vector3 &position, float radius, c_Sphere1 &s0, CollisionData_c* collData) const {


	float seperation = Vector3::Dot(position,normal) + distance;
	if ( seperation <= -radius) {
		return false;
	}

	if(collData) {
		collData->m_penetration = radius - seperation;
		collData->m_normal = normal;
		collData->m_point = s0.m_pos - normal * collData->m_penetration;
	}

	return true;

}

