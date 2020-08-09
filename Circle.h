#pragma once
#include "Figure.h"

class Circle : public Figure
{
public:
	Circle() : Figure()
	{
		_boundType = BoundType::CIRCLE;
	}
	Circle(float x, float y, float radius) : Figure(x, y)
	{
		_geo.z = 2 * radius;
		_geo.w = 2 * radius;
		_boundType = BoundType::CIRCLE;
	}
	Circle(const glm::vec2& pos, float radius) : Figure(pos)
	{
		_geo.z = 2 * radius;
		_geo.w = 2 * radius;
		_boundType = BoundType::CIRCLE;
	}
	~Circle() {}

	glm::vec2 getCenter() const { return glm::vec2(_geo.x, _geo.y); }
	float getRadius() const { return _geo.z / 2; }

	void lineReflection(const glm::vec2& A, const glm::vec2& B);

	void draw(ObjectsGroup& objGroup);
	void collision(Figure* pfig);

private:

};

