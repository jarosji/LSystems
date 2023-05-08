#pragma once

#include "../Level.h"

class EmptyLevel : public Level
{
public:
	EmptyLevel();
	
	virtual void Tick(const float delta) override;
	virtual void DrawGUI() override;
	

private:
};

