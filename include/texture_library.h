#ifndef TEXTURE_LIBRARY_H_INCLUDED
#define TEXTURE_LIBRARY_H_INCLUDED

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_assert.h>
#include <functional>
#include <memory>
#include <iostream>
#include <map>

#include "SDLPP/sdl_renderer.h"
#include "SDLPP/sdl_surface.h"
#include "SDLPP/sdl_texture.h"
#include "game_settings.h"

namespace Game
{
enum FontSize
{
    Size_12,
    Size_18,
    Size_24,
    Size_36,
    Size_48,
    Size_60,
    Size_72
};

enum FontType
{
    Default,
    STKAITI
};
/*SDL_Texture* LoadTexture(sdl2::Renderer rdr,char const* fname)
{
    return IMG_LoadTexture(rdr.renderer.fname);
}*/
class TextureLibrary
{
private:
    TextureLibrary()=default;
    TextureLibrary(TextureLibrary const&)=default;
public:
    static TextureLibrary& Instance()
    {
        static TextureLibrary instance;
        return instance;
    }

    bool Init(sdl2::Renderer* renderer);

    void Quit()
    {
        for(int i=0;i<7;i++)
            TTF_CloseFont(Font_STKAITI[i]);
    }

    sdl2::Renderer* GetRenderer()
    {
        return _renderer;
    }

    sdl2::Texture& GetTexture(std::string name)
    {
        return (s2t[name]);
    }
    SDL_Texture* GetTextureFromText(std::string text,SDL_Color col,FontSize fsize=FontSize::Size_18,FontType ftype=FontType::Default)
    {
        if(FontType::Default==ftype)
        {
            ftype=FontType::STKAITI;
        }
        TTF_Font** array_of_font;
        switch(ftype)
        {
            case FontType::Default:
                array_of_font=Font_STKAITI;
                break;
            case FontType::STKAITI:
                array_of_font=Font_STKAITI;
                break;
        }
        //std::cout<<text<<std::endl;
        SDL_Surface* sur=TTF_RenderUTF8_Solid(array_of_font[static_cast<int>(fsize)],text.c_str(),col);
        SDL_assert(sur!=nullptr);
        return SDL_CreateTextureFromSurface(_renderer->renderer,sur);

    }

public:
    SDL_Texture* LoadTexture(std::string fname,Uint8 a);

private:
    sdl2::Renderer *_renderer;
    std::map<std::string,sdl2::Texture> s2t;

    TTF_Font* Font_STKAITI[7];
};

}

#endif // TEXTURE_LIBRARY_H_INCLUDED
