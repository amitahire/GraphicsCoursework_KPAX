#include "PhysicsNode.h"
#define DAMP_FACTOR 0.9995

PhysicsNode::PhysicsNode(void)	{
	target = NULL;
	isMissile		= false;
	isShip			= false;
	isHit			= false;
	m_HasHit		= false;
	isBackFire		= false;
}

PhysicsNode::PhysicsNode(Quaternion orientation, Vector3 position) {
	m_orientation	= orientation;
	m_position		= position;
	isPlane			= false;
	isMissile		= false;
	isShip			= false;
	isHit			= false;
	m_HasHit		= false;
	isBackFire		= false;

	yaw -= (Window::GetMouse()->GetRelativePosition().x);
	pitch -= (Window::GetMouse()->GetRelativePosition().y);
	pitch = min(pitch,90.0f);
	pitch = max(pitch,-90.0f);

	if(yaw < 0) {
		yaw += 360.0f;
	}
	if(yaw > 360.0f) {
		yaw -= 360.0f;
	}
}

PhysicsNode::~PhysicsNode(void)	{




}


void	PhysicsNode::Update(float msec) {


		if(target) {
			target->SetTransform(BuildTransform());
		}
}


void PhysicsNode::IntergrateGravity(float dt)
{
	
	//Gravity & Friction.
	m_linearVelocity = m_linearVelocity + (Vector3(0, -9.81, 0)) * dt;
	m_position = m_position + m_linearVelocity *dt; //* msec;

	//m_linearVelocity = m_linearVelocity * DAMP_FACTOR;

	if(m_position.y < 0)
	{
		m_position.y = 0;

	}

}


Matrix4		PhysicsNode::BuildTransform() {
	Matrix4 m = m_orientation.ToMatrix();

	m.SetPositionVector(m_position);

	return m;
}