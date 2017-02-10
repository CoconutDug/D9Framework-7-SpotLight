#pragma once
#include "Material.h"

class Cylinder
{
public:
	Cylinder(const Vector3D& position, const Vector3D& direction, float topRadius, float bottomRadius,
		float length, UINT slices, UINT stacks);
	~Cylinder();
	void SetWireFrame(bool wireFrame);
	void SetMaterial(Material& material);
	Material& GetMaterial();
	void SetPosition(const Vector3D& position);
	const Vector3D&	GetPosition() const;
	void SetDirection(const Vector3D& direction);
	const Vector3D& GetDirection() const;
	void Render();
private:
	void CreateCylinder(float topRadius, float bottomRadius, float length, UINT slices, UINT stacks);
	Mesh* m_cyclinderMesh;
	Vector3D m_position;
	Vector3D m_direction;
	bool m_wireFrame;
	Material m_material;
};
