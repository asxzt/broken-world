#include <SDL2/SDL_image.h>
#include <SDL2/SDL_assert.h>
#include <SDL2/SDL_ttf.h>
#include <functional>
#include <memory>
#include <map>

#include "SDLPP/sdl_renderer.h"
#include "SDLPP/sdl_surface.h"
#include "SDLPP/sdl_texture.h"
#include "game_settings.h"
#include "texture_library.h"

namespace Game
{
/*SDL_Texture* LoadTexture(sdl2::Renderer rdr,char const* fname)
{
    return IMG_LoadTexture(rdr.renderer.fname);
}*/
bool TextureLibrary::Init(sdl2::Renderer* renderer)
{
    SDL_assert(renderer!=nullptr);
    _renderer=renderer;

    bool all_ok=1;
    for(auto i=Game::Settings::images.begin();i!=Game::Settings::images.end();i++)
    {
        SDL_Texture* tt=LoadTexture(i->second,0);
        if(tt!=nullptr)
        {
            s2t[i->first].texture=tt;
        }
        else
        {
            all_ok=0;
            break;
        }

    }
    if(!all_ok)
        return false;

    //ttf

    for(int i=0;i<7;i++)
    {
        this->Font_STKAITI[i]=TTF_OpenFont("./asserts/fonts/STKAITI.TTF",Settings::FontSizeTranslate[i]);
        if(Font_STKAITI[i]==NULL)
            all_ok=0;
    }
    return all_ok;
}
SDL_Texture* TextureLibrary::LoadTexture(std::string fname,Uint8 a)
{
    return IMG_LoadTexture(_renderer->renderer,fname.c_str());
}


}
