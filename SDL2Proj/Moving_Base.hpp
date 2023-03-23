#pragma once
#include <SDL.h>
#include "string"

class Moving_Base {
protected:
	//variables that allow you to return to the standard position and speed
	int default_x, default_y;
	int default_speed;
public:
	//SDL body
	SDL_Rect m_rect_body;
	//body speed
	int m_speed;
	//
	void set_default_cords();
	void set_default_speed();
	//constructor
	Moving_Base(int body_x_cord, int body_y_cord, int body_width, int body_height, int body_speed);
};