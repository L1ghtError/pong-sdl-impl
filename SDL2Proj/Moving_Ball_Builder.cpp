#include "Moving_Ball_Builder.hpp"

Default_Game_Ball_Builder::Default_Game_Ball_Builder(int p_window_width, int p_window_height)
	:window_width(p_window_width), window_height(p_window_height) {}
void Default_Game_Ball_Builder::create_ball() {
	game_ball = std::make_unique<Moving_Ball>
		((window_width / 2) + (ball_size / 2),
			(window_height / 2) + (ball_size / 2), ball_size, ball_size, window_width * 0.7);
}
void Default_Game_Ball_Builder::create_ball_sound() {
	game_ball->append_sound("../Assets/paddle_hit.wav");
	game_ball->append_sound("../Assets/paddle_hit_pitched.wav");
	game_ball->append_sound("../Assets/good.wav");
	game_ball->append_sound("../Assets/bad.wav");
}
std::unique_ptr<Moving_Ball> Default_Game_Ball_Builder::get_ball() {
	return std::move(game_ball);
}
;

Moving_Ball_Director::Moving_Ball_Director(IMoving_Ball_Builder* p_builder) :builder(p_builder
) {}

void Moving_Ball_Director::set_builder(IMoving_Ball_Builder* p_builder) {
	builder = p_builder;
}

void Moving_Ball_Director::construct_ball() {
	builder->create_ball();
	builder->create_ball_sound();
}

std::unique_ptr<Moving_Ball> Moving_Ball_Director::get_ball() {
	return builder->get_ball();
}
