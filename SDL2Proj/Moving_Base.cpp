#include "Moving_Base.hpp"

void Moving_Base::set_default_cords()
{
	rect_body.x = default_x;
	rect_body.y = default_y;
}

void Moving_Base::set_default_speed()
{
	speed = default_speed;
}

Moving_Base::Moving_Base(int p_x, int p_y, int p_w, int p_h, int p_speed)
	:speed(p_speed),default_x(p_x),default_y(p_y), default_speed(p_speed)
{
	rect_body.x = p_x;
	rect_body.y = p_y;
	rect_body.w = p_w;
	rect_body.h = p_h;
}