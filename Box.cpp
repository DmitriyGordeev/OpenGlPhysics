#include "Box.h"
#include "TextureLoader.h"
#include <gtx\rotate_vector.hpp>

void Box::draw(ObjectsGroup& objGroup)
{
	Color color;
	color.r = 255; color.g = 255; color.b = 255, color.a = 255;

	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static GLTexture texture = TextureLoader::getTexture("textures/box.png");

	objGroup.addInGroupTransform(_geo, uv, _trMat, texture.id, 0, color);
}

void Box::collision(Figure* pfig)
{

}

