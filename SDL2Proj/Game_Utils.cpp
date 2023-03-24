#include "Game_Utils.hpp"


void Game_Utils::math::normalize(float& p_first_operand, float& p_second_operand) {
	float pow_mult = powf(p_first_operand, 2) + powf(p_second_operand, 2);
	p_first_operand /= pow_mult;
	p_second_operand /= pow_mult;
}
