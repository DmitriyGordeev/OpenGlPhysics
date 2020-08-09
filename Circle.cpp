#include "Circle.h"
#include "TextureLoader.h"
#include <gtx\rotate_vector.hpp>
#include "Math2D.h"
#include "Box.h"

#include <iostream>

void Circle::draw(ObjectsGroup& objGroup)
{
	Color color;
	color.r = 255; color.g = 255; color.b = 255, color.a = 255;

	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static GLTexture texture = TextureLoader::getTexture("textures/circle.png");

	objGroup.addInGroupTransform(_geo, uv, _trMat, texture.id, 0, color);
}

void Circle::collision(Figure* pfig)
{
	if (pfig->getBoundType() == BoundType::CIRCLE)
	{
		glm::vec2 center = getCenter();
		glm::vec2 pfigCenter = pfig->getPos();

		glm::vec2 connectionLine = pfigCenter - center;
		connectionLine = glm::normalize(connectionLine);

		float radius = getRadius();
		float pfigRadius = (pfig->getSize().x) / 2;

		glm::vec2 vel1 = getVel();
		glm::vec2 vel2 = pfig->getVel();
		

		if (glm::distance(center, pfigCenter) <= radius + pfigRadius)
		{
			std::cout << "Circle collided!" << std::endl;

			glm::vec2 vel;
			glm::vec2 pfigVel;

			float p = 2 * (glm::dot(vel1, connectionLine) - glm::dot(vel2, connectionLine)) / (_mass + pfig->mass());

			vel = vel1 - p * pfig->mass() * connectionLine;
			pfigVel = vel2 + p * _mass * connectionLine;

			setVel(vel.x, vel.y);
			pfig->setVel(pfigVel.x, pfigVel.y);
		}
	}
	else if (pfig->getBoundType() == BoundType::BOX)
	{
		glm::vec2* box_dots = pfig->getDots();
		glm::vec2 box_center = pfig->getPos();

		float box_angle = pfig->getAngle();

		//getting local ABCD vectors from box_center:
		glm::vec2 A = box_dots[0] - box_center;
		glm::vec2 B = box_dots[1] - box_center;
		glm::vec2 C = box_dots[2] - box_center;
		glm::vec2 D = box_dots[3] - box_center;

		//moving circle center by box_center:
		glm::vec2 M = getCenter() - box_center; //M - transformed center pos of the circle
		glm::vec2 rotated_circle_Vel = glm::rotate(getVel(), -box_angle);

		//rotating everything to Axis-Aligned Box:
		M = glm::rotate(M, -box_angle);

		A = glm::rotate(A, -box_angle);
		B = glm::rotate(B, -box_angle);
		C = glm::rotate(C, -box_angle);
		D = glm::rotate(D, -box_angle);

		glm::vec2 box_size = pfig->getSize();
		float r = _geo.z / 2;
		if ((M.x <= C.x + r) && (M.x > C.x))
		{
			if ((M.y <= C.y + r) && (M.y >= D.y - r))
			{
				rotated_circle_Vel.x *= -1.0f;
				setVel(glm::rotate(rotated_circle_Vel, box_angle));
			}	
		}
		else if ((M.x >= B.x - r) && (M.x < B.x))
		{
			if ((M.y <= C.y + r) && (M.y >= D.y - r))
			{
				rotated_circle_Vel.x *= -1.0f;
				setVel(glm::rotate(rotated_circle_Vel, box_angle));
			}
		}
		else if ((M.y <= B.y + r) && (M.y > B.y))
		{
			if ((M.x >= B.x - r) && (M.x <= C.x + r))
			{
				rotated_circle_Vel.y *= -1.0f;
				setVel(glm::rotate(rotated_circle_Vel, box_angle));
			}
		}
		else if ((M.y >= A.y - r) && (M.y < A.y))
		{
			if ((M.x >= B.x - r) && (M.x <= C.x + r))
			{
				rotated_circle_Vel.y *= -1.0f;
				setVel(glm::rotate(rotated_circle_Vel, box_angle));
			}
		}

	}
}

void Circle::lineReflection(const glm::vec2& A, const glm::vec2& B)
{
	float angle = Math2D::getAngle(B - A);

	float friction = 0.02f;

	glm::vec2 rotated_Pos = glm::rotate(glm::vec2(_geo.x, _geo.y), -angle);
	glm::vec2 rotated_Vel = glm::rotate(getVel(), -angle);
	glm::vec2 rotated_A = glm::rotate(A, -angle);
	glm::vec2 rotated_B = glm::rotate(B, -angle);

	//acceleration (gravity and friction):
	float accel = grav * (sinf(angle) - friction * cosf(angle));

	if ((rotated_Pos.x >= rotated_A.x - _geo.z) && (rotated_Pos.x <= rotated_B.x + _geo.z))
	{
		if (abs(rotated_Pos.y - rotated_A.y) <= 1.0f + _geo.z / 2)
		{
			//Decreasing normal velocity after impact:
			if (abs(rotated_Vel.y) > 0.1f) 
				rotated_Vel.y = -(rotated_Vel.y - 0.1f * rotated_Vel.y);
			else
				rotated_Vel.y = 0.0f;
				
			//Defining angle velocity and direction:
			float angleVel = -2 * rotated_Vel.x / _geo.z / 2;

			//Reducing tangens velocity due to friction:
			if (abs(rotated_Vel.x) > 0.1f)
				rotated_Vel.x -= accel;
			else
				rotated_Vel.x = 0.0f;
	
			//Rotate velocity back:
			glm::vec2 newPos = glm::rotate(rotated_Pos, angle);
			glm::vec2 newVel = glm::rotate(rotated_Vel, angle);
			setPos(newPos.x, newPos.y);
			setVel(newVel.x, newVel.y);

			//Surface reaction:
			glm::vec2 reaction = glm::rotate(glm::vec2(0.0f, _mass * grav * cosf(angle)), angle);
			force(reaction);

			//Angle velocity direction and value:
		    setAngleVel(angleVel);

			std::cout << "pos: " << _geo.x << "  " << _geo.y;
			std::cout << " ; velocity: " << newVel.x << "  " << newVel.y << std::endl;
		}
	}
}