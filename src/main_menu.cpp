#include <iostream>
#include <functional>

#include "main_menu.h"

#include "SDLPP/sdl_renderer.h"
#include "SDLPP/sdl_timer.h"

#include "texture_library.h"
#include "game_settings.h"
#include "time_center.h"
#include "virtual_drawer.h"
#include "game_map.h"

using namespace std;
using namespace Game;

namespace Game
{
struct main_menu_data
{

};
main_menu_data menud;
void DrawMenuUI()
{
    TextureLibrary& tlib=TextureLibrary::Instance();
    sdl2::Renderer* rdr=tlib.GetRenderer();
}
bool menu_scene()
{

    TextureLibrary& tlib=TextureLibrary::Instance();
    sdl2::Renderer* rdr=tlib.GetRenderer();

    bool quit=false;
    while(!quit)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    quit=true;
                    break;
            }
        }
        DrawMenuUI();
        rdr->Present();
    }
    return true;
}
}
