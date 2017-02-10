#pragma once
#include "Light.h"

//////////////////////////////////////////////////////////////////////////
//SpotLight
//
//This Class creates a SpotLight using the light object derived from the
//light class, within the light manager, the user can call AddSpotLight,
//the Light object will be added to the Light List and then can be controlled and
//rendered.
//
//Within D3D, a SpotLight is much like a spot light in the real world,
//it is a light with position and direction, the light can also shine with
//different intercity and range.
//
//In addition to Attenuation and range, a Spot Light requires a Theta, Phi
//and Falloff,
//
//Theta: Angle, in radians, of a spotlight's inner cone - that is, 
//		 the fully illuminated spotlight cone. This value must be in the range from 0 through the value specified by Phi. 
//
//Phi: Angle, in radians, defining the outer edge of the spotlight's outer cone. 
//	   Points outside this cone are not lit by the spotlight. This value must be between 0 and pi. 
//
//Falloff: Decrease in illumination between a spotlight's inner cone (the angle specified by Theta) 
//		   and the outer edge of the outer cone (the angle specified by Phi). 
//		   The effect of falloff on the lighting is subtle. Furthermore, 
//		   a small performance penalty is incurred by shaping the falloff curve. For these reasons, most developers set this value to 1.0. 
//
//
//////////////////////////////////////////////////////////////////////////

class SpotLight : public Light
{
public:
	SpotLight(const char* ID, int index, const Vector3D& pos, const Vector3D& dir, const Vector3D& attenuation, float range,
		float theta, float phi, float falloff, float r, float g, float b, float a);
	virtual	~SpotLight();
	virtual const char* GetType() const { return "SPOTLIGHT"; };
};