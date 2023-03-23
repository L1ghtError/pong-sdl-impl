#pragma once
#include "Moving_Base.hpp"

class Moving_Paddle : public Moving_Base {
public:
	//Constructor
	Moving_Paddle(int body_x_cord, int body_y_cord, int body_width, int body_height, int body_speed);

	//Function that move paddle in corresponding direction by one pixel
	void move_y(int body_move_direction);
};
