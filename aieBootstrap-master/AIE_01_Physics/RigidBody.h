#pragma once
#include "PhysicsObject.h"
#include <iostream>
#include <functional>
#include <glm/glm.hpp>

//global constant variables
const float MIN_LINEAR_THRESHOLD = 0.01f;
const float MIN_ANGULAR_THRESHOLD = 0.001f;

class RigidBody : public PhysicsObject
{

public:

	RigidBody(ShapeType a_shapeID, glm::vec2 a_position,
		glm::vec2 a_velocity, float a_rotation, float a_mass);

	~RigidBody() {};

	virtual void FixedUpdate(glm::vec2 a_gravity, float a_timeStep);

	virtual void Debug()
	{
		std::cout << "position: " << m_position.x << ', ' <<
			m_position.y << std::endl;
	}

	void ResolveCollision(RigidBody* a_otherActor, glm::vec2 a_contact,
		glm::vec2* a_collisionNormal = nullptr, float a_pen = 0);

	void ApplyForce(glm::vec2 a_force, glm::vec2 a_contact);

	glm::vec2 ToWorld(glm::vec2 a_localPos);

	glm::vec2 GetPosition() const { return m_position; }
	glm::vec2 GetVelocity() const { return m_velocity; }

	float GetRotation() const { return m_rotation; }
	float GetMass() const { return m_isKinematic ? INT_MAX : m_Mass; }

	float GetAngularVelocity() const { return m_anglurVelocity; }
	void SetAngularVelocity(float a_aVel) { m_anglurVelocity = a_aVel; }

	float GetMoment() const { return m_isKinematic ? INT_MAX : m_moment; }
	void  SetMass(const float m_mass);

	void SetPosition(glm::vec2 a_position) { m_position = a_position; }

	void  SetKinematic(bool a_state) { m_isKinematic = a_state; }
	bool  GetIsKinamatic() const { return m_isKinematic; }
	float GetKineticEnergy();

	void SetHasLinearVelocity(bool a_state) { m_hasLinearVelocity = a_state; }
	bool GetHasLinearVelocity() { return m_hasLinearVelocity; }

	bool GetHasAngulerVelocity(){ return m_hasAngularVelocity;}
	void SetHasAngulerVelocity(bool a_state) { m_hasLinearVelocity = a_state; }

	bool GetAllowExteriorForces() { return m_allowExteriorForces; }
	void SetAllowExteriorForces(bool state) { m_allowExteriorForces = state; }

	float GetLinearDrag() const { return m_linearDrag; }
	float GetAngularDrag() const { return m_angularDrag; }
	void  SetLinearDrag(const float a_linearDrag);
	void  SetAngularDrag(const float a_angulerDrag);

	void OnTriggerEnter(PhysicsObject* a_otherObject);

	
protected:

	float m_Mass;
	float m_rotation; 
	float m_anglurVelocity;
	float m_moment;
	float m_linearDrag;
	float m_angularDrag;

	bool m_hasLinearVelocity = true;
	bool m_hasAngularVelocity = true;
	bool m_allowExteriorForces = true;

	glm::vec2 m_position;
	glm::vec2 m_velocity; 

	//We will store the local x and y axes of the box 
	//based on its angle of rotation
	glm::vec2 m_localX;
	glm::vec2 m_localY;

};

