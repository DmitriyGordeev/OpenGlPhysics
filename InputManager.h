#pragma once
#include <glm.hpp>
#include <unordered_map>

class InputManager
{
public:
	InputManager();
	~InputManager();

	void pressKey(unsigned int keyID);
	void releaseKey(unsigned int keyID);
	
	bool isKeyPressed(unsigned int keyID);
	void setMouseCoords(float x, float y);

	glm::vec2 getMouseCoords() const { return _mouseCoords; }

private:
	std::unordered_map<unsigned int, bool> _keyMap;
	glm::vec2 _mouseCoords;
};

