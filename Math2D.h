#pragma once
#include <glm.hpp>
#include <cmath>
#include <string>

#define PI 3.141592

class Math2D
{
public:
	static glm::vec2 vec2rand();
	static float getAngle(const glm::vec2& vector2D);
	static float distLineDot(glm::vec2 A, glm::vec2 B, glm::vec2 Dot);
	static void showVec(const std::string& name, const glm::vec2& vec);
};

