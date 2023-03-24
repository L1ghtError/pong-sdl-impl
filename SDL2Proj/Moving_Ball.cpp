#include "Moving_Ball.hpp"

void Moving_Ball::play_sound(int type)
{
	int temp_ticks = SDL_GetTicks();
	if (temp_ticks - _sound_throttle < 100) {

	}
	else
	{
		_sound_throttle = temp_ticks;
		if (Mix_PlayChannel(-1, ball_sounds[type].get(), 0) == -1) {
			SDL_Log("Cannot play sound %s", Mix_GetError());

		};
	}

}

Moving_Ball::Moving_Ball(int body_x_cord, int body_y_cord, int body_width, int body_height, float body_speed)
	:Moving_Base(body_x_cord, body_y_cord, body_width, body_height, body_speed),
	_sound_throttle(0),
	m_ball_x_direction(0.f),
	m_ball_y_direction(0.f)
{
}

void Moving_Ball::append_sound(const char* sound_path)
{
	ball_sounds.emplace_back((Mix_LoadWAV(sound_path)));
}

void Moving_Ball::handle_paddle_hit(SDL_Rect intersection_body)
{
	double relativeIntersectY = (intersection_body.y + (intersection_body.h / 2)) - (m_rect_body.y + (m_rect_body.w / 2));
	double norm = relativeIntersectY / (intersection_body.h / 2);
	double bounce = norm * (5 * Game_Utils::PI / 12);
	int x_direction = m_rect_body.x - intersection_body.x;
	m_ball_x_direction = (x_direction / SDL_abs(x_direction)) * cos(bounce);
	m_ball_y_direction = -sin(bounce);

	m_speed += default_speed * 0.01f;
}

void Moving_Ball::move_in_calculated_direction(float delta_time)
{
	Game_Utils::math::normalize(m_ball_x_direction, m_ball_y_direction);
	interpolated_body_x_cord += m_ball_x_direction * m_speed * delta_time;
	interpolated_body_y_cord += m_ball_y_direction * m_speed * delta_time;
}

void Moving_Ball::set_ball_direction(float ball_x_direction, float ball_y_direction)
{
	m_ball_x_direction = ball_x_direction;
	m_ball_y_direction = ball_y_direction;
}
