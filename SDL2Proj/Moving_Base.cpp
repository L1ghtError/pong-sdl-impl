#include "Moving_Base.hpp"

void Moving_Base::set_default_cords()
{
	interpolated_body_x_cord = static_cast<float>(default_x);
	interpolated_body_y_cord = static_cast<float>(default_y);
}

void Moving_Base::set_default_speed()
{
	m_speed = default_speed;
}

SDL_Rect& Moving_Base::get_rect_body()
{
	m_rect_body.x = static_cast<int>(roundf(interpolated_body_x_cord));
	m_rect_body.y = static_cast<int>(roundf(interpolated_body_y_cord));
	return m_rect_body;
}

Moving_Base::Moving_Base(int body_x_cord, int body_y_cord, int body_width, int body_height, float body_speed)
	:default_x(body_x_cord), default_y(body_y_cord),
	default_speed(body_speed),
	interpolated_body_x_cord(static_cast<float>(body_x_cord)), interpolated_body_y_cord(static_cast<float>(body_y_cord)),
	m_speed(body_speed)
{
	m_rect_body.x = body_x_cord;
	m_rect_body.y = body_y_cord;
	m_rect_body.w = body_width;
	m_rect_body.h = body_height;
}