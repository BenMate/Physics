#include "RigidBody.h"
#include "PhysicsScene.h"
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

	m_linearDrag = 0.3f;
	m_angularDrag = 0.3f;

	m_isTrigger = false;
	m_isKinematic = false;
}


void RigidBody::FixedUpdate(glm::vec2 a_gravity, float a_timeStep)
{
	if (m_isTrigger) 
	{
		//check every object that is inside and called OnTriggerEnter
		//on if they havnt registered inside of us this frame, they had to of exited
		//therefore we can remove them from our list and call triggerExit.
		for (auto it = m_objectsInside.begin(); it != m_objectsInside.end(); it++)
		{
			if (std::find(m_objectsInsideThisFrame.begin(), m_objectsInsideThisFrame.end(), 
				*it) == m_objectsInsideThisFrame.end()) 
			{
				if (onTriggerExit) 
				{
					onTriggerExit(*it);
					it = m_objectsInside.erase(it);

					if (it == m_objectsInside.end()) 				
						break;
				}

			}
		}
	}
	//clear this list now for the next frame
	m_objectsInsideThisFrame.clear();

	if (m_hasLinearVelocity && !m_isKinematic) 
	{
		m_Velocity -= m_Velocity * m_linearDrag * a_timeStep;
		m_Position += GetVelocity() * a_timeStep;

		if (glm::length(m_Velocity) < MIN_LINEAR_THRESHOLD)
			m_Velocity = glm::vec2(0, 0);

		ApplyForce(a_gravity * GetMass() * a_timeStep, glm::vec2(0, 0));
	}

	if (m_hasAngularVelocity && !m_isKinematic)
	{
		m_anglurVelocity -= m_anglurVelocity * m_angularDrag * a_timeStep;
		m_Rotation += m_anglurVelocity * a_timeStep;

		if (glm::abs(m_anglurVelocity) < MIN_ANGULAR_THRESHOLD)
			m_anglurVelocity = 0;
	}	
}

void RigidBody::ResolveCollision(RigidBody* a_otherActor, glm::vec2 a_contact,
	glm::vec2* a_collisionNormal, float a_pen)
{
	//register that a collision has occurred and these objects have overlapped
	m_objectsInsideThisFrame.push_back(a_otherActor);
	a_otherActor->m_objectsInsideThisFrame.push_back(this);

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
		if (!m_isTrigger && !a_otherActor->m_isTrigger)
		{
			//this will calculate the effective mass at the contact point for each objet....
			//ie. how much the contact point will move due to the forces applied.
			float massThis = 1.0f / (1.0f / GetMass() + glm::pow(radiusThis, 2.0f) / m_moment);
			float massOther = 1.0f / (1.0f / a_otherActor->GetMass() +
				glm::pow(radiusOther, 2.0f) / a_otherActor->GetMoment());

			float elasticity = (m_elasticity + a_otherActor->GetElasticity()) / 2.0f;

			glm::vec2 impact = (1.0f + elasticity) * massThis * massOther / (massThis + massOther) *
				(cp_VelThis - cp_VelOther) * normal;

			ApplyForce(-impact, a_contact - m_Position);

			a_otherActor->ApplyForce(impact, a_contact - a_otherActor->GetPosition());
		}
		else
		{
			OnTriggerEnter(a_otherActor);
			a_otherActor->OnTriggerEnter(this);
		}
	}

	if (a_pen > 0)
	{
		PhysicsScene::ApplyContactForces(this, a_otherActor, normal, a_pen);
	}
}

void RigidBody::ApplyForce(glm::vec2 a_force, glm::vec2 a_contact)
{
	if (m_allowExteriorForces)
		m_Velocity += a_force / GetMass();

	if (m_allowExteriorForces)
		m_anglurVelocity += (a_force.y * a_contact.x - a_force.x * a_contact.y) / GetMoment();

}

glm::vec2 RigidBody::ToWorld(glm::vec2 a_localPos)
{
	return m_Position + m_localX * a_localPos.x 
					  + m_localY * a_localPos.y;
}

void RigidBody::SetMass(const float m_mass)
{
	m_Mass = m_mass;

}

float RigidBody::GetKineticEnergy()
{
	return 0.5f * (GetMass() * glm::dot(m_Velocity, m_Velocity) +
		GetMoment() * m_anglurVelocity * m_anglurVelocity);
}

void RigidBody::SetLinearDrag(const float a_linearDrag)
{
	m_linearDrag = a_linearDrag;
}

void RigidBody::SetAngularDrag(const float a_angulerDrag)
{
	m_angularDrag = a_angulerDrag;
}

void RigidBody::OnTriggerEnter(PhysicsObject* a_otherObject)
{

	if (m_isTrigger && std::find(m_objectsInside.begin(), m_objectsInside.end(),
		a_otherObject) == m_objectsInside.end())
	{
		m_objectsInside.push_back(a_otherObject);

		if (onTriggerEnter != nullptr)
		{
			onTriggerEnter(a_otherObject);
		}
	}
}
