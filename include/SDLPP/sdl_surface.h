#ifndef SDL_SURFACE_HPP_INCLUDED
#define SDL_SURFACE_HPP_INCLUDED

namespace sdl2
{
struct Surface
{
    Surface(int w,int h,int depth,Uint32 r_mask,Uint32 g_mask,Uint32 b_mask,Uint32 a_mask)
        :surface(SDL_CreateRGBSurface(0,w,h,depth,r_mask,g_mask,b_mask,a_mask))
    {}
     Surface(int w,int h,int depth,Uint32 format)
        :surface(SDL_CreateRGBSurfaceWithFormat(0,w,h,depth,format))
    {}
    explicit Surface(SDL_Surface* surface)
        :surface(surface)
    {}
    Surface(Surface const&)=delete;
    Surface& operator = (Surface const&) =delete;
    ~Surface()
    {
        if(surface)
            SDL_FreeSurface(surface);
    }
    explicit operator bool()const
    {
        return surface!=nullptr;
    }
    bool EnableColorKey(Uint32 key)
    {
        SDL_assert(surface!=nullptr);
        return 0==SDL_SetColorKey(surface,SDL_TRUE,key);
    }
    bool EnableColorKey(Uint8 r,Uint8 g,Uint8 b,Uint8 a)
    {
        SDL_assert(surface!=nullptr);
        Uint32 key=SDL_MapRGBA(surface->format,r,g,b,a);
        return 0==SDL_SetColorKey(surface,SDL_TRUE,key);
    }
    bool SetAlphaMod(Uint8 a)
    {
        SDL_assert(surface!=nullptr);
        return 0==SDL_SetSurfaceAlphaMod(surface,a);
    }
    bool SetBlendMod(SDL_BlendMode const& mode)
    {
        SDL_assert(surface!=nullptr);
        return 0==SDL_SetSurfaceBlendMode(surface,mode);
    }
// TODO (WCM#1#): We need finish it!

    SDL_Surface* surface;
};
}

#endif // SDL_SURFACE_HPP_INCLUDED
