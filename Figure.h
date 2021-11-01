#pragma once
#include "ObjectsGroup.h"
#include <glm.hpp>
#include <gtx\transform.hpp>

enum struct HitboxType
{
	CIRCLE,
	BOX,
	TRIANGLE,
	ELLIPSIS
};

class Figure
{
public:
	Figure();
	Figure(float x, float y);
	explicit Figure(const glm::vec2& pos);
	explicit Figure(const glm::vec4& destRect);
	virtual ~Figure();

	void setPos(float x, float y);
	void setVel(float vx, float vy);
	void setVel(const glm::vec2& vel);
	void setAngle(float angle);
	void setAngleVel(float angleVel);
	void transform(const glm::mat2x2& trMat);
	void applyForce(const glm::vec2& impulse);

	float mass() const { return _mass; }
	void setMass(float mass) { _mass = mass; }
	void move();
	void rotate();

	glm::vec2 getVel() const { return _vel; }
	glm::vec2 getPos() const { glm::vec2 center(_geo.x, _geo.y); return center; }
	glm::vec2 getSize() const { glm::vec2 size(_geo.z, _geo.w); return size; }
	float getAngle() const { return _angle; }
	float getAngleVel() const { return _angleVel; }
	HitboxType getBoundType() const { return _boundType; }

	glm::vec2* getDots();

	virtual void collision(Figure* pFig) = 0;
	virtual void lineReflection(const glm::vec2& A, const glm::vec2& B);
	virtual void draw(ObjectsGroup& objGroup);

	static float grav;

protected:
	glm::vec4 _geo{};
	glm::vec2 _dots[4]{};
	glm::vec2 _vel{};
	float _angle;
	float _angleVel;
	float _mass;

	glm::mat2x2 _trMat{};

	HitboxType _boundType;
};



