#include "RigidBody.h"


RigidBody::RigidBody(ShapeType a_shapeID, glm::vec2 a_position, 
	glm::vec2 a_velocity, float a_rotation, float a_mass) : PhysicsObject(a_shapeID)
{
	m_Position = a_position;
	m_Velocity = a_velocity;
	m_Rotation = a_rotation;
	m_Mass = a_mass;

}


void RigidBody::FixedUpdate(glm::vec2 a_gravity, float a_timeStep)
{
	ApplyForce(a_gravity * GetMass() * a_timeStep);
	m_Position += GetVelocity() * a_timeStep;
}

void RigidBody::ApplyForce(glm::vec2 a_force)
{
	m_Velocity += a_force / GetMass();
}

void RigidBody::ApplyForceToActor(RigidBody* a_actor2, glm::vec2 a_force)
{

	ApplyForce(-a_force);
	a_actor2->ApplyForce(a_force);
}
