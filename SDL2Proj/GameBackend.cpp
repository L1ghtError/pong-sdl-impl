#include "GameBackend.hpp"

GameBackend::GameBackend(int p_window_width, int p_window_height)
	:window_width(p_window_width), window_height(p_window_height), quit(false)
{
	//checks whether the window dimensions are specified, if not specifies automatically
	if (window_height == 0 || window_width == 0) {
		SDL_DisplayMode DM;
		SDL_VideoInit(NULL);
		if (SDL_GetDesktopDisplayMode(0, &DM) != 0)
		{
			SDL_Log("SDL_GetDesktopDisplayMode failed: %s", SDL_GetError());
		}
		window_height = window_height == 0 ? DM.h : window_height;
		window_width = window_width == 0 ? DM.w : window_width;
	}
	//initialise SDL2
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) std::cout << "Failed at SDL_Init()" << std::endl;
	//Create SDL window
	if (SDL_CreateWindowAndRenderer(window_width, window_height, 0, &window, &renderer) < 0) std::cout << "Failed at SDL_CreateWindowAndRenderer())" << std::endl;
	SDL_SetWindowTitle(window, "Pong");
	//init SDL2 soud lib
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
	}

	//Load sound effects
	paddle_hit = Mix_LoadWAV("../Assets/paddle_hit.wav");
	if (paddle_hit == NULL)
	{
		printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	}
	other_hit = Mix_LoadWAV("../Assets/paddle_hit_pitched.wav");
	if (other_hit == NULL)
	{
		printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	}
	player_goal = Mix_LoadWAV("../Assets/good.wav");
	if (other_hit == NULL)
	{
		printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	}
	enemy_goal = Mix_LoadWAV("../Assets/bad.wav");
	if (other_hit == NULL)
	{
		printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	}
	//initialise font lib
	TTF_Init();
	//selects the desired font
	font = TTF_OpenFont("../Assets/Peepo.ttf", ((window_height + window_width) / 40));
	if (font == NULL) {
		SDL_Log("TTF_OpenFont %s", TTF_GetError());
	}

	//specify objects color :)
	color.r = 84;
	color.g = 206;
	color.b = 199;

	//initialise user pedal
	user_pedal = std::make_unique<Moving_Pedal>
		(32, ((window_height / 2) - (window_height / 4)), 12, window_height / 4, 10);

	//initialise enemy pedal
	enemy_pedal = std::make_unique<Moving_Pedal>
		(window_width - 12 - 32, ((window_height / 2) - (window_height / 4)), 12, window_height / 4, 5);;

	//initialise ball
	ball_size = 20;
	game_ball = std::make_unique<Moving_Ball>
		((window_width / 2) + (ball_size / 2),
			(window_height / 2) + (ball_size / 2), ball_size, ball_size, window_width * 0.015);
	//init scores
	user_score = enemy_score = 0;

	needs_delay = 0;
}

void GameBackend::game_loop()
{
	SDL_Event e;
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
		handle_input();
		render_scene();
		handle_delay();
		//std::cout << "\ndelta:" << deltaTime << " " << NOW << " " << LAST;
		//std::cout << "\n" << user_pedal->rect_body.y << " " << user_pedal->rect_body.y + user_pedal->rect_body.h;

	}
}

void GameBackend::handle_input()
{
	SDL_Event e;
	const Uint8* keystates = SDL_GetKeyboardState(NULL);
	while (SDL_PollEvent(&e))
		if (e.type == SDL_QUIT) quit = true;
	if (keystates[SDL_SCANCODE_ESCAPE]) quit = true;


	if ((keystates[SDL_SCANCODE_UP] || keystates[SDL_SCANCODE_W]) && user_pedal->rect_body.y > 1)
	{
		user_pedal->move_y(-1);
	}
	if ((keystates[SDL_SCANCODE_DOWN] || keystates[SDL_SCANCODE_S])
		&& user_pedal->rect_body.y + user_pedal->rect_body.h < window_height)
	{
		user_pedal->move_y(1);
	}
	if (keystates[SDL_SCANCODE_R]){
	restart_session();
	}
}

