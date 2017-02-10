#pragma once
//////////////////////////////////////////////////////////////////////////
//Directional Light
//
//This Class creates a directional light using the light object derived from
//the Light Class, within the light manager, the user can call AddDirectionalLight,
//the Light object will be added to the Light List and then can be controlled and
//rendered.
//
//Within D3D, a directional light has direction only, it does not have position, 
//any object with an opposing normal value to the direction light will be illuminated. 
//////////////////////////////////////////////////////////////////////////

#include "Light.h"

class DirectionalLight : public Light
{
public:
	DirectionalLight(const char* ID, int index, const Vector3D& direction);

	virtual	~DirectionalLight();
	virtual const char* GetType() const { return "DIRECTIONALLIGHT"; };

};

