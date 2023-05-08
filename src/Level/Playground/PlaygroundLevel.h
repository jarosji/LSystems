#pragma once

#include "../Level.h"

class PlaygroundLevel : public Level
{
public:
	PlaygroundLevel();

	virtual void Tick(const float delta) override;
	virtual void DrawGUI() override;

private:

};

