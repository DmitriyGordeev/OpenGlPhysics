#pragma once
#include "Figure.h"

class Circle : public Figure
{
public:
	Circle() : Figure()
	{
		_boundType = HitboxType::CIRCLE;
	}

	Circle(float x, float y, float radius) : Figure(x, y)
	{
		_geo.z = 2 * radius;
		_geo.w = 2 * radius;
		_boundType = HitboxType::CIRCLE;
	}

	Circle(const glm::vec2& pos, float radius) : Figure(pos)
	{
		_geo.z = 2 * radius;
		_geo.w = 2 * radius;
		_boundType = HitboxType::CIRCLE;
	}

	~Circle() = default;

	glm::vec2 getCenter() const { return glm::vec2(_geo.x, _geo.y); }
	float getRadius() const { return _geo.z / 2; }

	void lineReflection(const glm::vec2& A, const glm::vec2& B) override;

	void draw(ObjectsGroup& objGroup) override;
	void collision(Figure* pfig) override;
};

