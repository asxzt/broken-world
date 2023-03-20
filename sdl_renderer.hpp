#ifndef SDL_RENDERER_HPP_INCLUDED
#define SDL_RENDERER_HPP_INCLUDED

#include <SDL2/SDL_assert.h>
#include <SDL2/SDL_hints.h>
#include <SDL2/SDL_render.h>

namespace sdl2
{
struct Renderer
{
    Renderer(SDL_Window* Window,int index_of_driver=-1)
        :renderer(SDL_CreateRenderer(Window,index_of_driver,SDL_RENDERER_ACCELERATED))
    {}
    explicit Renderer (SDL_Surface* surface)
        :renderer(SDL_CreateSoftwareRenderer(surface))
    {}
    explicit Renderer(SDL_Renderer* renderer)
        :renderer(renderer)
    {}
    Renderer(Renderer const&) = delete;
    operator =(Renderer const&)=delete;
    ~Renderer()
    {
        if(renderer)
            SDL_DestroyRenderer(renderer);
    }
    explicit operator bool()const
    {
        return renderer!= nullptr;
    }
    bool DrawPoint(int x,int y)
    {
        SDL_assert(renderer!=nullptr);
        return 0==SDL_RenderDrawPoint(renderer,x,y);
    }
    bool DrawLine(int x1,int y1,int x2,int y2)
    {
        SDL_assert(renderer!=nullptr);
        return 0==SDL_RenderDrawLine(renderer,x1,y1,x2,y2);
    }
    bool Fill()
    {
        SDL_assert(renderer!=nullptr);
        return 0==SDL_RenderClear(renderer);
    }
    bool FillRect(SDL_Rect const& rect)
    {
        SDL_assert(renderer!= nullptr);
        return 0 ==SDL_RenderFillRect(renderer,&rect);
    }
    bool DrawRect(SDL_Rect const&rect)
    {
        SDL_assert(renderer!= nullptr);
        return 0 ==SDL_RenderDrawRect(renderer,&rect);
    }
    bool SetColor(Uint8 r,Uint8 g,Uint8 b)
    {
        SDL_assert(renderer!= nullptr);
        return 0 ==SDL_SetRenderDrawColor(renderer,r,g,b,SDL_ALPHA_OPAQUE);
    }
    bool GetColor(Uint8* r,Uint8* g,Uint8* b)
    {
        SDL_assert(renderer != nullptr);
        Uint8 a=0;
        return 0 ==SDL_GetRenderDrawColor(renderer,r,g,b,&a);
    }
    bool SetBlendMode(SDL_BlendMode const& mode)
    {
        SDL_assert(renderer!= nullptr);
        return 0==SDL_SetRenderDrawBlendMode(renderer,mode);
    }
    bool GetBlendMode(SDL_BlendMode* mode)const
    {
        SDL_assert(renderer != nullptr);
        return 0==SDL_GetRenderDrawBlendMode(renderer,mode);
    }
    bool SetlogicalSize(int w,int h)
    {
        SDL_assert(renderer != nullptr);
        return 0==SDL_RenderSetLogicalSize(renderer,w,h);
    }
    void GetLogicalSize(int * w,int* h)
    {
        SDL_assert(renderer != nullptr);
        SDL_RenderGetLogicalSize (renderer,w,h);
    }
    bool CopyFrom (SDL_Texture* src_texture
                ,const SDL_Rect * src_rect = nullptr
                ,const SDL_Rect * dst_rect = nullptr)
    {
        SDL_assert(renderer!= nul1ptr);
        SDL_assert(src_texture!= nullptr);
        return 0 ==SDL_RenderCopy (renderer,src_texture,src_rect,dst_rect);
    }
    bool CopyFromEx(SDL_Texture* src_texture
                ,const SDL_Rect* src_rect= nullptr
                ,const SDL_Rect* dst_rect =nullptr
                ,double angle =0
                ,SDL_Point* center = nullptr
                ,SDL_RendererFlip const flip=SDL_FLIP_NONE)
    {
        SDL_assert(renderer!= nullptr);
        SDL_assert(src_texture!= nullptr);
        return 0==SDL_RenderCopyEx(renderer,src_texture,src_rect,dst_rect ,angle,center,flip);
    }
    void Present()
    {
        SDL_assert(renderer!= nullptr);
        SDL_RenderPresent(renderer);
    }
    SDL_Renderer* renderer;
};
}

#endif // SDL_RENDERER_HPP_INCLUDED
