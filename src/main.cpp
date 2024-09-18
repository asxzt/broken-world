#include <iostream>

#include <string>
#include <cstdio>
#include <thread>
#include <chrono>


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_ttf.h>

#include "SDLPP/sdl_error.h"
#include "SDLPP/sdl_window.h"
#include "SDLPP/sdl_renderer.h"

#include "texture_library.h"
#include "game_settings.h"
#include "virtual_drawer.h"

#include "war.h"
using namespace std;
using namespace Game;
void ErrorReport()
{
    string error_msg("Failed to Init .\n");
    error_msg+=string(sdl2::last_error());
    cerr<<error_msg<<endl;
    
}
bool InitAll()
{
    int init_states=SDL_Init(SDL_INIT_EVERYTHING
    & ~SDL_INIT_AUDIO);
    if(init_states<0)
    {
        ErrorReport();
        return false;
    }
    int init_img_states=IMG_Init(IMG_INIT_PNG);
    if(init_img_states!=(IMG_INIT_PNG))
    {
        ErrorReport();
        return false;
    }
    int init_ttf_states=TTF_Init();
    if(init_ttf_states!=0)
    {
        ErrorReport();
        return false;
    }
    return true;
}
int test()
{
    SDL_Window* window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    // 创建渲染器，便于后续渲染
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Could not create renderer: %s\n", SDL_GetError());
        return 1;
    }

    // 设置窗口背景颜色（这里为黑色）
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    // 事件循环，确保窗口保持打开
    SDL_Event event;
    int running = 1;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }
        // 渲染更新
        SDL_RenderPresent(renderer);
    }

} 
int main(int argc,char* argv[])
{
    if(!InitAll())
        return 1;
    cout<<"Init done."<<endl;
    cout<<test()<<endl;
    sdl2::Window win("Weird Land",
                     SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
                     Settings::screen_x,Settings::screen_y,sdl2::WindowFlags());
    
    if(!win)
    {
        ErrorReport();
        return -1;
    }
    win.SetWindowInputFocus();
    cout<<"Window done."<<endl;
    sdl2::Renderer rdr(win.window);
    if(!rdr)
    {
        ErrorReport();
        return -1;
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"linear");
    rdr.SetlogicalSize(Settings::screen_x,Settings::screen_y);

    Game::TextureLibrary& tlib=Game::TextureLibrary::Instance();
    if(!tlib.Init(&rdr))
    {
        ErrorReport();
        return 0;
    }

    war_scene();

    TextureLibrary::Instance().Quit();
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    return 0;
}
