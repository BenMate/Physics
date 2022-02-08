#pragma once
#include "RigidBody.h"

class Box : public RigidBody
{
public:
	Box(glm::vec2 a_position, glm::vec2 a_velocity, float a_rotation,
		float a_mass, float a_width, float a_height);
	//add colour
	Box(glm::vec2 a_position, glm::vec2 a_velocity, float a_rotation,
		float a_mass, float a_width, float a_height, glm::vec4 a_colour);
	//vec2 instead of 2 floats
	Box(glm::vec2 a_position, glm::vec2 a_velocity, float a_rotation,
		float a_mass, glm::vec2 a_dimensions);
	//add colour with vec2 instead of 2 floats
	Box(glm::vec2 a_position, glm::vec2 a_velocity, float a_rotation,
		float a_mass, glm::vec2 a_dimensions, glm::vec4 a_colour);

	~Box();

	virtual void FixedUpdate(glm::vec2 a_gravity, float a_timestep);
	virtual void MakeGizmo();

	bool CheckBoxCorners(const Box& a_box, glm::vec2& a_contact, 
		int& a_numContract, float& a_pen, glm::vec2& a_edgeNormal);

	float GetWidth() const { return m_extents.x * 2; }
	float GetHieght() const { return m_extents.y * 2; }
	glm::vec2 GetExtents() const{ return m_extents; }
	glm::vec2 GetLocalX() const { return m_localX; }
	glm::vec2 GetLocalY() const { return m_localY; }

	void SetColour(glm::vec4 a_colour) { m_colour = a_colour; }

protected:

	glm::vec2 m_extents; //the half edge lengths
	glm::vec4 m_colour; 

	//We will store the local x and y axes of the box 
	//based on its angle of rotation
	glm::vec2 m_localX;
	glm::vec2 m_localY;

	

};

