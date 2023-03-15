#pragma once
#include "Moving_Base.hpp"
class Moving_Ball : public Moving_Base  {
	
public:
	Moving_Ball(int p_x, int p_y, int p_w, int p_h, int p_speed);
	int x_velocity, y_velocity;
};
