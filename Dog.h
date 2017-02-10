#pragma once
#include "Types.h"
#include "Skeleton.h"

//struct Bone : public D3DXFRAME
//{
//	Matrix	CombinedTransformationMatrix;
//	bool	Dirty;
//};

class Dog
{
public:
	Dog();
	~Dog();
	void Render();
	void Update(float elapsedTime);
private:
	void CreateDogSkeleton();
	Bone* CreateBoneAndAttachTo(Bone* parent, const Vector3D& offset);
	void DeleteSkeleton(Bone* root);
	void RenderSkeleton(Bone* currentBone, const Matrix& parentMatrix, bool forceUpdate, bool render, Colour& col);
	Bone* m_skeletonRoot;
	Bone** m_selected;
	Bone* m_waist;
	Bone* m_torso;
	Bone* m_neck;
	Bone* m_head;
	Bone* m_frontLeftUpperLeg;
	Bone* m_frontLeftLowerLeg;
	Bone* m_frontLeftPaw;
	Bone* m_frontRightUpperLeg;
	Bone* m_frontRightLowerLeg;
	Bone* m_frontRightPaw;
	Bone* m_backLeftUpperLeg;
	Bone* m_backLeftLowerLeg;
	Bone* m_backLeftPaw;
	Bone* m_backRightUpperLeg;
	Bone* m_backRightLowerLeg;
	Bone* m_backRightPaw;
};
