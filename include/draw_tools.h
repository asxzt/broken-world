#ifndef DRAW_TOOLS_H_INCLUDED
#define DRAW_TOOLS_H_INCLUDED

#include <string>

#include "SDLPP/sdl_renderer.h"
#include "SDLPP/sdl_texture.h"

#include "virtual_drawer.h"
#include "texture_library.h"

namespace Game
{
void DrawTextOnScreen(std::string text,PPoint pos,SDL_Color col=SDL_Color({0,0,0}),FontSize siz=FontSize::Size_24)
{
    sdl2::Texture texture;
    texture.texture=TextureLibrary::Instance().GetTextureFromText(text,col,siz);
    int fpstw,fpsth;
    texture.GetSize(&fpstw,&fpsth);
    SDL_Rect fpstrect{pos.x,pos.y,fpstw,fpsth};
    TextureLibrary::Instance().GetRenderer()->CopyFromEx(texture.texture,nullptr,&fpstrect);
}
}

#endif // DRAW_TOOLS_H_INCLUDED
