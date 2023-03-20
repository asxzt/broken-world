#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_video.h>
#include "GameMap.h"
#include "sdl_renderer.hpp"
#include "sdl_surface.hpp"
#include "sdl_window.hpp"
using namespace std;

int main(int argc,char* argv[])
{
    if(SDL_Init(SDL_INIT_EVERYTHING)<0)
    {
        return -1;
    }
    SDL_Window* wnd=SDL_CreateWindow("破碎的世界",100,100,1280,960,0);
    if(!wnd)
    {
        return -1;
    }
    bool Q=false;
    while(!Q)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event)!=0)
        {
            switch(event.type)
            {
            case SDL_QUIT:
                Q=true;
                break;
            }
        }
    }
    SDL_Quit();
    return 0;
}
