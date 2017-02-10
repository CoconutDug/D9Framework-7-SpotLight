#include "Vertex.h"
#include "Square.h"
#include "InputManager.h"
#include "CameraController.h"
#include <d3dx9math.h>

Square::Square()
{
	BuildVertexBuffer();
	BuildIndexBuffer();
	m_wireFrame = false;
	m_colour = 0x00ffffff;
	m_position = Vector3D(0.0f, 1.1f, 0.0f);
	m_rotation = Vector3D(90.0f, 0.0f, 0.0f);
}

Square::~Square()
{
	m_vertexBuffer->Release();
	m_triangleListIndexBuffer->Release();
}

void Square::Render()
{
	Matrix positionMatrix;
	Matrix rotationMatrix;
	Matrix world;

	//create matrix to move quad in world;
	MatrixTranslation(&positionMatrix, m_position.x, m_position.y, m_position.z);
	MatrixRotationYawPitchRoll(&rotationMatrix, D3DXToRadian(m_rotation.y), D3DXToRadian(m_rotation.x), D3DXToRadian(m_rotation.z));
	world = rotationMatrix * positionMatrix;

	CameraController::GetInstance()->SetWorld(world);

	/// Set the vertex buffer to use
	m_D3DDevice->SetStreamSource(0, m_vertexBuffer, 0, sizeof(VertexPositionNormalColour));

	/// Set the index buffer to use
	m_D3DDevice->SetIndices(m_triangleListIndexBuffer);

	m_D3DDevice->SetMaterial(m_material);

	/// Set the vertex declaration, to tell d3d how our vertices are made up
	m_D3DDevice->SetVertexDeclaration(VertexPositionNormalColour::Decl);

	if (m_wireFrame)
	{
		m_D3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}
	else
	{
		m_D3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}

	/// Render the geomtry as a triangle list, with 8 verts and 12 indices
	//m_D3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 16 * 16 * 2);
	//m_D3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 16 * 16 * 2);
	m_D3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 6, 0, 12);
	CameraController::GetInstance()->ResetWorld();

}

void Square::Update(float elapsedTime)
{
	/// Check to see if we need to toggle the wireframe mode
	if (InputManager::GetInstance()->IsKeyClicked(true, '1'))
	{
		m_wireFrame = !m_wireFrame;
	}
}

void Square::BuildVertexBuffer()
{
	int width = 5;
	int height = 5;

	int m_numSubDivisions = 16;
	int m_numberOfVerts = m_numSubDivisions * m_numSubDivisions * 6;

	m_D3DDevice->CreateVertexBuffer(m_numberOfVerts * sizeof(VertexPositionNormalColour), D3DUSAGE_WRITEONLY, 0, D3DPOOL_DEFAULT, &m_vertexBuffer, 0);

	VertexPositionNormalColour* vertex = 0;

	m_vertexBuffer->Lock(0, 0, (void**)&vertex, 0);

	Vector3D normal(0, 0, -1);

	

	const float delta = 1.0f / ((float)m_numSubDivisions);

	int counter = 0;
	for (int y = 0; y < m_numSubDivisions; y++)
	{
		for (int x = 0; x < m_numSubDivisions; x++)
		{
			Vector3D p0((width * x * delta) - width / 2, (height * y * delta) - height / 2, 0);
			Vector3D p1((width * x * delta) - width / 2, (height * (y + 1)* delta) - height / 2, 0);
			Vector3D p2((width * (x + 1) * delta) - width / 2, (height * (y + 1) * delta) - height / 2, 0);
			Vector3D p3((width * (x + 1) * delta) - width / 2, (height * y * delta) - height / 2, 0);

			vertex[counter + 0] = VertexPositionNormalColour(p0, normal, 0x0000ffff);
			vertex[counter + 1] = VertexPositionNormalColour(p1, normal, 0x0000ffff);
			vertex[counter + 2] = VertexPositionNormalColour(p2, normal, 0x0000ffff);
			vertex[counter + 3] = VertexPositionNormalColour(p0, normal, 0x0000ffff);
			vertex[counter + 4] = VertexPositionNormalColour(p2, normal, 0x0000ffff);
			vertex[counter + 5] = VertexPositionNormalColour(p3, normal, 0x0000ffff);

			counter += 6;
		}
	}

	m_vertexBuffer->Unlock();
	m_material = Material((DWORD)0, (DWORD)0, (DWORD)0, 0);
}

void Square::BuildIndexBuffer()
{
	m_D3DDevice->CreateIndexBuffer(36 * sizeof(WORD), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_triangleListIndexBuffer, 0);

	WORD* index;

	m_triangleListIndexBuffer->Lock(0, 0, (void**)&index, 0);

	//triangeList
	// Front Face
	index[0] = 2;
	index[1] = 0;
	index[2] = 1;
	index[3] = 2;
	index[4] = 1;
	index[5] = 3;

	// Back face.
	index[6] = 5;
	index[7] = 6;
	index[8] = 4;
	index[9] = 5;
	index[10] = 7;
	index[11] = 6;

	// Left face.
	index[12] = 5;
	index[13] = 4;
	index[14] = 0;
	index[15] = 5;
	index[16] = 0;
	index[17] = 2;

	// Right face.
	index[18] = 3;
	index[19] = 1;
	index[20] = 6;
	index[21] = 3;
	index[22] = 6;
	index[23] = 7;

	// Top face.
	index[24] = 0;
	index[25] = 4;
	index[26] = 6;
	index[27] = 0;
	index[28] = 6;
	index[29] = 1;

	// Bottom face.
	index[30] = 5;
	index[31] = 2;
	index[32] = 3;
	index[33] = 5;
	index[34] = 3;
	index[35] = 7;

	m_triangleListIndexBuffer->Unlock();
}

/************************************************************************/
