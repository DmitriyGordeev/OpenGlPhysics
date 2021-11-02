#include "Math2D.h"
#include <gtx\rotate_vector.hpp>
#include <iostream>


glm::vec2 Math2D::vec2rand()
{
	float fi = 6.283184 * rand() / RAND_MAX;
	glm::vec2 v(cosf(fi), sinf(fi));
	return v;
}

float Math2D::getAngle(const glm::vec2& vector2D)
{
	float v = glm::length(vector2D);

    // todo: refactor this function

	if (v == 0.0f)
		return 0.0f;

	if (vector2D.x == 0.0f && vector2D.y > 0.0f)
		return PI / 2;

	else if (vector2D.x > 0.0f && vector2D.y == 0.0f)
		return 0.0f;

	else if (vector2D.x < 0.0f && vector2D.y == 0.0f)
		return PI;

	else if (vector2D.x == 0.0f && vector2D.y < 0)
		return 3 * PI / 2;

	else if (vector2D.x > 0.0f && vector2D.y > 0.0f)
		return acosf(vector2D.x / v);

	else if (vector2D.x < 0.0f && vector2D.y > 0.0f)
		return acosf(vector2D.x / v);

	else if (vector2D.x < 0.0f && vector2D.y < 0.0f)
		return 2 * PI - acosf(vector2D.x / v);

	else if (vector2D.x > 0.0f && vector2D.y < 0.0f)
		return 2 * PI - acosf(vector2D.x / v);
}

float Math2D::distLineDot(glm::vec2 A, glm::vec2 B, glm::vec2 Dot)
{
	//Define the angle:
	glm::vec2 tau = B - A;
	float angle = getAngle(tau);

	//Rotating to OX:
	A = glm::rotate(A, -angle);
	B = glm::rotate(B, -angle);
	Dot = glm::rotate(Dot, -angle);
	
	//Calculating range (by OY):
	float range = 0.0f;

	if (((Dot.x < A.x) && (Dot.x < B.x)) || ((Dot.x > A.x) && (Dot.x > B.x)))
		return -1.0f;

	std::cout << abs(Dot.y) << std::endl;

	return abs(Dot.y);
}

void Math2D::showVec(const std::string& name, const glm::vec2& vec)
{
	std::cout << name + "= " << vec.x << " " << vec.y << std::endl;
}