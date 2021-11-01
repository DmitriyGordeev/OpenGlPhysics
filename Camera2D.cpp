#include "Camera2D.h"


Camera2D::Camera2D() : _needMatrixUpdate(true),
                       _scale(0.3f),
                       _pos(0.0f, 0.0f),
                       _cameraMatrix(1.0f),
                       _orthMatrix(1.0f),
                       _screenWidth(640),
                       _screenHeight(480)
{
}

Camera2D::~Camera2D()
{
}

void Camera2D::init(int screenWidth, int screenHeight)
{
	_screenWidth = screenWidth;
	_screenHeight = screenHeight;

    _orthMatrix = glm::ortho(0.0f, (float)_screenWidth, 0.0f, (float)_screenHeight);
}

void Camera2D::update()
{
	if (_needMatrixUpdate)
	{
		glm::vec3 translate(-_pos.x + _screenWidth / 2, -_pos.y + _screenHeight / 2, 0.0f);
		_cameraMatrix = glm::translate(_orthMatrix, translate);

		glm::vec3 scale(_scale, _scale, 0.0f);
		_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * _cameraMatrix;

		//translate = glm::vec3(_screenWidth / 2, _screenHeight / 2, 0.0f);
		_needMatrixUpdate = false;
	}
}

void Camera2D::convertToWorldCoords(glm::vec2& screenCoords)
{
	// 0 - center
	screenCoords -= glm::vec2(_screenWidth / 2, _screenHeight / 2);
	screenCoords /= _scale;
	screenCoords += _pos;
}