void GameBackend::render_scene()
{
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 255);
	SDL_RenderClear(renderer);

	frameCount++;
	timerFPS = SDL_GetTicks() - lastFrame;
	if (timerFPS < (1000 / 60)) {
		SDL_Delay((1000 / 60) - timerFPS);
	}
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
	SDL_RenderFillRect(renderer, &user_pedal->rect_body);
	SDL_RenderFillRect(renderer, &enemy_pedal->rect_body);
	SDL_RenderFillRect(renderer, &game_ball->rect_body);
	render_score_borad(window_width / 2 + font_size, font_size * 2);
	SDL_RenderPresent(renderer);
}
GameBackend::~GameBackend()
{
	TTF_CloseFont(font);
	SDL_DestroyRenderer(renderer);
	Mix_FreeChunk(paddle_hit);
	Mix_FreeChunk(other_hit);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
void GameBackend::restart_session()
{

	who_serves = rand() % 2;
	needs_delay = 1;
	user_score = 0;
	enemy_score = 0;
	prepeare_a_round();
}
void GameBackend::handle_delay()
{
	if (needs_delay == 1) {
			SDL_Delay(400);
			needs_delay = 0;
	}
}
void GameBackend::compute_ball_movement()
{
	if (SDL_HasIntersection(&game_ball->rect_body, &enemy_pedal->rect_body)) {
		double relativeIntersectY = (enemy_pedal->rect_body.y + (enemy_pedal->rect_body.h / 2)) - (game_ball->rect_body.y + (ball_size / 2));
		double norm = relativeIntersectY / (enemy_pedal->rect_body.h / 2);
		double bounce = norm * (5 * PI / 12);
		game_ball->x_velocity = -game_ball->speed * cos(bounce);
		game_ball->y_velocity = game_ball->speed * -sin(bounce);
		if (!(rand() % 5)) {
			++game_ball->speed;
		}
		Mix_PlayChannel(-1, paddle_hit, 0);
	}
	if (SDL_HasIntersection(&game_ball->rect_body, &user_pedal->rect_body)) {
		double relativeIntersectY = (user_pedal->rect_body.y + (user_pedal->rect_body.h / 2)) - ((game_ball->rect_body.y + (ball_size / 2)));
		double norm = relativeIntersectY / (user_pedal->rect_body.h / 2);
		double bounce = norm * (5 * PI / 12);
		game_ball->x_velocity = game_ball->speed * cos(bounce);
		game_ball->y_velocity = game_ball->speed * -sin(bounce);
		if (!(rand() % 5)) {
			++game_ball->speed;
		}

		Mix_PlayChannel(-1, paddle_hit, 0);
	}
	if (game_ball->rect_body.x + game_ball->rect_body.w > window_width)
	{
		Mix_PlayChannel(-1, player_goal, 0);
		++user_score;
		who_serves = 0;
		if(user_score==10){
			restart_session();
		}else{
		prepeare_a_round();
		}
	}
	if (game_ball->rect_body.x < 0)
	{
		Mix_PlayChannel(-1, enemy_goal, 0);
		++enemy_score;
		who_serves = 1;
		if (enemy_score == 10) {
			restart_session();
		}
		else {
			prepeare_a_round();
		}
	}
	if (game_ball->rect_body.y<0 || game_ball->rect_body.y + game_ball->rect_body.h>window_height)
	{
		Mix_PlayChannel(-1, other_hit, 0);
		game_ball->y_velocity = -game_ball->y_velocity;
	}
	game_ball->rect_body.x += game_ball->x_velocity;
	game_ball->rect_body.y += game_ball->y_velocity;
}
void GameBackend::compute_enemy_movement()
{
	if (game_ball->rect_body.y - game_ball->rect_body.h / 2 > enemy_pedal->rect_body.y + enemy_pedal->rect_body.h / 2
		&& enemy_pedal->rect_body.y + enemy_pedal->rect_body.h < window_height)
		enemy_pedal->move_y(1);
	if (game_ball->rect_body.y - game_ball->rect_body.h / 2 < enemy_pedal->rect_body.y + enemy_pedal->rect_body.h / 2
		&& enemy_pedal->rect_body.y > 1)
		enemy_pedal->move_y(-1);
}
void GameBackend::render_score_borad(int p_x_pos, int p_y_pos)
{

	std::string s_t = (std::to_string(user_score) + "   " + std::to_string(enemy_score));
	const char* t = s_t.c_str();
	SDL_Surface* surfaceMessage =
		TTF_RenderText_Solid(font, t, color);

	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	SDL_Rect Message_rect; //create a rect
	Message_rect.x = p_x_pos - surfaceMessage->w / 2;  //controls the rect's x coordinate 
	Message_rect.y = 0; // controls the rect's y coordinte
	Message_rect.w = surfaceMessage->w; // controls the width of the rect
	Message_rect.h = surfaceMessage->h; // controls the height of the rect

	SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);
}
void GameBackend::prepeare_a_round()
{
	user_pedal->set_default_cords();
	enemy_pedal->set_default_cords();
	game_ball->set_default_cords();

	game_ball->set_default_speed();
	game_ball->y_velocity = 0;
	if (who_serves == 0) {
		game_ball->x_velocity = game_ball->speed;
	}
	if (who_serves == 1) {
		game_ball->x_velocity = -game_ball->speed;
	}
}
