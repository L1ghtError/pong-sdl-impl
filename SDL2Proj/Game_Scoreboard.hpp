#pragma once
#include <string>
#include "Game_Utils.hpp"
class Game_Scoreboard {

	std::unique_ptr<TTF_Font, Game_Utils::Game_Deleters::SDL_TTF_Deleter> font;

public:

	SDL_Rect m_message_rect;
	std::unique_ptr<SDL_Texture, Game_Utils::Game_Deleters::SDL_Texture_Deleter> m_message_texture;
	Game_Scoreboard(const char* p_font_filepath, int p_window_width = 0, int p_window_height = 0);

	void 	compute_scoreboard(int window_width, SDL_Color p_color, SDL_Renderer* renderer, std::string score_message);
};