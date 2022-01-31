#include <iostream>
#include <Gizmos.h>
#include <glm/ext.hpp>

#include "AIE_01_PhysicsApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Sphere.h"

AIE_01_PhysicsApp::AIE_01_PhysicsApp() 
{

}

AIE_01_PhysicsApp::~AIE_01_PhysicsApp() 
{

}

bool AIE_01_PhysicsApp::startup() 
{
	//increase the ui count to maximise the number
	//of objects we can draw
	aie::Gizmos::create(255U, 225U, 65535U, 65535U);

	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	m_physicsScene = new PhysicsScene();

	/* The lower the value the more accurate the simulation will be,
	but it will increase he proccessing time required. if the value is to
	high it will cause the sim to stutter and reduce the stability. */
	m_physicsScene->SetTimeStep(0.01f);


	m_physicsScene->SetGravity(glm::vec2(0, 0));
	m_physicsScene->SetTimeStep(0.01f);

	CreateSphere();

	return true;
}

void AIE_01_PhysicsApp::shutdown() 
{

	delete m_font;
	delete m_2dRenderer;
}

void AIE_01_PhysicsApp::update(float deltaTime) 
{
	// input example
	aie::Input* input = aie::Input::getInstance();

	aie::Gizmos::clear();

	m_physicsScene->Update(deltaTime);
	m_physicsScene->Draw();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void AIE_01_PhysicsApp::draw() 
{

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	static float aspectRatio = 16.0f / 9.0f;
	aie::Gizmos::draw2D(glm::ortho<float>(-100, 100,
		-100 / aspectRatio, 100 / aspectRatio, -1.0f, 1.0f));

	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 10);

	// done drawing sprites
	m_2dRenderer->end();
}

void AIE_01_PhysicsApp::CreateSphere() 
{
	Sphere* ball = new Sphere(glm::vec2(-20, 0) ,glm::vec2(0,0), 10.0f, 4.0f,
		glm::vec4(1, 0, 0, 1));

	Sphere* ball2 = new Sphere(glm::vec2(10, 0), glm::vec2(0, 0), 10.0f, 4.0f,
		glm::vec4(0, 1, 0, 1));

	m_physicsScene->AddActor(ball);
	m_physicsScene->AddActor(ball2);

	ball->ApplyForce(glm::vec2(30, 0));
	ball2->ApplyForce(glm::vec2(-60, 0));
}