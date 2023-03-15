#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "string"
#include <iostream>

class Moving_Base {
protected:
	int default_x, default_y;
	int default_speed;
public:
	SDL_Rect rect_body;
	int speed;
	void set_default_cords();
	void set_default_speed();
	Moving_Base(int p_x, int p_y, int p_w, int p_h, int p_speed);
};