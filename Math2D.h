#pragma once
#include <glm.hpp>
#include <math.h>
#include <string>

#define PI 3.141592

class Math2D
{
public:
	static glm::vec2 vec2rand();
	static float getAngle(glm::vec2 vector2D);
	static float distLineDot(glm::vec2 A, glm::vec2 B, glm::vec2 Dot);
	static void showVec(std::string name, glm::vec2 vec);
};

