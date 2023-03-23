#include "Game_Scoreboard.hpp"


Game_Scoreboard::Game_Scoreboard(const char* p_font_filepath, int p_window_width, int p_window_height)
{
	font = std::unique_ptr<TTF_Font, Game_Utils::Game_Deleters::SDL_TTF_Deleter>(TTF_OpenFont(p_font_filepath, ((p_window_width + p_window_height) / 40)));
	if (font == nullptr) {
		SDL_Log("TTF_OpenFont %s", TTF_GetError());
	}

}

void Game_Scoreboard::compute_scoreboard(int window_width, SDL_Color p_color, SDL_Renderer* renderer,std::string score_message)
{
	const char* t = score_message.c_str();
	SDL_Surface* surfaceMessage =
		TTF_RenderText_Solid(font.get(), t, p_color);

	m_message_texture = std::unique_ptr<SDL_Texture, Game_Utils::Game_Deleters::SDL_Texture_Deleter>(SDL_CreateTextureFromSurface(renderer, surfaceMessage));

	m_message_rect.x = window_width - surfaceMessage->w / 2;  //controls the rect's x coordinate 
	m_message_rect.y = surfaceMessage->h / 2; // controls the rect's y coordinte
	m_message_rect.w = surfaceMessage->w; // controls the width of the rect
	m_message_rect.h = surfaceMessage->h; // controls the height of the rect
	SDL_RenderCopy(renderer, m_message_texture.get(), nullptr, &m_message_rect);
	SDL_FreeSurface(surfaceMessage);
}
