#ifndef SDL_TEXTURE_H_INCLUDED
#define SDL_TEXTURE_H_INCLUDED

#include <SDL2/SDL_assert.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_render.h>
namespace sdl2
{
struct Texture
{
    Texture()
        :texture(nullptr)
    {}
    Texture(SDL_Renderer* renderer,SDL_Surface *surface)
        :texture(SDL_CreateTextureFromSurface(renderer,surface))
    {}
    Texture(Texture const&) =delete;
    Texture& operator=(Texture const&) =delete;
    /*Texture& operator=(SDL_Texture* other)
    {
        if(this->texture==nullptr)
            this->texture=other;
    }*/
    ~Texture()
    {
        if(texture)
        {
            SDL_DestroyTexture(texture);
        }
    }
    explicit operator bool()const
    {
        return texture!=nullptr;
    }
    bool GetSize(int *w,int *h)const
    {
        SDL_assert(texture!=nullptr);
        return 0==SDL_QueryTexture(texture,nullptr,nullptr,w,h);
    }
    SDL_Texture* texture;
};
}

#endif // SDL_TEXTURE_H_INCLUDED
