#include "Figure.h"
#include "TextureLoader.h"
#include <gtx\rotate_vector.hpp>
#include "Math2D.h"
#include <iostream>

float Figure::grav = 0.4f;

Figure::Figure()
{
	_geo = glm::vec4(0.0f, 0.0f, 50.0f, 50.0f);
	_angle = 0.0f;

	_vel.x = 0.0f; _vel.y = 0.0f;
	_angleVel = 0.0f;
	_mass = 1.0f;
}

Figure::Figure(float x, float y)
{
	_geo.x = x;
	_geo.y = y;
	_geo.z = 50.0f;
	_geo.w = 50.0f;

	_angle = 0.0f;

	_vel.x = 0.0f; _vel.y = 0.0f;
	_angleVel = 0.0f;
	_mass = 1.0f;
}

Figure::Figure(const glm::vec2& pos)
{
	_geo.x = pos.x;
	_geo.y = pos.y;
	_geo.z = 50.0f;
	_geo.w = 50.0f;

	_angle = 0.0f;

	_vel.x = 0.0f; _vel.y = 0.0f;
	_angleVel = 0.0f;
	_mass = 1.0f;
}

Figure::Figure(const glm::vec4& destRect)
{
	_geo = destRect;
	_angle = 0.0f;

	_vel.x = 0.0f; _vel.y = 0.0f;
	_angleVel = 0.0f;
	_mass = 1.0f;
}

Figure::~Figure()
{
}

void Figure::draw(ObjectsGroup& objGroup)
{
	Color color;
	color.r = 255; color.g = 255; color.b = 255, color.a = 255;

	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static GLTexture texture = TextureLoader::getTexture("textures/circle.png");

	objGroup.addInGroupTransform(_geo, uv, _trMat, texture.id, 0, color);
}

glm::vec2* Figure::getDots()
{
	glm::vec2 A(-_geo.z / 2, -_geo.w / 2);
	glm::vec2 B(-_geo.z / 2, _geo.w / 2);
	glm::vec2 C( _geo.z / 2, _geo.w / 2);
	glm::vec2 D( _geo.z / 2, -_geo.w / 2);

	A = glm::rotate(A, _angle);
	B = glm::rotate(B, _angle);
	C = glm::rotate(C, _angle);
	D = glm::rotate(D, _angle);

	A.x += _geo.x;
	A.y += _geo.y;

	B.x += _geo.x;
	B.y += _geo.y;

	C.x += _geo.x;
	C.y += _geo.y;

	D.x += _geo.x;
	D.y += _geo.y;

	_dots[0] = A;
	_dots[1] = B;
	_dots[2] = C;
	_dots[3] = D;

	return _dots;
}

void Figure::setPos(float x, float y)
{
	_geo.x = x;
	_geo.y = y;
}

void Figure::setVel(float vx, float vy)
{
	_vel.x = vx;
	_vel.y = vy;
}

void Figure::setVel(glm::vec2 vel)
{
	_vel = vel;
}

void Figure::setAngle(float angle)
{
	_angle = angle;

	glm::mat2x2 rotor(
		cosf(_angle), sinf(_angle),
		-sinf(_angle), cosf(_angle));

	_trMat = rotor;
}

void Figure::setAngleVel(float angleVel)
{
	_angleVel = angleVel;
}

void Figure::transform(const glm::mat2x2& trMat)
{
	_trMat = trMat;
}

void Figure::force(const glm::vec2 force)
{
	if (_mass != 0.0f)
		_vel += force / _mass;
}

void Figure::move()
{
	_geo.x += _vel.x;
	_geo.y += _vel.y; 
}

void Figure::rotate()
{
	_angle += _angleVel;

	glm::mat2x2 rotor(
		cosf(_angle), sinf(_angle),
		-sinf(_angle), cosf(_angle));

	_trMat = rotor;
}

void Figure::lineReflection(const glm::vec2& A, const glm::vec2& B)
{
	float angle = Math2D::getAngle(B - A);

	glm::vec2 rotated_Pos = glm::rotate(glm::vec2(_geo.x, _geo.y), -angle);
	glm::vec2 rotated_Vel = glm::rotate(getVel(), -angle);
	glm::vec2 rotated_A = glm::rotate(A, -angle);
	glm::vec2 rotated_B = glm::rotate(B, -angle);
	
	if ((rotated_Pos.x >= rotated_A.x) && (rotated_Pos.x <= rotated_B.x))
	{
		std::cout << "Range = " << abs(rotated_Pos.y - rotated_A.y) << std::endl;

		if (abs(rotated_Pos.y - rotated_A.y) <= 10.0f)
		{
			rotated_Vel.y = -rotated_Vel.y;

			//rotate velocity back:
			glm::vec2 newVel = glm::rotate(rotated_Vel, angle);
			std::cout << "LINECollided!:  " << "newVel.x = " << newVel.x << " newVel.y = " << newVel.y << std::endl;
			setVel(newVel.x, newVel.y);
		}
	}
	
}