#include "Game_Backend.hpp"

Game_Backend::Game_Backend(int p_window_width, int p_window_height)
	:window_width(p_window_width)
	, window_height(p_window_height)
	, quit(false)
	, m_game_scoreboard("../Assets/Koulen.ttf", window_width, window_height)
{
	//Create SDL window
	if (SDL_CreateWindowAndRenderer(window_width, window_height, 0, &window, &renderer) < 0) std::cout << "Failed at SDL_CreateWindowAndRenderer())" << std::endl;
	SDL_SetWindowTitle(window, "Pong");

	//specify objects color
	color.r = 84;
	color.g = 206;
	color.b = 199;

	//initialise user paddle
	user_paddle = std::make_unique<Moving_Paddle>
		(32, ((window_height / 2) - (window_height / 4)), 12, window_height / 4, 10);

	//initialise enemy paddle
	enemy_paddle = std::make_unique<Moving_Paddle>
		(window_width - 12 - 32, ((window_height / 2) - (window_height / 4)), 12, window_height / 4, 5);;

	//initialise ball
	Default_Game_Ball_Builder builder(window_width, window_height);
	Moving_Ball_Director moving_ball_director(&builder);
	moving_ball_director.construct_ball();
	game_ball = moving_ball_director.get_ball();
	//init scores
	user_score = enemy_score = 0;

	needs_delay = 0;
}

void Game_Backend::game_loop()
{
	int lastTime = 0;

	restart_session();
	while (!quit) {
		lastFrame = SDL_GetTicks();
		if (lastFrame >= (lastTime + 1000)) {
			lastTime = lastFrame;
			fps = frameCount;
			frameCount = 0;
		}
		compute_ball_movement();
		compute_enemy_movement();
		compute_scoreboard_change();
		handle_input();
		render_scene();
		handle_delay();

	}
}

void Game_Backend::handle_input()
{
	SDL_Event e;
	const Uint8* keystates = SDL_GetKeyboardState(nullptr);
	while (SDL_PollEvent(&e))
		if (e.type == SDL_QUIT) quit = true;
	if (keystates[SDL_SCANCODE_ESCAPE]) quit = true;


	if ((keystates[SDL_SCANCODE_UP] || keystates[SDL_SCANCODE_W]) && user_paddle->m_rect_body.y > 1)
	{
		user_paddle->move_y(-1);
	}
	if ((keystates[SDL_SCANCODE_DOWN] || keystates[SDL_SCANCODE_S])
		&& user_paddle->m_rect_body.y + user_paddle->m_rect_body.h < window_height)
	{
		user_paddle->move_y(1);
	}
	if (keystates[SDL_SCANCODE_R]) {
		restart_session();
	}
}

