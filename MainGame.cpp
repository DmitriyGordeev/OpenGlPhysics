#include "MainGame.h"
#include "ImageLoader.h"
#include "errors.h"
#include "Math2D.h"

#include <chrono>
#include <thread>

#include <gtx\transform.hpp>


MainGame::MainGame()
{
	_window = nullptr;
	_screenWidth = 640;
	_screenHeight = 640;
	_gameState = GameState::PLAY;
	_camera.init(_screenWidth, _screenHeight);
    _scene = nullptr;
	_time = 0.0f;
	_dt = 0.01f;
}

MainGame::~MainGame()
{
    delete _scene;
//    TODO
}

void MainGame::run()
{
    initSystems();
    _scene->setup();
    gameLoop();
}

void MainGame::initSystems()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	_window = SDL_CreateWindow(
		"MyPhysics",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		_screenWidth,
		_screenHeight,
		SDL_WINDOW_OPENGL
		);

	if (_window == nullptr)
		fatal("SDL window could not be created!");

	SDL_GLContext glContext = SDL_GL_CreateContext(_window);
	if (glContext == nullptr)
		fatal("SDL GL context could not be created!");

	GLenum error = glewInit();
	if (error != GLEW_OK)
		fatal("could not initialize glew");

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	//Enable Alpha Blend
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Anti-Aliasing:
	glEnable(GL_MULTISAMPLE);

	initShaders();
	_objectsGroup.init();
    _scene = new Scene(&_objectsGroup);
}

void MainGame::initShaders()
{
	_shader.compile("shaders/shader.vs", "shaders/shader.ps");
	_shader.addAttribute("vertexPosition");
	_shader.addAttribute("vertexColor");
	_shader.addAttribute("vertexUV");
	_shader.link();
}

void MainGame::processInput()
{
	SDL_Event _event;
	float CamSpeed = 20.0f;
	float ScaleSpeed = 0.01f;

	while (SDL_PollEvent(&_event))
	{
		switch (_event.type)
		{
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;

		case SDL_MOUSEMOTION:
			_input.setMouseCoords(_event.motion.x, _event.motion.y);
			break;

		case SDL_KEYDOWN:
			_input.pressKey(_event.key.keysym.sym);
			break;

		case SDL_KEYUP:
			_input.releaseKey(_event.key.keysym.sym);
			break;

		case SDL_MOUSEBUTTONDOWN:
			_input.pressKey(_event.button.button);
			break;

		case SDL_MOUSEBUTTONUP:
			_input.releaseKey(_event.button.button);
			break;

		}
	}

	//Keys process input
	if (_input.isKeyPressed(SDLK_w))
		_camera.setPosition(_camera.getPos() + glm::vec2(0.0, CamSpeed));

	if (_input.isKeyPressed(SDLK_s))
		_camera.setPosition(_camera.getPos() + glm::vec2(0.0, -CamSpeed));

	if (_input.isKeyPressed(SDLK_a))
		_camera.setPosition(_camera.getPos() + glm::vec2(-CamSpeed, 0.0));

	if (_input.isKeyPressed(SDLK_d))
		_camera.setPosition(_camera.getPos() + glm::vec2(CamSpeed, 0.0));

	if (_input.isKeyPressed(SDLK_q))
		_camera.setScale(_camera.getScale() - ScaleSpeed);

	if (_input.isKeyPressed(SDLK_e))
		_camera.setScale(_camera.getScale() + ScaleSpeed);

	if (_input.isKeyPressed(SDL_BUTTON_LEFT))
	{
		glm::vec2 mouseCoords = _input.getMouseCoords();
		_camera.convertToWorldCoords(mouseCoords);
	}
}

void MainGame::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		_time += _dt;

		processInput();
		_camera.update();
		drawGame();

		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

void MainGame::drawGame()
{
	//Set the base depth to 1.0
	glClearDepth(1.0f);
	//Clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_shader.use();

	glActiveTexture(GL_TEXTURE0);

	//Get texture variable from shaders
	GLint textureLocation = _shader.getUniformLocation("mySampler");
	glUniform1i(textureLocation, 0);

	GLint pLocation = _shader.getUniformLocation("P");
	glm::mat4 cameraMatrix = _camera.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	// Draws all figures
    _objectsGroup.cleanUp();
    _scene->draw();
	_objectsGroup.post();
	_objectsGroup.renderGroup();

	glBindTexture(GL_TEXTURE_2D, 0);
	_shader.unuse();

	//swap buffers and draw everything on the screen
	SDL_GL_SwapWindow(_window);
}
