#include <iostream>
#include <Gizmos.h>
#include <glm/ext.hpp>

#include "Texture.h"
#include "Font.h"
#include "Input.h"

#include "AIE_01_PhysicsApp.h"
#include "Sphere.h"
#include "Plane.h"
#include "Box.h"
#include "Player.h"
#include "Spring.h"

//game states -----------------
#include "GameStateManager.h"
#include "IGameState.h"

#include "GameState.h"
#include "MenuState.h"
#include "GuideState.h"
//------------------------------

AIE_01_PhysicsApp::AIE_01_PhysicsApp() 
{

}

AIE_01_PhysicsApp::~AIE_01_PhysicsApp() 
{

}

bool AIE_01_PhysicsApp::startup() 
{
	//increase the ui count to maximise the number of objects we can draw
	aie::Gizmos::create(255U, 225U, 65535U, 65535U);
	m_2dRenderer = new aie::Renderer2D();
	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	m_physicsScene = new PhysicsScene();
	m_physicsScene->SetTimeStep(0.01f);
	m_physicsScene->SetGravity(glm::vec2(0.0f, -9.0f));

	m_gameStateManager = new GameStateManager();
	m_gameStateManager->SetState("Game", new GameState(this));
	m_gameStateManager->SetState("Menu", new MenuState(this));
	m_gameStateManager->SetState("Guide", new GuideState(this));
	m_gameStateManager->PushState("Game");
	return true;
}

void AIE_01_PhysicsApp::shutdown() 
{
	delete m_font;
	delete m_2dRenderer;
	delete m_gameStateManager;
}

