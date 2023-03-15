#pragma once
#include "Moving_Ball.hpp"

void Moving_Ball::_init_sound()
{
	ball_sounds.emplace_back((Mix_LoadWAV("../Assets/paddle_hit.wav")));
	ball_sounds.emplace_back((Mix_LoadWAV("../Assets/paddle_hit_pitched.wav")));
	ball_sounds.emplace_back((Mix_LoadWAV("../Assets/good.wav")));
	ball_sounds.emplace_back((Mix_LoadWAV("../Assets/bad.wav")));

	for (int i = 0; i < ball_sounds.size(); i++) {
		if (ball_sounds[i] == NULL)
		{
			printf("\nFailed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		}
	}
}

void Moving_Ball::play_sound(sound_enum type)
{
	int temp_ticks = SDL_GetTicks();
	if (temp_ticks - _sound_throttle < 100) {
		
	}
	else
	{
		_sound_throttle = temp_ticks;
		if (Mix_PlayChannel(-1, ball_sounds[static_cast<int>(type)].get(), 0) == -1) {
			SDL_Log("Cannot play sound %s", Mix_GetError());

		};
	}

}

Moving_Ball::Moving_Ball(int p_x, int p_y, int p_w, int p_h, int p_speed)
	:Moving_Base(p_x, p_y, p_w, p_h, p_speed), _sound_throttle(0)
{
	_init_sound();
}
