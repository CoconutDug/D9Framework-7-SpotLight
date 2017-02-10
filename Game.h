#pragma once
#include "GameState.h"
#include "Model.h"
#include "Scene.h"
#include "Cube.h"
#include "TexturedCube.h"
#include "Dog.h"
#include <memory>

class GameState;
class Stats;
class Text;
class Scene;

class Game : public GameState
{
public:
	Game();
	virtual	~Game();
	virtual void OnEntry();
	virtual void OnExit();
	virtual void Update(float elapsedTime);
	virtual void Render();
public:
	std::unique_ptr<Scene> m_scene;
	Matrix m_world;
};


