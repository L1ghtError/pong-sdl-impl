#include "Moving_Paddle.hpp"
Moving_Paddle::Moving_Paddle(int body_x_cord, int body_y_cord, int body_width, int body_height, int body_speed)
	:Moving_Base(body_x_cord, body_y_cord, body_width, body_height, body_speed)
{
}

void Moving_Paddle::move_y(int body_move_direction)
{

	m_rect_body.y += body_move_direction * m_speed;
}
