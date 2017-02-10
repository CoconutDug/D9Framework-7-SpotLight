#pragma once
#include "Types.h"
#include "Material.h"

class Square
{
public:
	Square();
	~Square();
	void Render();
	void Update(float elapsedTime);
private:
	void BuildVertexBuffer();
	void BuildIndexBuffer();
	bool m_wireFrame;
	Material m_material;
	DWORD m_colour;
	Vector3D m_position;
	Vector3D m_rotation;
	IDirect3DVertexBuffer9* m_vertexBuffer;
	IDirect3DIndexBuffer9* m_triangleListIndexBuffer;
};
#pragma once
