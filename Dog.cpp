#include "Dog.h"
#include "InputManager.h"
#include "Cylinder.h"
#include "Material.h"
#include "Skeleton.h"

Dog::Dog() :
	m_selected(NULL)
{
	CreateDogSkeleton();
}

Dog::~Dog()
{
	DeleteSkeleton(m_skeletonRoot);
}

void Dog::CreateDogSkeleton()
{
	m_waist = CreateBoneAndAttachTo(NULL, Vector3D(0.0f, 0.0f, 1.0f));

	m_torso = CreateBoneAndAttachTo(m_waist, Vector3D(-0.8f, 0.0f, 0.0f));
	m_neck = CreateBoneAndAttachTo(m_torso, Vector3D(-0.1f, 0.1f, 0.0f));
	m_head = CreateBoneAndAttachTo(m_neck, Vector3D(-0.3f, -0.2f, 0.0f));


	m_frontLeftUpperLeg = CreateBoneAndAttachTo(m_torso, Vector3D(-0.1f, -0.2f, -0.1f));
	m_frontLeftLowerLeg = CreateBoneAndAttachTo(m_frontLeftUpperLeg, Vector3D(0.1f, -0.2f, -0.1f));
	m_frontLeftPaw = CreateBoneAndAttachTo(m_frontLeftLowerLeg, Vector3D(-0.1f, 0.0f, -0.1f));

	m_skeletonRoot = m_waist;
}

Bone* Dog::CreateBoneAndAttachTo(Bone* parent, const Vector3D& offset)
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

void Dog::DeleteSkeleton(Bone* root)
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

void Dog::Update(float elapsedTime)
{

}

void Dog::Render()
{
	Matrix position;
	MatrixIdentity(&position);

	RenderSkeleton(m_skeletonRoot, position, false, false, Colour(0, 1.0, 2.0f, 0));
}

void Dog::RenderSkeleton(Bone* currentBone, const Matrix& parentMatrix, bool forceUpdate, bool render, Colour& col)
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
