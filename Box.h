#pragma once
#include "Figure.h"

class Box : public Figure
{
public:
	Box() : Figure() 
	{
		_boundType = BoundType::BOX;
	}
	Box(float x, float y) : Figure(x, y) 
	{
		_boundType = BoundType::BOX;
	}
	Box(float x, float y, float a) : Figure(x, y)
	{
		_boundType = BoundType::BOX;
		_geo.z = a;
		_geo.w = a;
	}
	Box(float x, float y, float w, float h) : Figure(x, y) 
	{
		_boundType = BoundType::BOX;
		_geo.z = w;
		_geo.w = h;
	}
	Box(const glm::vec2& pos) : Figure(pos) 
	{
		_boundType = BoundType::BOX;
	}
	Box(const glm::vec2& pos, float a) : Figure(pos)
	{
		_boundType = BoundType::BOX;
		_geo.z = a;
		_geo.w = a;
	}
	Box(const glm::vec2& pos, float w, float h) : Figure(pos)
	{
		_boundType = BoundType::BOX;
		_geo.z = w;
		_geo.w = h;
	}
	Box(const glm::vec2& pos, const glm::vec2& size) : Figure(pos)
	{
		_boundType = BoundType::BOX;
		_geo.z = size.x;
		_geo.y = size.y;
	}
	Box(const glm::vec4& destRect) : Figure(destRect) { _boundType = BoundType::BOX; }

	~Box() {}

	void draw(ObjectsGroup& objGroup);

	void collision(Figure* pfig);

private:
};

