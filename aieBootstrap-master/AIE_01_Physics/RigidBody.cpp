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
	m_Position += GetVelocity() * a_timeStep;
	ApplyForce(a_gravity * GetMass() * a_timeStep, glm::vec2(0,0));

	m_Rotation += m_anglurVelocity * a_timeStep;
}

void RigidBody::ResolveCollision(RigidBody* a_actor2)
{
	glm::vec2 normal = glm::normalize(a_actor2->GetPosition() - m_Position);
	glm::vec2 relativeVelocity = a_actor2->GetVelocity() - m_Velocity;

	//the surface boncyness???
	float elasticity = 1;
	//impulse magnitude
	float j = glm::dot(-(1 + elasticity) * relativeVelocity, normal) /
		((1 / m_Mass) + (1 / a_actor2->GetMass()));

	glm::vec2 force = normal * j;



}

void RigidBody::ApplyForce(glm::vec2 a_force, glm::vec2 a_contact)
{
	m_Velocity += a_force / GetMass();
	m_anglurVelocity += (a_force.y * a_contact.x - a_force.x * a_contact.y) / GetMoment();

}

//void RigidBody::ApplyForceToActor(RigidBody* a_actor2, glm::vec2 a_force, glm::vec2 a_contact)
//{
//
//	ApplyForce(-a_force, a_contact);
//	a_actor2->ApplyForce(a_force, a_contact);
//}

void RigidBody::SetMass(const float m_mass)
{
	m_Mass = m_mass;

}

float RigidBody::GetKineticEnergy()
{
	float totalEnergy = (m_Mass * glm::dot(m_Velocity, m_Velocity)) / 2;

	return totalEnergy;
}
