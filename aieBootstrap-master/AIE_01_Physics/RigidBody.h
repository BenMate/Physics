#pragma once
#include "PhysicsObject.h"
#include <iostream>
#include <functional>
#include <glm/glm.hpp>

class RigidBody : public PhysicsObject
{

public:

	RigidBody(ShapeType a_shapeID, glm::vec2 a_position, 
		glm::vec2 a_velocity, float a_rotation, float a_mass);

	~RigidBody() {};

	virtual void FixedUpdate(glm::vec2 a_gravity, float a_timeStep);

	virtual void Debug() 
	{	std::cout << "position: " << m_Position.x << ', ' <<
		m_Position.y << std::endl; }


	void ResolveCollision(RigidBody* a_otherActor, glm::vec2 a_contact,
		glm::vec2* a_collisionNormal = nullptr, float a_pen = 0);

	//virtual bool CheckCollision(PhysicsObject* pOther) = 0;

	void ApplyForce(glm::vec2 a_force, glm::vec2 a_contact);
	
	glm::vec2 GetPosition() { return m_Position; }
	glm::vec2 GetVelocity() { return m_Velocity; }
	float GetRotation() { return m_Rotation; }

	float GetMass() { return m_Mass; }
	void SetMass(const float m_mass);

	float GetAngularVelocity() { return m_anglurVelocity; }
	float GetMoment() { return m_isKinematic ? INT_MAX : m_moment; }
	bool GetIsKinamatic() { return m_isKinematic; }
	
	float GetKineticEnergy();
	
protected:

	float m_Mass;
	float m_Rotation; //2D needs only a float
	float m_anglurVelocity;
	float m_moment;

	

	glm::vec2 m_Position;
	glm::vec2 m_Velocity; 


};

