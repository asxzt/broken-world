#ifndef SDL_ERROR_H_INCLUDED
#define SDL_ERROR_H_INCLUDED

#include <SDL2/SDL.h>

namespace sdl2
{
    char const* last_error()
    {
        return SDL_GetError();
    }
}

#endif // SDL_ERROR_H_INCLUDED
