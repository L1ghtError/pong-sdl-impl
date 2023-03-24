#pragma once
#include "Moving_Base.hpp"
#include <vector>
#include "Game_Utils.hpp"



class Moving_Ball : public Moving_Base {
	//varible that controls amont of sound repeats
	int _sound_throttle;

	//vecotr of avalible sounds
	std::vector<std::unique_ptr<Mix_Chunk, Game_Utils::Game_Deleters::SDL_Mix_Deleter>> ball_sounds;
public:
	float m_ball_x_direction, m_ball_y_direction;
	//function that plays conresponding sound
	void play_sound(int type);
	//constructor
	Moving_Ball(int body_x_cord, int body_y_cord, int body_width, int body_height, float body_speed);
	
	//adds an element to sound vector
	void append_sound(const char* sound_path);

	void handle_paddle_hit(SDL_Rect intersection_body);
	void move_in_calculated_direction(float delta_time);
	void set_ball_direction(float ball_x_direction, float ball_y_direction);
};
