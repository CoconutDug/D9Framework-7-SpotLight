#include "Types.h"
#include "Material.h"
#include "Model.h"
#include "Scene.h"
#include "CameraController.h"
#include "FreeCamera.h"
#include "InputManager.h"
#include "StaticCamera.h"
#include "FreeCamera.h"
#include "ThirdPersonCamera.h"
#include "Light.h"
#include "LightingManager.h"

Scene::Scene()
	:
	m_timer(0)
{
	LightingManager::Create();
	CreateScene();
}

Scene::~Scene()
{
	LightingManager::Destroy();
}

void Scene::CreateScene()
{
	m_floor = std::make_unique<Quad>(Vector3D(0.0f, -1.1f, 0.0f), Vector3D(90.0f, 0.0f, 0.0f), 10, 10, 128, 0x00ffffff);
	m_car1 = std::make_unique<Model>("Car.x", Vector3D(3.0f, 0.0f, 0.0f), Vector3D(0, 0, 0), 0.5f);
	m_sphere = std::make_unique<Sphere>(Vector3D(0, 2, 0), 1.0f, D3DCOLOR_XRGB(255, 0, 0));
	//m_cube = std::make_unique<Cube>();
	//m_tCube = std::make_unique<TexturedCube>();
	//m_skeleton = std::make_unique<Skeleton>();

	LightingManager::GetInstance()->AddSpotLight("Spot1", Vector3D(-3, 5, -3), Vector3D(0, -1, 0), Vector3D(0.0f, 0.1f, 0.5f), 20, 0.2f, 0.8f, 1.0f, 1, 1, 1, 1);
	LightingManager::GetInstance()->AddSpotLight("Spot2", Vector3D(3, 5, -3), Vector3D(0, -1, 0), Vector3D(0.0f, 0.1f, 0.5f), 20, 0.2f, 0.8f, 1.0f, 1, 1, 1, 1);

	LightingManager::GetInstance()->AddPointLight("Point1", Vector3D(5, 3, -0), 20, Vector3D(0, 0.80f, 0), 1, 1, 1, 1);
	LightingManager::GetInstance()->AddPointLight("Point2", Vector3D(-5, 3, -0), 20, Vector3D(0, 0.80f, 0), 1, 1, 1, 1);
	LightingManager::GetInstance()->AddPointLight("Point3", Vector3D(0, 3, -0), 20, Vector3D(0, 0.80f, 0), 1, 1, 1, 1);
}

void Scene::Update(float elapsedTime)
{
	m_timer += elapsedTime;
	float x = sinf(m_timer * 2.000f);
	float y = sinf(m_timer * 2.246f);
	float z = sinf(m_timer * 2.640f);

	LightingManager::GetInstance()->GetLight("Point1")->SetDiffuse(x, y, z, 1);
	LightingManager::GetInstance()->GetLight("Point2")->SetDiffuse(y, z, x, 1);
	LightingManager::GetInstance()->GetLight("Point3")->SetDiffuse(z, x, y, 1);

	LightingManager::GetInstance()->GetLight("Spot1")->SetPosition(Vector3D(-3 + (z * 2.0f), 5, z * 2.0f));
	LightingManager::GetInstance()->GetLight("Spot2")->SetPosition(Vector3D(3 + (-z * 2.0f), 5, z * 2.0f));
	m_sphere->SetPosition(Vector3D(x,y,4));
}

void Scene::Render()
{
	LightingManager::GetInstance()->SetAllLightsActive();
	LightingManager::GetInstance()->RenderLights();

	m_floor->Render();
	m_car1->Render();
	//m_cube->Render();
	m_sphere->Render();
	//m_tCube->Render();
	//m_skeleton->Render();
}

