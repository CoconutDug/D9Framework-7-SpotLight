#include "InputManager.h"
#include "Cylinder.h"
#include "Material.h"
#include "Skeleton.h"

Skeleton::Skeleton() :
	m_selected(NULL)
{
	CreateHumanoidSkeleton();
}

Skeleton::~Skeleton()
{
	DeleteSkeleton(m_skeletonRoot);
}

void Skeleton::CreateHumanoidSkeleton()
{
	// Create our skeleton by making bones and attaching them to others to form a hierarchy
	m_waist = CreateBoneAndAttachTo(NULL, Vector3D(0.0f, 0.0f, 1.0f));

	m_torso = CreateBoneAndAttachTo(m_waist, Vector3D(0.0f, 0.0f, 1.0f));
	m_neck = CreateBoneAndAttachTo(m_torso, Vector3D(0.0f, 0.0f, 0.25f));
	m_head = CreateBoneAndAttachTo(m_neck, Vector3D(0.0f, 0.25f, -0.1f));

	m_leftUpperArm = CreateBoneAndAttachTo(m_torso, Vector3D(-0.3f, 0.0f, -0.3f));
	m_leftLowerArm = CreateBoneAndAttachTo(m_leftUpperArm, Vector3D(0.0f, 0.0f, -0.5f));
	m_leftHand = CreateBoneAndAttachTo(m_leftLowerArm, Vector3D(0.0f, 0.25f, -0.2f));

	m_rightUpperArm = CreateBoneAndAttachTo(m_torso, Vector3D(0.3f, 0.0f, -0.3f));
	m_rightLowerArm = CreateBoneAndAttachTo(m_rightUpperArm, Vector3D(0.0f, 0.0f, -0.5f));
	m_rightHand = CreateBoneAndAttachTo(m_rightLowerArm, Vector3D(0.0f, 0.25f, -0.2f));

	m_leftUpperLeg = CreateBoneAndAttachTo(m_waist, Vector3D(-0.25f, 0.0f, -0.5f));
	m_leftLowerLeg = CreateBoneAndAttachTo(m_leftUpperLeg, Vector3D(0.0f, 0.0f, -0.5f));
	m_leftFoot = CreateBoneAndAttachTo(m_leftLowerLeg, Vector3D(0.0f, 0.25f, -0.05f));

	m_rightUpperLeg = CreateBoneAndAttachTo(m_waist, Vector3D(0.25f, 0.0f, -0.5f));
	m_rightLowerLeg = CreateBoneAndAttachTo(m_rightUpperLeg, Vector3D(0.0f, 0.0f, -0.5f));
	m_rightFoot = CreateBoneAndAttachTo(m_rightLowerLeg, Vector3D(0.0f, 0.25f, -0.05f));

	m_skeletonRoot = m_waist;
}

Bone* Skeleton::CreateBoneAndAttachTo(Bone* parent, const Vector3D& offset)
{
	// Allocate a new bone
	Bone* newBone = new Bone;

	// Initialise the transformation matrices
	MatrixTranslation(&newBone->TransformationMatrix, offset.x, offset.y, offset.z);
	MatrixIdentity(&newBone->CombinedTransformationMatrix);

	// Mark the bone as dirty which means the combined transformation matrix needs updating later
	newBone->Dirty = true;

	// We start off with no children or siblings
	newBone->pFrameFirstChild = NULL;
	newBone->pFrameSibling = NULL;

	// Are we being attached to a parent?
	if (parent)
	{
		// Does the parent have any children already?
		if (parent->pFrameFirstChild)
		{
			// If so, consider the parent's first child (a sibling to us)
			Bone* sibling = (Bone*)parent->pFrameFirstChild;

			// The siblings are all linked together in a chain.  We need to follow
			// the chain and find the end so we can attach ourselves there
			while (sibling->pFrameSibling)
			{
				sibling = (Bone*)sibling->pFrameSibling;
			}

			// We've found the end of the chain (a sibling with no link) so link it to us 
			sibling->pFrameSibling = newBone;
		}
		else
		{
			// The parent has no children already, so we can directly link it to us
			parent->pFrameFirstChild = newBone;
		}
	}

	// Return the newly generated bone
	return newBone;
}

void Skeleton::DeleteSkeleton(Bone* root)
{
	// Recursively delete a skeleton
	if (root->pFrameFirstChild)
	{
		// If the current bone has any children, remove the first one and recursively remove any other descendents
		DeleteSkeleton((Bone*)root->pFrameFirstChild);
	}

	if (root->pFrameSibling)
	{
		// If the current bone has any siblings, remove the first one and recursively remove any other descendents
		DeleteSkeleton((Bone*)root->pFrameSibling);
	}

	// Delete the current bone
	delete root;

	return;
}

