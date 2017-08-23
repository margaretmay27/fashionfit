#pragma once
#include <SDL\SDL.h>
#include <GLEW\glew.h>
#include "Sprite.h"
#include "GLSLRunner.h"
#include "MathLib.h"
#include "ClothObject.h"

enum class GameState {
	PLAY,
	EXIT
};


class MainGame
{
public:
	MainGame();
	MainGame(int width, int height);
	~MainGame();

	void run();

private:
	void initSystems();
	void initShaders();
	void gameLoop();
	void processInput();
	void drawGame();

	SDL_Window* _window;
	int _screenWidth;
	int _screenHeight;
	GameState _gameState;

	//temporary sprites and shaders
	Sprite _sprites[2];
	ClothObject _tempCloth;
	GLSLRunner _shaderProgram;
	GLuint* _matricies;
};

