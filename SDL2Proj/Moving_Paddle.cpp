#include "Moving_Paddle.hpp"
Moving_Paddle::Moving_Paddle(int body_x_cord, int body_y_cord, int body_width, int body_height, float body_speed)
	:Moving_Base(body_x_cord, body_y_cord, body_width, body_height, body_speed)
{
}

void Moving_Paddle::move_y(float body_move_direction, float delta_time)
{

	interpolated_body_y_cord += body_move_direction * m_speed * delta_time;
	m_rect_body.y = static_cast<int>(roundf(interpolated_body_y_cord));
}
