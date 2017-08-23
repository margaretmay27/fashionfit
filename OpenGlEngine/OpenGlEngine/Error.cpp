#include "Error.h"

#include <cstdlib>
#include <iostream>
#include <SDL\SDL.h>

void fatalError(std::string errorString) {
	std::cout << errorString << "\n" << "Enter any key to quit...";
	int temp;
	std::cin >> temp;
	SDL_Quit();

	exit(125);
}