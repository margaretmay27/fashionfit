#include "MainGame.h"
#include <iostream>
#include <string>

#include "Error.h"

float temp = 2.0f;

MainGame::MainGame(){
	_window = nullptr;
	_screenWidth = 1024;
	_screenHeight = 768;
	_gameState = GameState::PLAY;
}

MainGame::MainGame(int width,int height) {
	_window = nullptr;
	_screenWidth = width;
	_screenHeight = height;
	_gameState = GameState::PLAY;
}

MainGame::~MainGame(){

}

void MainGame::run() {
	initSystems();

	_sprites[0].init(-0.5, -0.5, 0.5, 0.5);
	_sprites[1].init(0.0, 0.0, 1.0, 1.0);

	_tempCloth.init(20, 20, 1.0f, 1.0f,3.0f);
	Vec4 v = Vec4(1, 1, 1);
	(v + Vec4(0.5, 0.25, 0)).print();
	(Vec4(1, 1, 1) - Vec4(0.5, 0.25, 0)).print();

	v *= 2;
	v.print();
	v += Vec3(1, 1, 1);
	v.print();
	v += Vec4(1, 1, 1,0.75);
	v.print();

	gameLoop();
}

void MainGame::initSystems() {
	SDL_Init(SDL_INIT_EVERYTHING);

	_window = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight,SDL_WINDOW_OPENGL);

	if (_window == nullptr) {
		fatalError("SDL Window Could Not Be Created");
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(_window);
	if (glContext == nullptr) {
		fatalError("SDL_GL Context Could Not Be Created");
	}

	
	GLenum error=glewInit();
	if (error != GLEW_OK) {
		fatalError("GLEW Could Not Be Initialized");
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	
	initShaders();
}

void MainGame::initShaders() {

	//replace with actual shaders later
	_shaderProgram.compileShaders("Shaders/shader.vertshader","Shaders/shader.fragshader");
	_shaderProgram.addAttribute("vert_pos");
	_shaderProgram.addAttribute("vert_color");
	_shaderProgram.linkShaders();
}


void MainGame::gameLoop() {
	while (_gameState != GameState::EXIT) {
		processInput();
		drawGame();
	}
}


void MainGame::processInput() {
	SDL_Event evnt;

	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
			case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;
			case SDL_MOUSEMOTION:
				if (evnt.motion.state == SDL_PRESSED) {
					temp = evnt.motion.x*100.0f / _screenWidth;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (evnt.button.button == SDL_BUTTON_LEFT) {
					temp = evnt.motion.x*100.0f / _screenWidth;
				}
				break;
		}
	}
}

void MainGame::drawGame() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_tempCloth.update();

	//temporary sprites colored and white
	_shaderProgram.use();
	
	GLuint _transformPointer = _shaderProgram.getUniform("uni_change");
	//glUniform1f(_transformPointer, 0.1f);
	GLfloat glArray[16];

	(MathLib::PerspectiveMatrix(60.0f, 4.0f / 3.0f, 1.0f, 100.0f)*MathLib::TransformMatrix(0.0f, -temp/4.0f, -temp)).toGLArray(glArray);

	glUniformMatrix4fv(_transformPointer, 1, GL_FALSE, glArray);
	//ScaleMatrix(0.5f, 0.5f, 0.5f)

	//_sprites[0].draw();
	
	_tempCloth.draw();

	_shaderProgram.unuse();
	
	
	//_sprites[1].draw();
	

	SDL_GL_SwapWindow(_window);
}
