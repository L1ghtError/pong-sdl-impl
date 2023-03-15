#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include "GameBackend.hpp"

int main(int argc, char** argv) {
	GameBackend gameBackend(750,500);
	gameBackend.game_loop();
	return 0;
}