void Skeleton::Update(float elapsedTime)
{
	// Check to see if any of the bone select keys have been pressed
	SelectBoneIfKeyDown(&m_torso, DIK_E);
	SelectBoneIfKeyDown(&m_neck, DIK_3);
	SelectBoneIfKeyDown(&m_head, DIK_4);
	SelectBoneIfKeyDown(&m_leftUpperArm, DIK_W);
	SelectBoneIfKeyDown(&m_leftLowerArm, DIK_Q);
	SelectBoneIfKeyDown(&m_leftHand, DIK_A);
	SelectBoneIfKeyDown(&m_rightUpperArm, DIK_R);
	SelectBoneIfKeyDown(&m_rightLowerArm, DIK_T);
	SelectBoneIfKeyDown(&m_rightHand, DIK_G);
	SelectBoneIfKeyDown(&m_leftUpperLeg, DIK_S);
	SelectBoneIfKeyDown(&m_leftLowerLeg, DIK_X);
	SelectBoneIfKeyDown(&m_leftFoot, DIK_Z);
	SelectBoneIfKeyDown(&m_rightUpperLeg, DIK_F);
	SelectBoneIfKeyDown(&m_rightLowerLeg, DIK_V);
	SelectBoneIfKeyDown(&m_rightFoot, DIK_B);

	if (m_selected)
	{
		Matrix rotation;

		// If any of the arrow keys are pressed then rotate the selected bone and mark it (dirty) for recalculation 
		if (InputManager::GetInstance()->IsKeyDown(false, DIK_UP))
		{
			MatrixRotationX(&rotation, elapsedTime);
			(*m_selected)->TransformationMatrix = (*m_selected)->TransformationMatrix * rotation;
			(*m_selected)->Dirty = true;
		}
		if (InputManager::GetInstance()->IsKeyDown(false, DIK_DOWN))
		{
			MatrixRotationX(&rotation, -elapsedTime);
			(*m_selected)->TransformationMatrix = (*m_selected)->TransformationMatrix * rotation;
			(*m_selected)->Dirty = true;
		}
		if (InputManager::GetInstance()->IsKeyDown(false, DIK_LEFT))
		{
			MatrixRotationZ(&rotation, elapsedTime);
			(*m_selected)->TransformationMatrix = (*m_selected)->TransformationMatrix * rotation;
			(*m_selected)->Dirty = true;
		}
		if (InputManager::GetInstance()->IsKeyDown(false, DIK_RIGHT))
		{
			MatrixRotationZ(&rotation, -elapsedTime);
			(*m_selected)->TransformationMatrix = (*m_selected)->TransformationMatrix * rotation;
			(*m_selected)->Dirty = true;
		}
	}

	if (InputManager::GetInstance()->IsKeyDown(false, DIK_SPACE))
	{
		// The reset key has been pressed so restore the original
		// skeleton position by deleting it and recreating it
		DeleteSkeleton(m_skeletonRoot);
		CreateHumanoidSkeleton();
	}
}

void Skeleton::SelectBoneIfKeyDown(Bone** bone, int key)
{
	if (InputManager::GetInstance()->IsKeyDown(false, key))
	{
		m_selected = bone;
	}
}

void Skeleton::Render()
{
	Matrix position;
	MatrixIdentity(&position);

	RenderSkeleton(m_skeletonRoot, position, false, false, Colour(0, 1.0, 1.0f, 0));
}

void Skeleton::RenderSkeleton(Bone* currentBone, const Matrix& parentMatrix, bool forceUpdate, bool render, Colour& col)
{
	// We need to recalculate if either an update is being forced (because one
	// of our ancestors was dirty) or the current bone is dirty
	forceUpdate |= currentBone->Dirty;

	if (forceUpdate)
	{
		// Update the combined matrix
		currentBone->CombinedTransformationMatrix = currentBone->TransformationMatrix * parentMatrix;

		// The bone is now up to date to can be marked clean
		currentBone->Dirty = false;
	}

	if (render)
	{
		// We'll be drawing a cone from our parent's bone position to our position
		Vector3D position(parentMatrix._41, parentMatrix._42, parentMatrix._43);
		Vector3D direction(currentBone->CombinedTransformationMatrix._41, currentBone->CombinedTransformationMatrix._42, currentBone->CombinedTransformationMatrix._43);
		direction -= position;
		float length = Vector3DLength(&direction);

		Cylinder boneCone(position + direction / 2, direction, 0.05f, 0.0f, length, 40, 1);
		boneCone.GetMaterial().m_ambient = (m_selected && currentBone == *m_selected ? Colour(1.0f, 0.0f, 0.0f, 0.0f) : col);
		boneCone.Render();
	}

	if (currentBone->pFrameFirstChild)
	{
		// If we have any children then recursively render them in a slightly different shade
		Colour childCol = col * 0.75f;
		RenderSkeleton((Bone*)currentBone->pFrameFirstChild, currentBone->CombinedTransformationMatrix, forceUpdate, true, childCol);
	}

	if (currentBone->pFrameSibling)
	{
		// If we have any siblings then recursively render them
		RenderSkeleton((Bone*)currentBone->pFrameSibling, parentMatrix, forceUpdate, true, col);
	}
}
