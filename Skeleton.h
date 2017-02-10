#pragma once
#include "Types.h"

struct Bone : public D3DXFRAME
{
	Matrix	CombinedTransformationMatrix;
	bool	Dirty;
};

class Skeleton
{
public:
	Skeleton();
	~Skeleton();
	void Render();
	void Update(float elapsedTime);
private:
	void CreateHumanoidSkeleton();
	Bone* CreateBoneAndAttachTo(Bone* parent, const Vector3D& offset);
	void DeleteSkeleton(Bone* root);
	void RenderSkeleton(Bone* currentBone, const Matrix& parentMatrix, bool forceUpdate, bool render, Colour& col);
	void SelectBoneIfKeyDown(Bone** bone, int key);
	Bone*	m_skeletonRoot;
	Bone**	m_selected;
	Bone*	m_waist;
	Bone*	m_torso;
	Bone*	m_neck;
	Bone*	m_head;
	Bone*	m_leftUpperArm;
	Bone*	m_leftLowerArm;
	Bone*	m_leftHand;
	Bone*	m_rightUpperArm;
	Bone*	m_rightLowerArm;
	Bone*	m_rightHand;
	Bone*	m_leftUpperLeg;
	Bone*	m_leftLowerLeg;
	Bone*	m_leftFoot;
	Bone*	m_rightUpperLeg;
	Bone*	m_rightLowerLeg;
	Bone*	m_rightFoot;
};