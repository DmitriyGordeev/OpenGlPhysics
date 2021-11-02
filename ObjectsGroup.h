#pragma once
#include <GL\glew.h>
#include <glm.hpp>
#include "Vertex.h"
#include <vector>
#include <memory>


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
public:
	RenderGroup(GLuint Offset, GLuint NV, GLuint Texture)
	{
		offset = Offset;
        numVertexes = NV;
		texture = Texture;
	}

	GLuint offset;
	GLuint numVertexes;
	GLuint texture;
};

class ObjectsGroup
{
public:
	ObjectsGroup();
	~ObjectsGroup();

	void init();
	void cleanUp(ObjectSortType sortType = ObjectSortType::TEXTURE);
	void post();
	void addInGroup(const glm::vec4& destRect, const glm::vec4& uvRect, float angle, GLuint texture, float depth, const Color& color);
	void addInGroupCenter(const glm::vec4& centerRect, const glm::vec4& uvRect, float angle, GLuint texture, float depth, const Color& color);
	void addInGroupTransform(const glm::vec4& centerRect, const glm::vec4& uvRect, const glm::mat2x2& trMat, GLuint texture, float depth, const Color& color);
	void renderGroup();

private:
	void _createRenderGroups();
	void _sortObjects();
	void _createVertexArray();

	static bool _compareFTB(const std::unique_ptr<Object>& a, const std::unique_ptr<Object>& b)
	{
		return (a->depth < b->depth);
	}
	static bool _compareBTF(const std::unique_ptr<Object>& a, const std::unique_ptr<Object>& b)
	{
		return (a->depth > b->depth);
	}
	static bool _compareTEX(const std::unique_ptr<Object>& a, const std::unique_ptr<Object>& b)
	{
		return (a->texture < b->texture);
	}

	GLuint _vbo;
	GLuint _vao;
	
	ObjectSortType _sortType {ObjectSortType::NONE};

	std::vector<std::unique_ptr<Object>> _pObjects;
	std::vector<RenderGroup> _rgs;
};

