#pragma once
#include "Types.h"

class TexturedCube
{
public:
	TexturedCube();
	~TexturedCube();
	void Render();
	void Update(float elapsedTime);
private:
	void BuildVertexBuffer();
	void BuildIndexBuffer();
	void LoadTexture();

	IDirect3DVertexBuffer9* m_vertexBuffer;
	IDirect3DIndexBuffer9* m_triangleListIndexBuffer;
	LPDIRECT3DTEXTURE9 m_texture;
	bool m_wireFrame;
};