void Game_Backend::render_scene()
{
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 255);
	SDL_RenderClear(renderer);

	frameCount++;
	timerFPS = SDL_GetTicks() - lastFrame;
	if (timerFPS < (1000 / 60)) {
		SDL_Delay((1000 / 60) - timerFPS);
	}
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
	SDL_RenderFillRect(renderer, &user_paddle->m_rect_body);
	SDL_RenderFillRect(renderer, &enemy_paddle->m_rect_body);
	SDL_RenderFillRect(renderer, &game_ball->m_rect_body);

	SDL_RenderCopy(renderer, m_game_scoreboard.m_message_texture.get(), nullptr, &m_game_scoreboard.m_message_rect);
	SDL_RenderPresent(renderer);
}
Game_Backend::~Game_Backend()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
void Game_Backend::restart_session()
{

	who_serves = rand() % 2;
	needs_delay = 1;
	user_score = 0;
	enemy_score = 0;
	prepeare_a_round();
}
void Game_Backend::handle_delay()
{
	if (needs_delay == 1) {
		SDL_Delay(400);
		needs_delay = 0;
	}
}
void Game_Backend::compute_ball_movement()
{
	if (SDL_HasIntersection(&game_ball->m_rect_body, &enemy_paddle->m_rect_body)) {
		double relativeIntersectY = (enemy_paddle->m_rect_body.y + (enemy_paddle->m_rect_body.h / 2)) - (game_ball->m_rect_body.y + (game_ball->m_rect_body.w / 2));
		double norm = relativeIntersectY / (enemy_paddle->m_rect_body.h / 2);
		double bounce = norm * (5 * PI / 12);
		game_ball->m_ball_x_velocity = -game_ball->m_speed * cos(bounce);
		game_ball->m_ball_y_velocity = game_ball->m_speed * -sin(bounce);
		if (!(rand() % 5)) {
			++game_ball->m_speed;
		}
		game_ball->play_sound(static_cast<int>(sound_enum::paddle_hit));
	}
	if (SDL_HasIntersection(&game_ball->m_rect_body, &user_paddle->m_rect_body)) {
		double relativeIntersectY = (user_paddle->m_rect_body.y + (user_paddle->m_rect_body.h / 2)) - ((game_ball->m_rect_body.y + (game_ball->m_rect_body.w / 2)));
		double norm = relativeIntersectY / (user_paddle->m_rect_body.h / 2);
		double bounce = norm * (5 * PI / 12);
		game_ball->m_ball_x_velocity = game_ball->m_speed * cos(bounce);
		game_ball->m_ball_y_velocity = game_ball->m_speed * -sin(bounce);
		if (!(rand() % 5)) {
			++game_ball->m_speed;
		}

		game_ball->play_sound(static_cast<int>(sound_enum::paddle_hit));
	}
	if (game_ball->m_rect_body.x + game_ball->m_rect_body.w > window_width)
	{
		game_ball->play_sound(static_cast<int>(sound_enum::player_goal));
		++user_score;
		who_serves = 1;
		if (user_score == 10) {
			restart_session();
		}
		else {
			prepeare_a_round();
		}
	}
	if (game_ball->m_rect_body.x < 0)
	{
		game_ball->play_sound(static_cast<int>(sound_enum::enemy_goal));
		++enemy_score;
		who_serves = 0;
		if (enemy_score == 10) {
			restart_session();
		}
		else {
			prepeare_a_round();
		}
	}
	if (game_ball->m_rect_body.y<0 || game_ball->m_rect_body.y + game_ball->m_rect_body.h>window_height)
	{
		game_ball->play_sound(static_cast<int>(sound_enum::other_hit));
		game_ball->m_ball_y_velocity = -game_ball->m_ball_y_velocity;
	}
	game_ball->m_rect_body.x += game_ball->m_ball_x_velocity;
	game_ball->m_rect_body.y += game_ball->m_ball_y_velocity;
}
void Game_Backend::compute_enemy_movement()
{
	if (game_ball->m_rect_body.y - game_ball->m_rect_body.h / 2 > enemy_paddle->m_rect_body.y + enemy_paddle->m_rect_body.h / 2
		&& enemy_paddle->m_rect_body.y + enemy_paddle->m_rect_body.h < window_height)
		enemy_paddle->move_y(1);
	if (game_ball->m_rect_body.y - game_ball->m_rect_body.h / 2 < enemy_paddle->m_rect_body.y + enemy_paddle->m_rect_body.h / 2
		&& enemy_paddle->m_rect_body.y > 1)
		enemy_paddle->move_y(-1);
}
void Game_Backend::prepeare_a_round()
{
	user_paddle->set_default_cords();
	enemy_paddle->set_default_cords();
	game_ball->set_default_cords();

	game_ball->set_default_speed();
	game_ball->m_ball_y_velocity = 0;
	if (who_serves == 0) {
		game_ball->m_ball_x_velocity = game_ball->m_speed;
	}
	if (who_serves == 1) {
		game_ball->m_ball_x_velocity = -game_ball->m_speed;
	}
}

void Game_Backend::compute_scoreboard_change() {

	std::string string_message = (std::to_string(user_score) + "   " + std::to_string(enemy_score));
	m_game_scoreboard.compute_scoreboard(window_width / 2, color,
		renderer, string_message);
}