#include "texture.h"

// Loads a texture from file and returns a pointer to it
SDL_Texture* load_texture(SDL_Renderer* pRenderer, std::string path)
{
    SDL_Texture* texture = NULL;
    SDL_Surface* surface = IMG_Load(path.c_str());

    if (surface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        texture = SDL_CreateTextureFromSurface(pRenderer, surface);
        if (texture == NULL)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }

        SDL_FreeSurface(surface);
    }

    return texture;
}

// Gets the dimensions of a texture
SDL_Point get_texture_size(SDL_Texture* pTexture)
{
    SDL_Point size;
    SDL_QueryTexture(pTexture, NULL, NULL, &size.x, &size.y);
    return size;
}