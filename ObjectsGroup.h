#pragma once
#include <GL\glew.h>
#include <glm.hpp>
#include "Vertex.h"
#include <vector>


enum class ObjectSortType 
{
	NONE,
	FRONT_TO_BACK,
	BACK_TO_FRONT,
	TEXTURE
};

struct Object 
{
	Vertex topLeft;
	Vertex topRight;
	Vertex bottomLeft;
	Vertex bottomRight;

	float depth;
	GLuint texture;
};

class RenderGroup
{
	//stores offset in vertex array object
public:
	RenderGroup(GLuint Offset, GLuint NV, GLuint Texture)
	{
		offset = Offset;
		numVerticies = NV;
		texture = Texture;
	}

	GLuint offset;
	GLuint numVerticies;
	GLuint texture;
};

class ObjectsGroup
{
public:
	ObjectsGroup();
	~ObjectsGroup();

	void init();
	void pre(ObjectSortType sortType = ObjectSortType::TEXTURE);
	void post();
	void addInGroup(const glm::vec4& destRect, const glm::vec4& uvRect, float angle, GLuint texture, float depth, const Color& color);
	void addInGroupCenter(const glm::vec4& centerRect, const glm::vec4& uvRect, float angle, GLuint texture, float depth, const Color& color);
	void addInGroupTransform(const glm::vec4& centerRect, const glm::vec4& uvRect, glm::mat2x2 trMat, GLuint texture, float depth, const Color& color);
	void renderGroup();

private:
	void _createRenderGroups();
	void _sortObjects();
	void _createVertexArray();

	static bool _compareFTB(Object* a, Object* b)
	{
		return (a->depth < b->depth);
	}
	static bool _compareBTF(Object* a, Object* b)
	{
		return (a->depth > b->depth);
	}
	static bool _compareTEX(Object* a, Object* b)
	{
		return (a->texture < b->texture);
	}

	GLuint _vbo;
	GLuint _vao;
	
	ObjectSortType _sortType;

	std::vector<Object*> _pObjects;
	std::vector<RenderGroup> _rgs;
};

