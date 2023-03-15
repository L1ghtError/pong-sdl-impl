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
	//handles user input
	void handle_input();
	//reset data after every goal 
	void prepeare_a_round();
	
	void compute_ball_movement();
	void compute_enemy_movement();
	void render_score_borad(int p_x_pos, int p_y_pos);
	//displays all rects
	void render_scene();
	//reset data after 10 rounds
	void restart_session();
	//delay before round
	void handle_delay();
public:
	GameBackend(int p_window_width = 0, int p_window_height = 0);
	void game_loop();

	~GameBackend();
};