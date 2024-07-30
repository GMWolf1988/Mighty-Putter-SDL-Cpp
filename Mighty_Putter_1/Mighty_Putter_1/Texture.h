#pragma once
#include <string>
#include <SDL.h>
#include <SDL_image.h>


SDL_Texture*
// Function prototype for a function that loads a texture from a file and returns a pointer to the texture
load_texture(SDL_Renderer* pRenderer, std::string path);

// Function prototype for a function that returns the size of a texture as an SDL_Point
SDL_Point get_texture_size(SDL_Texture* pTexture);