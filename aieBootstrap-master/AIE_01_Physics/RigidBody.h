#pragma once
#include "PhysicsObject.h"
#include <iostream>
#include <functional>
#include <glm/glm.hpp>

//global constant variables
const float MIN_LINEAR_THRESHOLD = 0.0f;
const float MIN_ANGULAR_THRESHOLD = 0.0f;

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

	void ApplyForce(glm::vec2 a_force, glm::vec2 a_contact);
	
	glm::vec2 GetPosition() const { return m_Position; }
	glm::vec2 GetVelocity() const { return m_Velocity; }
	float GetRotation() const { return m_Rotation; }
	float GetMass() const { return m_Mass; }
	float GetAngularVelocity() const { return m_anglurVelocity; }
	float GetMoment() const { return m_isKinematic ? INT_MAX : m_moment; }
	bool GetIsKinamatic() const { return m_isKinematic; }

	void SetMass(const float m_mass);

	float GetKineticEnergy();

	float GetLinearDrag() const { return m_linearDrag; }
	float GetAngularDrag() const { return m_angularDrag; }
	void SetLinearDrag(const float a_linearDrag);
	void SetAngularDrag(const float a_angulerDrag);

	
protected:

	float m_Mass;
	float m_Rotation; //2D needs only a float
	float m_anglurVelocity;
	float m_moment;
	float m_linearDrag;
	float m_angularDrag;

	

	glm::vec2 m_Position;
	glm::vec2 m_Velocity; 


};

