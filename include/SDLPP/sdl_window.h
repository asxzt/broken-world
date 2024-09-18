#ifndef SDL_WINDOW_HPP_INCLUDED
#define SDL_WINDOW_HPP_INCLUDED

#include <SDL2/SDL_assert.h>
#include <SDL2/SDL_video.h>

namespace sdl2
{
struct WindowPosition
{
    WindowPosition()
        :x(SDL_WINDOWPOS_UNDEFINED),y(SDL_WINDOWPOS_UNDEFINED)
    {}
    WindowPosition(int x,int y)
        :x(x),y(y)
    {}
    WindowPosition& Centered(bool x_centered=true,bool y_centered=true)
    {
        if(x_centered)
            x=SDL_WINDOWPOS_CENTERED;
        if(y_centered)
            y=SDL_WINDOWPOS_CENTERED;
        return *this;
    }
    int x,y;
};
struct WindowFlags
{
    WindowFlags()
        :flags(0)
    {}
    WindowFlags(Uint32 flags)
        :flags(flags)
    {}
    WindowFlags& Hidden()
    {
        flags|=SDL_WINDOW_HIDDEN;
        return *this;
    }
    WindowFlags& FullScreen()//全屏，改分辨率
    {
        flags&=~SDL_WINDOW_FULLSCREEN_DESKTOP;
        flags|=SDL_WINDOW_FULLSCREEN;
        return *this;
    }
    WindowFlags& FullScreenDesktop()//全屏，不改分辨率
    {
        flags&=~SDL_WINDOW_FULLSCREEN;
        flags|=SDL_WINDOW_FULLSCREEN_DESKTOP;
        return *this;
    }
    WindowFlags& Minimized()
    {
        flags&=~SDL_WINDOW_MAXIMIZED;
        flags|=SDL_WINDOW_MINIMIZED;
        return *this;
    }
    WindowFlags& Maximized()
    {
        flags&=~SDL_WINDOW_MINIMIZED;
        flags|=SDL_WINDOW_MAXIMIZED;
        return *this;
    }
    WindowFlags& Borderless()
    {
        flags|=SDL_WINDOW_BORDERLESS;
        return *this;
    }
    WindowFlags& Resizeable()
    {
        flags|=SDL_WINDOW_RESIZABLE;
        return *this;
    }
    WindowFlags& AllowHDPI()
    {
        flags|=SDL_WINDOW_FULLSCREEN;
        return *this;
    }
    WindowFlags& CanUseForOpenGL()
    {
        flags|=SDL_WINDOW_OPENGL;
        return *this;
    }
    Uint32 flags;
};
struct Window
{
    Window(char const* title,int x,int y,int w,int h,WindowFlags const& win_flags)
    {
        window=SDL_CreateWindow(title,x,y,w,h,win_flags.flags);
    }
    Window(char const* title,WindowPosition const& pos,int w,int h,WindowFlags const& win_flags)
    {
        window=SDL_CreateWindow(title,pos.x,pos.y,w,h,win_flags.flags);
    }
    explicit Window(SDL_Window* window)
        :window(window)
    {}
    Window(Window const&)=delete;
    Window& operator = (Window const&) =delete;
    ~Window()
    {
        if(window)
            SDL_DestroyWindow(window);
    }
    explicit operator bool()const
    {
        return window!=nullptr;
    }
    Uint32 GetID()const
    {
        SDL_assert(window!=nullptr);
        return SDL_GetWindowID(window);
    }
    static SDL_Window* FromID(Uint32 id)
    {

        return SDL_GetWindowFromID(id);
    }
    void SetTitle(char const* title)
    {
        SDL_assert(window!=nullptr);
        SDL_SetWindowTitle(window,title);
    }
    void SetWindowInputFocus()
    {
        SDL_assert(window!=nullptr);
        SDL_SetWindowInputFocus(window);
    }
// TODO (WCM#1#): To finish sdl_window.hpp
    //need more
    SDL_Window* window;
};
}

#endif // SDL_WINDOW_HPP_INCLUDED

