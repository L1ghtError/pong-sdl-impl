#pragma once
#include "Moving_Base.hpp"
class Moving_Pedal : public Moving_Base {
public:
	//Constructor
	Moving_Pedal(int p_x, int p_y, int p_w, int p_h, int p_speed);

	//Function that move paddle in corresponding direction by one pixel
	void move_y(int p_direction);
};
