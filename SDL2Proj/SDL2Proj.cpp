#include "Game_Backend.hpp"

void init_sdl_librarys() {
	//initialise SDL2
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		throw std::runtime_error((std::string)"SDL_Init could not initialize! SDL_Init Error: \n" + SDL_GetError());
	}
	if (TTF_Init() < 0) {
		throw std::runtime_error((std::string)"TTF_Init could not initialize! TTF_Init Error: \n" + TTF_GetError());
	};

	//init SDL2 soud lib
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		throw std::runtime_error((std::string)"SDL_mixer could not initialize! SDL_mixer Error: \n" + Mix_GetError());
	}
}
int main(int argc, char** argv) {
	try {
		init_sdl_librarys();
	}
	catch (std::runtime_error error){
		std::cout << error.what();
		return 1;
	}
	Game_Backend gameBackend(1000,720);
	gameBackend.game_loop();
	return 0;
}