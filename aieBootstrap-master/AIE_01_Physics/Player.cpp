#include "Player.h"
#include <Input.h>
#include <Gizmos.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Input.h"


Player::Player(glm::vec2 a_position, glm::vec2 a_velocity, float a_mass,
	float a_radius, glm::vec4 a_colour) : Sphere (a_position, a_velocity, a_mass, a_radius, a_colour)
{
	m_Radius = a_radius;
	m_colour = a_colour;
	m_isKinematic = false;
	m_moment = 0.5f * a_mass * m_Radius * m_Radius;
}

Player::~Player()
{

}

void Player::UpdateInput(float deltaTime, aie::Input* a_input)
{
	//use input keys to move the sphere/player
	if (a_input->isKeyDown(aie::INPUT_KEY_A)) ApplyForce(glm::vec2(-1, 0), glm::vec2(0));
	if (a_input->isKeyDown(aie::INPUT_KEY_D)) ApplyForce(glm::vec2(1, 0), glm::vec2(0));
}

void Player::MakeGizmo()
{
	glm::vec2 end = glm::vec2(std::cos(m_rotation),
		std::sin(m_rotation)) * m_Radius;

	aie::Gizmos::add2DCircle(m_position, m_Radius, 12, m_colour);
	aie::Gizmos::add2DLine(m_position, m_position + end, glm::vec4(1, 1, 1, 1));
}


