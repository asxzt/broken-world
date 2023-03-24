#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_video.h>
#include "GameMap.h"
#include "common/sdl_renderer.hpp"
#include "common/sdl_surface.hpp"
#include "common/sdl_window.hpp"
#include "common/game_settings.h"
using namespace std;
using namespace sdl2;
using namespace Game::Settings;
int main(int argc,char* argv[])
{
    if(SDL_Init(SDL_INIT_EVERYTHING)<0)
    {
        return -1;
    }
    Window wnd("破碎的世界",0,0,window_width,window_height,sdl2::WindowFlags().FullScreenDesktop());
    if(!wnd)
    {
        return -1;
    }
    while(!game_quiet)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event)!=0)
        {
            switch(event.type)
            {
            case SDL_QUIT:
                game_quiet=true;
                break;
            }
        }
    }
    SDL_Quit();
    return 0;
}
