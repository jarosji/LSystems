#pragma once

class Event
{
public:
	virtual ~Event() = default;
};

class WindowResizeEvent : public Event
{
public:
	WindowResizeEvent(const int width, const int height) : width(width), height(height) {}

	int GetWidth() const { return width; }
	int GetHeight() const { return height; }

private:
	int width;
	int height;
};

class KeyEvent : public Event
{

public:
	const int GetKeyCode() { return keyCode; }

protected:
	KeyEvent(int keyCode, int scanCode, int mods)
		: keyCode(keyCode), scanCode(scanCode), mods(mods)
	{

	}

	int keyCode;
	int scanCode;
	int mods;
};

class KeyPressedEvent : public KeyEvent
{
public:
	KeyPressedEvent(int keyCode, int scanCode, int mods)
		: KeyEvent(keyCode, scanCode, mods)
	{

	}

protected:
	
};

class ScrollEvent : public Event
{
public:
	ScrollEvent(const double offsetX, const double offsetY)
		: offsetX(offsetX), offsetY(offsetY)
	{
	}

	const double GetOffsetX() const {
		return offsetX;
	}

	const double GetOffsetY() const {
		return offsetY;
	}

	void GetOffsets(double& outOffsetX, double& outOffsetY) const {
		outOffsetX = offsetX;
		outOffsetY = offsetY;
	}

protected:

	double offsetX;
	double offsetY;
};