#pragma once
#include "Game_Utils.hpp"
#include "Moving_Ball.hpp"

class IMoving_Ball_Builder {
public:
	virtual void create_ball() = 0;
	virtual void create_ball_sound() = 0;
	virtual std::unique_ptr<Moving_Ball> get_ball() = 0;
};

class Default_Game_Ball_Builder :public IMoving_Ball_Builder {
	std::unique_ptr<Moving_Ball> game_ball;
	int window_width, window_height;
	int ball_size = 20;

public:

	Default_Game_Ball_Builder(int p_window_width, int p_window_height);
	void create_ball() override;
	void create_ball_sound() override;
	std::unique_ptr<Moving_Ball> get_ball()override;

};
class Moving_Ball_Director {
	IMoving_Ball_Builder* builder;
public:
	Moving_Ball_Director(IMoving_Ball_Builder* p_builder);
	void set_builder(IMoving_Ball_Builder* p_builder);
	void construct_ball();
	std::unique_ptr<Moving_Ball> get_ball();
};