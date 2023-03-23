#include "Moving_Ball.hpp"

void Moving_Ball::_init_sound()
{
	for (int i = 0; i < ball_sounds.size(); i++) {
		if (ball_sounds[i] == nullptr)
		{
			printf("\nFailed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		}
	}
}

void Moving_Ball::play_sound(int type)
{
	int temp_ticks = SDL_GetTicks();
	if (temp_ticks - _sound_throttle < 100) {

	}
	else
	{
		_sound_throttle = temp_ticks;
		if (Mix_PlayChannel(-1, ball_sounds[type].get(), 0) == -1) {
			SDL_Log("Cannot play sound %s", Mix_GetError());

		};
	}

}

Moving_Ball::Moving_Ball(int body_x_cord, int body_y_cord, int body_width, int body_height, int body_speed)
	:Moving_Base(body_x_cord, body_y_cord, body_width, body_height, body_speed), _sound_throttle(0)
{
	_init_sound();
}

void Moving_Ball::append_sound(const char* sound_path)
{
	ball_sounds.emplace_back((Mix_LoadWAV(sound_path)));
}
