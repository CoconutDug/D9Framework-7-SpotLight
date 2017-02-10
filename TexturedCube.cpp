#include "Types.h"
#include "Vertex.h"
#include "TexturedCube.h"
#include "InputManager.h"

TexturedCube::TexturedCube()
{
	BuildVertexBuffer();
	BuildIndexBuffer();
	LoadTexture();
	m_wireFrame = false;
}

TexturedCube::~TexturedCube()
{
	m_vertexBuffer->Release();
	m_triangleListIndexBuffer->Release();
}

void TexturedCube::Render()
{
	m_D3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	m_D3DDevice->SetStreamSource(0, m_vertexBuffer, 0, sizeof(VertexPositionTexCoord));

	m_D3DDevice->SetIndices(m_triangleListIndexBuffer);

	m_D3DDevice->SetVertexDeclaration(VertexPositionTexCoord::Decl);

	if (m_wireFrame)
	{
		m_D3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}
	else
	{
		m_D3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}

	//Set the texture in the device, that will be rendered on all objects rendered after this point
	m_D3DDevice->SetTexture(0, m_texture);


	m_D3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 24, 0, 12);

	//Reset the texture in memory
	m_D3DDevice->SetTexture(0, NULL);

	m_D3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}

void TexturedCube::Update(float elapsedTime)
{
	if (InputManager::GetInstance()->IsKeyClicked(true, '1'))
	{
		m_wireFrame = !m_wireFrame;
	}
}

void TexturedCube::BuildVertexBuffer()
{
	m_D3DDevice->CreateVertexBuffer(24 * sizeof(VertexPositionTexCoord), D3DUSAGE_WRITEONLY, 0, D3DPOOL_DEFAULT, &m_vertexBuffer, 0);

	VertexPositionTexCoord* vertex = 0;

	m_vertexBuffer->Lock(0, 0, (void**)&vertex, 0);

	//Set the Vertices, each Vertex has a position and a texture co-ordinate.
	//texture co-ordinates, usually defined as U and V is a position on the texture
	//much like an x and y and valued between 0 and 1. 

	//looking at the first four vertex, the Texture will maps from u:0 v:0 at the top
	//left of the face, and u:1 v:1 at the bottom right of the cube.

	vertex[0] = VertexPositionTexCoord(-1.0f, 1.0f, -1.0f, 0.0f, 0.0f);
	vertex[1] = VertexPositionTexCoord(1.0f, 1.0f, -1.0f, 1.0f, 0.0f);
	vertex[2] = VertexPositionTexCoord(-1.0f, -1.0f, -1.0f, 0.0f, 1.0f);
	vertex[3] = VertexPositionTexCoord(1.0f, -1.0f, -1.0f, 1.0f, 1.0f);

	vertex[4] = VertexPositionTexCoord(-1.0f, 1.0f, 1.0f, 1.0f, 0.0f);
	vertex[5] = VertexPositionTexCoord(-1.0f, -1.0f, 1.0f, 1.0f, 1.0f);
	vertex[6] = VertexPositionTexCoord(1.0f, 1.0f, 1.0f, 0.0f, 0.0f);
	vertex[7] = VertexPositionTexCoord(1.0f, -1.0f, 1.0f, 0.0f, 1.0f);

	vertex[8] = VertexPositionTexCoord(-1.0f, 1.0f, 1.0f, 0.0f, 0.0f);
	vertex[9] = VertexPositionTexCoord(1.0f, 1.0f, 1.0f, 1.0f, 0.0f);
	vertex[10] = VertexPositionTexCoord(-1.0f, 1.0f, -1.0f, 0.0f, 1.0f);
	vertex[11] = VertexPositionTexCoord(1.0f, 1.0f, -1.0f, 1.0f, 1.0f);

	vertex[12] = VertexPositionTexCoord(-1.0f, -1.0f, 1.0f, 0.0f, 0.0f);
	vertex[13] = VertexPositionTexCoord(-1.0f, -1.0f, -1.0f, 0.0f, 1.0f);
	vertex[14] = VertexPositionTexCoord(1.0f, -1.0f, 1.0f, 1.0f, 0.0f);
	vertex[15] = VertexPositionTexCoord(1.0f, -1.0f, -1.0f, 1.0f, 1.0f);

	vertex[16] = VertexPositionTexCoord(1.0f, 1.0f, -1.0f, 0.0f, 0.0f);
	vertex[17] = VertexPositionTexCoord(1.0f, 1.0f, 1.0f, 1.0f, 0.0f);
	vertex[18] = VertexPositionTexCoord(1.0f, -1.0f, -1.0f, 0.0f, 1.0f);
	vertex[19] = VertexPositionTexCoord(1.0f, -1.0f, 1.0f, 1.0f, 1.0f);

	vertex[20] = VertexPositionTexCoord(-1.0f, 1.0f, -1.0f, 1.0f, 0.0f);
	vertex[21] = VertexPositionTexCoord(-1.0f, -1.0f, -1.0f, 1.0f, 1.0f);
	vertex[22] = VertexPositionTexCoord(-1.0f, 1.0f, 1.0f, 0.0f, 0.0f);
	vertex[23] = VertexPositionTexCoord(-1.0f, -1.0f, 1.0f, 0.0f, 1.0f);

	m_vertexBuffer->Unlock();
}

void TexturedCube::BuildIndexBuffer()
{
	m_D3DDevice->CreateIndexBuffer(36 * sizeof(WORD), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_triangleListIndexBuffer, 0);

	WORD* index;

	m_triangleListIndexBuffer->Lock(0, 0, (void**)&index, 0);

	//triangeList
	//Back Face
	index[0] = 2; index[1] = 0; index[2] = 1;
	index[3] = 2; index[4] = 1; index[5] = 3;

	// front face.
	index[6] = 5; index[7] = 6; index[8] = 4;
	index[9] = 5; index[10] = 7; index[11] = 6;

	// Top face. 
	index[12] = 10; index[13] = 8; index[14] = 9;
	index[15] = 10; index[16] = 9; index[17] = 11;

	// bottom face. 
	index[18] = 14; index[19] = 12; index[20] = 13;
	index[21] = 14; index[22] = 13; index[23] = 15;

	// Right face. 
	index[24] = 18; index[25] = 16; index[26] = 17;
	index[27] = 18; index[28] = 17; index[29] = 19;

	// Left face.
	index[30] = 22; index[31] = 20; index[32] = 21;
	index[33] = 22; index[34] = 21; index[35] = 23;

	m_triangleListIndexBuffer->Unlock();
}

void TexturedCube::LoadTexture()
{
	D3DXCreateTextureFromFileA(m_D3DDevice, "GBrick.bmp", &m_texture);
	m_D3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_D3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

}
