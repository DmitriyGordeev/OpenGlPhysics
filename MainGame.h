#pragma once
#include <SDL.h>
#include <GL/glew.h>

#include <iostream>
#include <string>

#include "Shaders.h"
#include "Camera2D.h"
#include "InputManager.h"
#include "GLTexture.h"
#include "ObjectsGroup.h"
#include "Box.h"
#include "Circle.h"
#include "Scene.h"

enum class GameState {PLAY, EXIT};
 
class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();
	void initSystems();
	void initShaders();
	void processInput();
	void gameLoop();
	void drawGame();

private:
	void _figuresDraw();

	int _screenWidth;
	int _screenHeight;
	SDL_Window* _window;
	GameState _gameState;

	Shaders _shader;
	Camera2D _camera;
	InputManager _input;

	ObjectsGroup _objectsGroup;

    Scene* _scene;

//	std::vector<Figure*> _pFigures;
//	Box* _groundBox;

	float _time;
	float _dt;
};