void AIE_01_PhysicsApp::update(float deltaTime)
{
	aie::Input* input = aie::Input::getInstance();
	aie::Gizmos::clear();

	m_gameStateManager->Update(deltaTime);
	m_physicsScene->Update(deltaTime);

	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void AIE_01_PhysicsApp::draw() 
{
	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	//begin drawing gamestate.
	m_gameStateManager->Draw();

	m_physicsScene->Draw();

	// draw your stuff here!
	aie::Gizmos::draw2D(glm::ortho<float>(-m_extents, m_extents,
		-m_extents / m_aspectRatio, m_extents / m_aspectRatio, -1.0f, 1.0f));

	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_2dRenderer->drawText(m_font, fps, 50, getWindowHeight() - 30);

	// output some text, uses the last used colour
	//m_2dRenderer->drawText(m_font, "Press ESC to quit", 10, 10);

	// done drawing sprites
	m_2dRenderer->end();
}

glm::vec2 AIE_01_PhysicsApp::ScreenToWorld(glm::vec2 a_screenPos)
{
	glm::vec2 worldPos = a_screenPos;
	
	//move the center of the screen to (0, 0)

	worldPos.x -= getWindowWidth() / 2;
	worldPos.y -= getWindowHeight() / 2;

	worldPos.x *= 2.0f * m_extents / getWindowWidth();
	worldPos.y *= 2.0f * m_extents / (m_aspectRatio * getWindowHeight());


	return worldPos;
}

void AIE_01_PhysicsApp::CreateSphere() 
{
	Sphere* ball = new Sphere(glm::vec2(-20, 0) ,glm::vec2(0,0), 1.7f, 4.0f,
		glm::vec4(1, 1, 1, 1));
	Sphere* ball2 = new Sphere(glm::vec2(10, 0), glm::vec2(0, 0), 1.6f, 4.0f,
		glm::vec4(0, 1, 0, 1));

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

void AIE_01_PhysicsApp::RotationRest()
{
	//plane
	Plane* plane = new Plane(glm::vec2(0, 1), -30);
	m_physicsScene->AddActor(plane);

	//ball green
	Sphere* ball3 = new Sphere(glm::vec2(20, 30), glm::vec2(0, 0), 1.7f, 4.0f,
		glm::vec4(0, 1, 0, 1));
	m_physicsScene->AddActor(ball3);
	ball3->ApplyForce(glm::vec2(0.0f, -20.0f), ball3->GetPosition());

	//box 
	Box* box1 = new Box(glm::vec2(20, 0), glm::vec2(0, 1), 0, 4, 8, 4);
	m_physicsScene->AddActor(box1);
	box1->ApplyForce(glm::vec2(0.0f, -40.f), box1->GetPosition());

	//box 2
	Box* box2 = new Box(glm::vec2(20, -10), glm::vec2(0, 1), 45, 4, 8, 4);
	m_physicsScene->AddActor(box2);
	box2->ApplyForce(glm::vec2(0.0f, -20.f), box2->GetPosition());
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

void AIE_01_PhysicsApp::ElasticityTest()
{
	//plane
	Plane* plane = new Plane(glm::vec2(0, 1), -30);
	m_physicsScene->AddActor(plane);

	//ball green bouncy
	Sphere* ball3 = new Sphere(glm::vec2(50, 30), glm::vec2(0, 0), 1.7f, 4.0f,
		glm::vec4(0, 1, 0, 1));

	m_physicsScene->AddActor(ball3);
	ball3->SetElasticity(0.7f);
	ball3->ApplyForce(glm::vec2(0.0f, -20.0f), ball3->GetPosition());

	//box big blue not bouncy
	Box* box1 = new Box(glm::vec2(20, 0), glm::vec2(0, 1), 0, 4, 20, 20);

	m_physicsScene->AddActor(box1);
	box1->SetElasticity(0.1f);
	box1->ApplyForce(glm::vec2(0.0f, -40.f), box1->GetPosition());
	box1->SetKinematic(false);

	//ball green2 bouncy
	Sphere* ball = new Sphere(glm::vec2(20, 30), glm::vec2(0, 0), 1.7f, 4.0f,
		glm::vec4(0, 1, 0, 1));

	m_physicsScene->AddActor(ball);
	ball->SetElasticity(0.7f);
	ball->ApplyForce(glm::vec2(0.0f, -20.0f), ball3->GetPosition());

	//box bouncy red
	Box* box2 = new Box(glm::vec2(50, 0), glm::vec2(0, 1), 0, 4, 20, 20, 
		glm::vec4(1,0,0,1));

	m_physicsScene->AddActor(box2);
	box2->SetElasticity(0.9f);
	box2->ApplyForce(glm::vec2(0.0f, -40.f), box2->GetPosition());
	box2->SetKinematic(false);


}

void AIE_01_PhysicsApp::MouseInputTest(aie::Input* a_input)
{
	int xScreen, yScreen;
	if (a_input->isMouseButtonDown(0)) 
	{
		m_isKeyPressed = true;
		a_input->getMouseXY(&xScreen, &yScreen);
		glm::vec2 worldPos = ScreenToWorld(glm::vec2(xScreen, yScreen));
		aie::Gizmos::add2DCircle(worldPos, 5, 32, glm::vec4(0.1f, 0.1f, 0.9f, 1.0f));
	}

	if (a_input->wasMouseButtonReleased(0)) 
	{
		a_input->getMouseXY(&xScreen, &yScreen);
		glm::vec2 worldPos = ScreenToWorld(glm::vec2(xScreen, yScreen));
		Sphere* spawn = new Sphere(worldPos, glm::vec2(0, 0), 4.0f, 4.0f, glm::vec4(0.1f, 0.1f, 0.4f, 1.0f));
		m_physicsScene->AddActor(spawn);	
	}
}

void AIE_01_PhysicsApp::ObjectTest()
{
	m_physicsScene->SetGravity(glm::vec2(0, -9.82f));

	//ball green
	Sphere* ball1 = new Sphere(glm::vec2(-40, 10), glm::vec2(0, 0), 4.0f, 4.0f,
		glm::vec4(0, 1, 0, 1));
	
	//ball red static
	Sphere* ball2 = new Sphere(glm::vec2(-40, 0), glm::vec2(0, 0), 4.0f, 4.0f,
		glm::vec4(1, 0, 0, 1));

	//box bouncy red
	Box* box2 = new Box(glm::vec2(50, 0), glm::vec2(0, 1), 0.6f, 4, 5, 5,
		glm::vec4(1, 0, 0, 1));

	box2->SetKinematic(false);
	ball1->SetKinematic(false);
	ball2->SetKinematic(true);
	ball2->SetTrigger(true);
	
	m_physicsScene->AddActor(ball1);
	m_physicsScene->AddActor(ball2);
	m_physicsScene->AddActor(box2);

	m_physicsScene->AddActor(new Plane(glm::vec2(0, 1), -30));
	m_physicsScene->AddActor(new Plane(glm::vec2(1, 0), -50));
	m_physicsScene->AddActor(new Plane(glm::vec2(-1, 0), -50));

	ball2->onTriggerEnter = [=](PhysicsObject* a_other)
	{
		std::cout << "Entered: " << a_other << std::endl;
	};

	ball2->onTriggerExit = [=](PhysicsObject* a_other)
	{
		std::cout << "Exited: " << a_other << std::endl;
	};
}

void AIE_01_PhysicsApp::SpringTest(int a_amount)
{
	Sphere* prev = nullptr;
	
	for (int i = 0; i < a_amount; i++)
	{
		//spawn a new sphere below the last.
		Sphere* ball = new Sphere(glm::vec2(i * 3, 30 - i * 5), glm::vec2(0), 10, 2, glm::vec4(0,0,1,1));

		if (i == 0) ball->SetKinematic(true);

		m_physicsScene->AddActor(ball);

		if (prev) 
			m_physicsScene->AddActor(new Spring(ball, prev, 10, 500));
		prev = ball;
		
	}

	//add a kinamatic box
	Box* box = new Box(glm::vec2(0, -20), glm::vec2(0), 0.3f, 20,
		glm::vec2(8, 2), glm::vec4(0, 1, 1, 1));

	m_physicsScene->AddActor(box);

}






