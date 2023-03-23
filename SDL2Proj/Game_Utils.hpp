#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>

#include <memory>
namespace Game_Utils {
	namespace Game_Deleters {
		struct SDL_Mix_Deleter {
			void operator()(Mix_Chunk* chunk) const {
				Mix_FreeChunk(chunk);
			}
		};
		struct SDL_TTF_Deleter {
			void operator()(TTF_Font* _font) {
				TTF_CloseFont(_font);
			}
		};
		struct SDL_Texture_Deleter {
			void operator()(SDL_Texture* _texture) {
				SDL_DestroyTexture(_texture);
			}
		};
	}
}