#include "Moving_Pedal.hpp"
Moving_Pedal::Moving_Pedal(int p_x, int p_y, int p_w, int p_h, int p_speed)
	:Moving_Base(p_x, p_y, p_w, p_h, p_speed)
{
}

void Moving_Pedal::move_y(int p_direction)
{

	rect_body.y += p_direction * speed;
}
