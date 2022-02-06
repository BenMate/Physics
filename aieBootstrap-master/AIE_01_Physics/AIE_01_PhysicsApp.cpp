#include <iostream>
#include <Gizmos.h>
#include <glm/ext.hpp>

#include "Texture.h"
#include "Font.h"
#include "Input.h"

#include "AIE_01_PhysicsApp.h"
#include "Sphere.h"
#include "Plane.h"

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
	;

	//CollisionDetectionTest();

	CreateSphere();
	//CreateBeaker();
	
	//CreateRocket


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

	//UpdateRocket(deltaTime);
	


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

	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_2dRenderer->drawText(m_font, fps, 0, 720 - 32);

	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 10, 10);

	// done drawing sprites
	m_2dRenderer->end();
}

void AIE_01_PhysicsApp::CreateSphere() 
{
	Sphere* ball = new Sphere(glm::vec2(-20, 0) ,glm::vec2(0,0), 1.7f, 4.0f,
		glm::vec4(1, 1, 1, 1));
	Sphere* ball2 = new Sphere(glm::vec2(10, 0), glm::vec2(0, 0), 1.6f, 4.0f,
		glm::vec4(0, 1, 0, 1));

	//adds 2 balls
	m_physicsScene->AddActor(ball);
	m_physicsScene->AddActor(ball2);

	ball->ApplyForce(glm::vec2(20.f, -20.0f), ball->GetPosition());
	ball2->ApplyForce(glm::vec2(-20, -20.0f), ball2->GetPosition());

	Plane* plane = new Plane(glm::vec2(0, 1), - 30);
	m_physicsScene->AddActor(plane);


}

void AIE_01_PhysicsApp::CreateBeaker()
{

	auto leftAngle = glm::vec2(1, 1);
	auto rightAngle = glm::vec2(-1, 1);
	auto rightWall = glm::vec2(-1, 0);
	auto bottomWall = glm::vec2(0, 1);
	auto LeftWall = glm::vec2(1, 0);

	Plane* testPlane  = new Plane(leftAngle,  -20);
	Plane* testPlane2 = new Plane(rightAngle, -20);
	Plane* testPlane3 = new Plane(rightWall,  -30);
	Plane* testPlane4 = new Plane(bottomWall, -30);
	Plane* testPlane5 = new Plane(LeftWall,   -30);

	m_physicsScene->AddActor(testPlane);
	m_physicsScene->AddActor(testPlane2);
	m_physicsScene->AddActor(testPlane3);
	m_physicsScene->AddActor(testPlane4);
	m_physicsScene->AddActor(testPlane5);

}

void AIE_01_PhysicsApp::CollisionDetectionTest()
{
	Sphere* sphere1 = new Sphere(glm::vec2(-10, 0), glm::vec2(0, 0), 4.0f, 4.0f,
		glm::vec4(0,0,1,1));

	Sphere* sphere2 = new Sphere(glm::vec2(10, 0), glm::vec2(0, 0), 4.0f, 4.0f,
		glm::vec4(1, 0, 0, 1));

	Plane* plane = new Plane(glm::vec2(0, 1), -30);

	m_physicsScene->AddActor(sphere1);
	m_physicsScene->AddActor(sphere2);
	m_physicsScene->AddActor(plane);

}

void AIE_01_PhysicsApp::CreateRocket()
{
	m_rocket = new Sphere(glm::vec2(0, -40), glm::vec2(0, 0), 25, 10,
		glm::vec4(1, 0, 1, 1));

	//adds rocket
	m_physicsScene->AddActor(m_rocket);
}

void AIE_01_PhysicsApp::UpdateRocket(float deltaTime)
{
	//create new circles near the rocket to simulate boost every so often

	timer += deltaTime;
	float mass = m_rocket->GetMass();

	if (timer > 0.1f && mass > 5.0f)
	{
		//creates circle under the rocket
		auto pos = m_rocket->GetPosition();
		pos = { pos.x, pos.y };

		Sphere* boost = new Sphere(glm::vec2(pos.x, pos.y - 15), glm::vec2(0, 0), 0.5f, 3.0f,
			glm::vec4(0, 1, 0, 1));

		//adds boost when rocket is added
		m_physicsScene->AddActor(boost);

		//makes the rocket add more force each boost
		//boost->ApplyForceToActor(m_rocket, glm::vec2(0, 8));
		
		boost->ApplyForce(glm::vec2(0, -8.0f), m_rocket->GetPosition());

		//change the mass everytime we boost because we consume fuel

		m_rocket->SetMass(mass - 0.5f);

		timer = 0.0f;
	} 
}


