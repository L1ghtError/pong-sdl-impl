#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <memory>
#include "Moving_Pedal.hpp"
#include "Moving_Ball.hpp"

#define PI 3.14159265358979323846
class GameBackend {
	int window_width, window_height;
	bool quit;
	int user_score, enemy_score;
	SDL_Rect score_board;
	int font_size, ball_size;
	std::unique_ptr<Moving_Pedal> user_pedal, enemy_pedal;
	std::unique_ptr<Moving_Ball> game_ball;
	SDL_Renderer* renderer;
	SDL_Window* window;
	TTF_Font* font;
	SDL_Color color;
	int frameCount, timerFPS, lastFrame, fps;
	bool who_serves;
	int needs_delay;

	Mix_Music* gSound = NULL;
	Mix_Chunk* paddle_hit = NULL;
	Mix_Chunk* other_hit = NULL;
	Mix_Chunk* player_goal = NULL;
	Mix_Chunk* enemy_goal = NULL;
public:
	GameBackend(int p_window_width = 0, int p_window_height = 0);
	void game_loop();
	void handle_input();
	void prepeare_a_round();
	void compute_ball_movement();
	void compute_enemy_movement();
	void render_score_borad(int p_x_pos, int p_y_pos);
	void render_scene();
	void restart_session();
	void handle_delay();

	~GameBackend();
};