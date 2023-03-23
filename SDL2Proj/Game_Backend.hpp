#pragma once
#include <iostream>

#include "Moving_Ball.hpp"
#include "Moving_Paddle.hpp"
#include "Game_Scoreboard.hpp"

#include "Game_Utils.hpp"
#include "Moving_Ball_Builder.hpp";

namespace {
	constexpr double PI = 3.14159265358979323846;
}
class Game_Backend {

	int window_width, window_height;
	bool quit;
	Game_Scoreboard m_game_scoreboard;
	int user_score, enemy_score;
	
	int ball_size;
	std::unique_ptr<Moving_Paddle> user_paddle, enemy_paddle;
	std::unique_ptr<Moving_Ball> game_ball;
	SDL_Renderer* renderer;
	SDL_Window* window;
	SDL_Color color;
	int frameCount, timerFPS, lastFrame, fps;
	bool who_serves;
	bool needs_delay;
	//handles user input
	void handle_input();
	//reset data after every goal 
	void prepeare_a_round();
	void compute_scoreboard_change();
	void compute_ball_movement();
	void compute_enemy_movement();
	//displays all rects
	void render_scene();
	//reset data after 10 rounds
	void restart_session();
	//delay before round
	void handle_delay();

	
	//alias for ball_sound elements
	enum class sound_enum
	{
		paddle_hit, other_hit, player_goal, enemy_goal
	};
public:
	Game_Backend(int p_window_width, int p_window_height);
	void game_loop();

	~Game_Backend();
};