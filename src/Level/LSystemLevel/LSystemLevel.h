#pragma once

#include "../Level.h"
#include "../../Scene/ECS/EntityRegistry.h"

class LSystemLevel : public Level
{
public:
	LSystemLevel();

	virtual void Tick(const float delta) override;
	virtual void DrawGUI() override;

private:
	Entity* travelLight;
	Entity* pLight;
	Entity* spotLight;

	float time = 0;

	float accLinearInit = 0.00001f;
	float accQuadInit = 0.000025f;
	float accLinear = accLinearInit;
	float accQuad = accQuadInit;

};

