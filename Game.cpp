#include "Types.h"
#include "Scene.h"
#include "BaseCamera.h"
#include "Game.h"
#include "CameraController.h"
#include "FreeCamera.h"
#include "Sphere.h"
#include "Program.h"
#include "InputManager.h"

Game::Game() 
	:
	GameState(L"Game")
{
	m_scene = std::make_unique<Scene>();
}

Game::~Game()
{
	CameraController::Destroy();
}

void Game::OnEntry()
{
	CameraController::Create();
	CameraController::GetInstance()->AddCamera(std::make_shared<FreeCamera>());
}

void Game::OnExit()
{
	CameraController::Destroy();
}

void Game::Update(float elapsedTime)
{
	InputManager::GetInstance()->Update();
	CameraController::GetInstance()->Update(elapsedTime);
	m_scene->Update(elapsedTime);
}

void Game::Render()
{
	CameraController::GetInstance()->ComputeCamera();
	m_scene->Render();
}
