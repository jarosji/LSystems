#pragma once



class System
{
public:
	virtual void Tick(const float deltaTime) {

	}

	friend class Scene;

private:
	int a;
};

