#include "Moving_Base.hpp"

void Moving_Base::set_default_cords()
{
	m_rect_body.x = default_x;
	m_rect_body.y = default_y;
}

void Moving_Base::set_default_speed()
{
	m_speed = default_speed;
}

Moving_Base::Moving_Base(int body_x_cord, int body_y_cord, int body_width, int body_height, int body_speed)
	:m_speed(body_speed), default_x(body_x_cord), default_y(body_y_cord), default_speed(body_speed)
{
	m_rect_body.x = body_x_cord;
	m_rect_body.y = body_y_cord;
	m_rect_body.w = body_width;
	m_rect_body.h = body_height;
}