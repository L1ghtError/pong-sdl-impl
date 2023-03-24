#pragma once
#include <SDL.h>
#include "string"

class Moving_Base {
protected:
	//variables that allow you to return to the standard position and speed
	int default_x, default_y;
	float default_speed;
	float interpolated_body_x_cord, interpolated_body_y_cord;
	
	SDL_Rect m_rect_body;
public:
	
	
	//body speed
	float m_speed;
	//
	void set_default_cords();
	void set_default_speed();
	//returns rect body depending on the interpolated values
	SDL_Rect& get_rect_body();
	//constructor
	Moving_Base(int body_x_cord, int body_y_cord, int body_width, int body_height, float body_speed);
};