#include "RigidBody.h"
#include <glm/glm.hpp>


RigidBody::RigidBody(ShapeType a_shapeID, glm::vec2 a_position, 
	glm::vec2 a_velocity, float a_rotation, float a_mass) : PhysicsObject(a_shapeID)
{
	m_Position = a_position;
	m_Velocity = a_velocity;
	m_Rotation = a_rotation;
	m_Mass = a_mass;
	m_elasticity = 1;
	m_anglurVelocity = 0;
}


void RigidBody::FixedUpdate(glm::vec2 a_gravity, float a_timeStep)
{
	m_Position += GetVelocity() * a_timeStep;
	ApplyForce(a_gravity * GetMass() * a_timeStep, glm::vec2(0,0));

	m_Rotation += m_anglurVelocity * a_timeStep;
}

void RigidBody::ResolveCollision(RigidBody* a_otherActor, glm::vec2 a_contact,
	glm::vec2* a_collisionNormal, float a_pen)
{
	//we need to find the vector between their 
	//centers or use the provided directional force

	glm::vec2 normal = glm::normalize(a_collisionNormal ? *a_collisionNormal :
		a_otherActor->GetPosition() - m_Position);

	//get the pependiculer vector to the collision normal
	glm::vec2 perpendicularColNorm(normal.y, -normal.x);
	float radiusThis = glm::dot(a_contact - m_Position, -perpendicularColNorm);
	float radiusOther = glm::dot(a_contact - a_otherActor->GetPosition(), perpendicularColNorm);

	//the velocity of the contact points
	float cp_VelThis = glm::dot(m_Velocity, normal) - radiusThis * m_anglurVelocity;
	float cp_VelOther = glm::dot(a_otherActor->GetVelocity(), normal) +
		radiusOther * a_otherActor->GetAngularVelocity();

	if (cp_VelThis > cp_VelOther) //they are moving closer
	{
		//this will calculate the effective mass at the contact point for each objet....
		//ie. how much the contact point will move due to the forces applied.
		float massThis = 1.0f / (1.0f / m_Mass + glm::pow(radiusThis, 2.0f) / m_moment);
		float massOther = 1.0f / (1.0f / a_otherActor->GetMass() +
			glm::pow(radiusOther, 2.0f) / a_otherActor->GetMoment());

		float elasticity = (m_elasticity + a_otherActor->GetElasticity()) / 2.0f;

		glm::vec2 impact = (1.0f + elasticity) * massThis * massOther / (massThis + massOther) *
			(cp_VelThis - cp_VelOther) * normal;

		ApplyForce(-impact, a_contact - m_Position);

		a_otherActor->ApplyForce(impact, a_contact - a_otherActor->GetPosition());
	}
}

void RigidBody::ApplyForce(glm::vec2 a_force, glm::vec2 a_contact)
{
	m_Velocity += a_force / GetMass();
	m_anglurVelocity += (a_force.y * a_contact.x - a_force.x * a_contact.y) / GetMoment();

}

void RigidBody::SetMass(const float m_mass)
{
	m_Mass = m_mass;

}

float RigidBody::GetKineticEnergy()
{
	float totalEnergy = (m_Mass * glm::dot(m_Velocity, m_Velocity)) / 2;

	return totalEnergy;
}
