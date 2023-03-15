#pragma once
#include "Moving_Base.hpp"
#include <vector>
#include <memory>
#include <SDL_mixer.h>
class Moving_Ball : public Moving_Base {
	//Custom deleater for chunks
	struct SDL_Mix_Deleter {
		void operator()(Mix_Chunk* chunk) {
			Mix_FreeChunk(chunk);
		}
	};
	//varible that controls amont of sound repeats
	int _sound_throttle;

	//vecotr of avalible sounds
	std::vector<std::unique_ptr<Mix_Chunk, SDL_Mix_Deleter>> ball_sounds;
	//function that intialise all sounds
	void _init_sound();
public:
	//alias for ball_sound elements
	static enum class sound_enum
	{
		paddle_hit, other_hit, player_goal, enemy_goal
	};
	//function that plays conresponding sound
	void play_sound(sound_enum type);
	//constructor
	Moving_Ball(int p_x, int p_y, int p_w, int p_h, int p_speed);
	int x_velocity, y_velocity;
};
