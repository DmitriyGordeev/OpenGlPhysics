#include "ObjectsGroup.h"
#include <algorithm>

#include <gtx\rotate_vector.hpp>

ObjectsGroup::ObjectsGroup()
{
	_vbo = 0;
	_vao = 0;
}

ObjectsGroup::~ObjectsGroup() = default;

void ObjectsGroup::init()
{
	_createVertexArray();
}

void ObjectsGroup::cleanUp(ObjectSortType sortType /* = TEXTURE */)
{
	_sortType = sortType;

//	for (int i = 0; i < _pObjects.size(); i++)
//		delete _pObjects[i];
    _pObjects.clear();

	_rgs.clear();
}

void ObjectsGroup::post()
{
	_sortObjects();
	_createRenderGroups();
	_pObjects.clear();
}

void ObjectsGroup::addInGroup(const glm::vec4& destRect, const glm::vec4& uvRect, float angle, GLuint texture, float depth, const Color& color)
{
//	Object* newObject = new Object;
    std::unique_ptr<Object> newObject = std::make_unique<Object>();

    newObject->texture = texture;
    newObject->depth = depth;

	//Rotating by angle:
	glm::vec2 topLeft(destRect.x, destRect.y + destRect.w);
	glm::vec2 topRight(destRect.x + destRect.z, destRect.y + destRect.w);
	glm::vec2 bottomLeft(destRect.x, destRect.y);
	glm::vec2 bottomRight(destRect.x + destRect.z, destRect.y);

	glm::vec2 uv_topLeft(uvRect.x, uvRect.y + uvRect.w);
	glm::vec2 uv_topRight(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
	glm::vec2 uv_bottomLeft(uvRect.x, uvRect.y);
	glm::vec2 uv_bottomRight(uvRect.x + uvRect.z, uvRect.y);

	topLeft = glm::rotate(topLeft, angle);
	topRight = glm::rotate(topRight, angle);
	bottomLeft = glm::rotate(bottomLeft, angle);
	bottomRight = glm::rotate(bottomRight, angle);

	//uv_topLeft     = glm::rotate(uv_topLeft, angle);
	//uv_topRight    = glm::rotate(uv_topRight, angle);
	//uv_bottomLeft  = glm::rotate(uv_bottomLeft, angle);
	//uv_bottomRight = glm::rotate(uv_bottomRight, angle);

	//Assigning values to object properties:
    newObject->topLeft.color = color;
    newObject->topLeft.setPos(topLeft.x, topLeft.y);
    newObject->topLeft.setUV(uv_topLeft.x, uv_topLeft.y);

    newObject->bottomLeft.color = color;
    newObject->bottomLeft.setPos(bottomLeft.x, bottomLeft.y);
    newObject->bottomLeft.setUV(uv_bottomLeft.x, uv_bottomLeft.y);

    newObject->topRight.color = color;
    newObject->topRight.setPos(topRight.x, topRight.y);
    newObject->topRight.setUV(uv_topRight.x, uv_topRight.y);

    newObject->bottomRight.color = color;
    newObject->bottomRight.setPos(bottomRight.x, bottomRight.y);
    newObject->bottomRight.setUV(uv_bottomRight.x, uv_bottomRight.y);

	_pObjects.push_back(std::move(newObject));
}

void ObjectsGroup::addInGroupCenter(const glm::vec4& centerRect, const glm::vec4& uvRect, float angle, GLuint texture, float depth, const Color& color)
{
    std::unique_ptr<Object> newObject = std::make_unique<Object>();
	newObject->texture = texture;
	newObject->depth = depth;

	float x = centerRect.x;
	float y = centerRect.y;
	float w = centerRect.z;
	float h = centerRect.w;
	
	//Rotating by angle:
	glm::vec2 topLeft(x - w/2, y + h/2);
	glm::vec2 topRight(x + w/2, y + h/2);
	glm::vec2 bottomLeft(x - w/2, y - h/2);
	glm::vec2 bottomRight(x + w/2, y - h/2);

	topLeft = glm::rotate(topLeft, angle);
	topRight = glm::rotate(topRight, angle);
	bottomLeft = glm::rotate(bottomLeft, angle);
	bottomRight = glm::rotate(bottomRight, angle);

	//Assigning values to object properties:
	newObject->topLeft.color = color;
	newObject->topLeft.setPos(topLeft.x, topLeft.y);
	newObject->topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

	newObject->bottomLeft.color = color;
	newObject->bottomLeft.setPos(bottomLeft.x, bottomLeft.y);
	newObject->bottomLeft.setUV(uvRect.x, uvRect.y);

	newObject->topRight.color = color;
	newObject->topRight.setPos(topRight.x, topRight.y);
	newObject->topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

	newObject->bottomRight.color = color;
	newObject->bottomRight.setPos(bottomRight.x, bottomRight.y);
	newObject->bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

	_pObjects.push_back(std::move(newObject));
}

void ObjectsGroup::addInGroupTransform(const glm::vec4& centerRect, const glm::vec4& uvRect, glm::mat2x2 trMat, GLuint texture, float depth, const Color& color)
{
    std::unique_ptr<Object> newObject = std::make_unique<Object>();
	newObject->texture = texture;
	newObject->depth = depth;

	float x = centerRect.x;
	float y = centerRect.y;
	float w = centerRect.z;
	float h = centerRect.w;

	//Transformation matrix:
	glm::vec2 center(centerRect.x, centerRect.y);

	glm::vec2 topLeft(-w / 2, h / 2);
	glm::vec2 topRight(w / 2, h / 2);
	glm::vec2 bottomLeft(-w / 2, -h / 2);
	glm::vec2 bottomRight(w / 2, -h / 2);

	topLeft = trMat * topLeft;
	topRight = trMat * topRight;
	bottomLeft = trMat * bottomLeft;
	bottomRight = trMat * bottomRight;

	//Assigning values to object properties:
	newObject->topLeft.color = color;
	newObject->topLeft.setPos((center + topLeft).x, (center + topLeft).y);
	newObject->topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

	newObject->bottomLeft.color = color;
	newObject->bottomLeft.setPos((center + bottomLeft).x, (center + bottomLeft).y);
	newObject->bottomLeft.setUV(uvRect.x, uvRect.y);

	newObject->topRight.color = color;
	newObject->topRight.setPos((center + topRight).x, (center + topRight).y);
	newObject->topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

	newObject->bottomRight.color = color;
	newObject->bottomRight.setPos((center + bottomRight).x, (center + bottomRight).y);
	newObject->bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

	_pObjects.push_back(std::move(newObject));
}

void ObjectsGroup::renderGroup()
{
	glBindVertexArray(_vao);

	for (int i = 0; i < _rgs.size(); i++)
	{
		glBindTexture(GL_TEXTURE_2D, _rgs[i].texture);
		glDrawArrays(GL_TRIANGLES, _rgs[i].offset, _rgs[i].numVertexes);
	}

	glBindVertexArray(0);
}

void ObjectsGroup::_createRenderGroups()
{
	std::vector<Vertex> vertexes;
	vertexes.resize(_pObjects.size() * 6);

	if (_pObjects.empty())
		return;

	int offset = 0;
	int cv = 0; // current vertex
	_rgs.emplace_back(0, 6, _pObjects[0]->texture);
    vertexes[cv++] = _pObjects[0]->topLeft;
    vertexes[cv++] = _pObjects[0]->bottomLeft;
    vertexes[cv++] = _pObjects[0]->bottomRight;
    vertexes[cv++] = _pObjects[0]->bottomRight;
    vertexes[cv++] = _pObjects[0]->topRight;
    vertexes[cv++] = _pObjects[0]->topLeft;
	offset += 6;

	for (int co = 1; co < _pObjects.size(); co++)
	{
		if (_pObjects[co]->texture != _pObjects[co - 1]->texture)
			_rgs.emplace_back(offset, 6, _pObjects[co]->texture);
		else
			_rgs.back().numVertexes += 6;

        vertexes[cv++] = _pObjects[co]->topLeft;
        vertexes[cv++] = _pObjects[co]->bottomLeft;
        vertexes[cv++] = _pObjects[co]->bottomRight;
        vertexes[cv++] = _pObjects[co]->bottomRight;
        vertexes[cv++] = _pObjects[co]->topRight;
        vertexes[cv++] = _pObjects[co]->topLeft;
		offset += 6;
	}

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, vertexes.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertexes.size() * sizeof(Vertex), vertexes.data());

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ObjectsGroup::_sortObjects()
{
	switch (_sortType) {
	case ObjectSortType::FRONT_TO_BACK:
		std::stable_sort(_pObjects.begin(), _pObjects.end(), _compareFTB);
		break;

	case ObjectSortType::BACK_TO_FRONT:
		std::stable_sort(_pObjects.begin(), _pObjects.end(), _compareBTF);
		break;

	case ObjectSortType::TEXTURE:
		std::stable_sort(_pObjects.begin(), _pObjects.end(), _compareTEX);
		break;

    default:
        break;
	}
}

void ObjectsGroup::_createVertexArray()
{
	if (_vao == 0)
		glGenVertexArrays(1, &_vao);
	
	glBindVertexArray(_vao);

	if(_vbo == 0)
		glGenBuffers(1, &_vbo);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);

	//Attributes of vertex
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	//Where our vertexData in vertexBuffer
	//index, dimensions, type, is_normalize?, stride, pointer (offset in bytes) 
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

	glBindVertexArray(0);
}