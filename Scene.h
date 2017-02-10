#pragma once
#include "Model.h"
#include "Quad.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Cube.h"
#include "Skeleton.h"
#include "TexturedCube.h"
#include "Square.h"
#include <memory>

class Scene
{
public:
	Scene();
	~Scene();
	void CreateScene();
	void Update(float elapsedTime);
	void Render();
private:
	std::unique_ptr<Quad> m_floor;
	std::unique_ptr<Model> m_car1;
	std::unique_ptr<Sphere> m_sphere;
	std::unique_ptr<Cube> m_cube;
	std::unique_ptr<TexturedCube> m_tCube;
	std::unique_ptr<Skeleton> m_skeleton;
	float m_timer;
};