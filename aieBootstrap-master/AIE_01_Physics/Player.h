#pragma once
#include "Sphere.h"
#include <glm/ext.hpp>
#include <Input.h>

class Player : public Sphere
{


public:

	Player(glm::vec2 a_position, glm::vec2 a_velocity,
		float a_mass, float a_radius, glm::vec4 a_colour);
		

	~Player();

	void UpdateInput(float deltaTime, aie::Input* a_input);

	virtual void MakeGizmo();
	

protected:

	


};

