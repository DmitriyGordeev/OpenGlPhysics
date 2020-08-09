#pragma once
#include "ObjectsGroup.h"
#include <glm.hpp>
#include <gtx\transform.hpp>

enum struct BoundType
{
	CIRCLE,
	BOX,
	TRIANGLE,
	ELLIPS
};

class Figure
{
public:
	Figure();
	Figure(float x, float y);
	Figure(const glm::vec2& pos);
	Figure(const glm::vec4& destRect);
	virtual ~Figure();

	void setPos(float x, float y);
	void setVel(float vx, float vy);
	void setVel(glm::vec2 vel);
	void setAngle(float angle);
	void setAngleVel(float angleVel);
	void transform(const glm::mat2x2& trMat);
	void force(const glm::vec2 force);

	float mass() { return _mass; }
	void setMass(float mass) { _mass = mass; }
	void move();
	void rotate();

	glm::vec2 getVel() const { return _vel; }
	glm::vec2 getPos() const { glm::vec2 center(_geo.x, _geo.y); return center; }
	glm::vec2 getSize() const { glm::vec2 size(_geo.z, _geo.w); return size; }
	float getAngle() const { return _angle; }
	float getAngleVel() const { return _angleVel; }
	BoundType getBoundType() const { return _boundType; }

	glm::vec2* getDots();

	virtual void collision(Figure* pfig) = 0;
	virtual void lineReflection(const glm::vec2& A, const glm::vec2& B);
	virtual void draw(ObjectsGroup& objGroup);

	static float grav;

protected:
	glm::vec4 _geo;
	glm::vec2 _dots[4];
	glm::vec2 _vel;
	float _angle;
	float _angleVel;
	float _mass;

	glm::mat2x2 _trMat;

	BoundType _boundType;
};



