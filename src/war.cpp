#include <iostream>
#include <functional>

#include "war.h"

#include "SDLPP/sdl_renderer.h"
#include "SDLPP/sdl_timer.h"

#include "texture_library.h"
#include "game_settings.h"
#include "time_center.h"
#include "virtual_drawer.h"
#include "game_map.h"
#include "draw_tools.h"

using namespace std;
using namespace Game;

namespace Game
{
struct war_data
{
    int xc=0,yc=0;
    double cw=5.0;

    int mosvx=0,mosvy=0;
    int mosx=0,mosy=0;
    bool is_touching=false;

    ChunkPoint mselected{0,0};
    GameMap gmap{-100,-100,100,100};

    Vdrawer vdr;

    int steady_timer_code=1;
    sdl2::Timer steady_timer;

    int now_fps=0;
    int fps_couter=0;
};
war_data ward;
void DrawWarMap()
{
    sdl2::Renderer* rdr=TextureLibrary::Instance().GetRenderer();
    rdr->SetColor(0,0,0);
    rdr->FillRect(SDL_Rect({0,0,Settings::screen_x,Settings::screen_y}));
    rdr->SetColor(int(ward.cw*15)%256,int(ward.cw*20)%256,int(ward.cw*10)%256);
    static const string he1="hexagon";
    static const string he2="hexagon_hlt";
    GamePoint luvp=ward.vdr.TranslatePPoint(PPoint({0,0})),rdvp=ward.vdr.TranslatePPoint(PPoint({Settings::screen_x,Settings::screen_y}));

    ChunkPoint lucp{luvp.x*4/3/(Settings::chunk_r*2),luvp.y/(Settings::chunk_r*2)};
    ChunkPoint rdcp{rdvp.x*4/3/(Settings::chunk_r*2),rdvp.y/(Settings::chunk_r*2)};
    //cout<<lucp.x<<" "<<lucp.y<<" "<<rdcp.x<<" "<<rdcp.y<<endl;
    for(int x=lucp.x-5;x<rdcp.x+5;x++)
    {
        for(int y=lucp.y-5;y<rdcp.y+5;y++)
        {
            GamePoint ccent=ward.gmap.CalcChunkCenter(ChunkPoint({x,y}));
            ward.vdr.DrawRect(GamePoint({ccent.x-10,ccent.y-10}),GamePoint({ccent.x+10,ccent.y+10}));
            GamePoint Postocopy({Settings::chunk_r*2*3/4*x-Settings::chunk_r*2/2,
                Settings::chunk_r*2*y+(abs(x)%2==1?Settings::chunk_r*2/2:0)-Settings::chunk_r*2/2});
            if(ward.mselected.x==x&&ward.mselected.y==y)
                ward.vdr.CopyFromSimple(he2,Postocopy);
            else
                ward.vdr.CopyFromSimple(he1,Postocopy);
        }
    }
}
void DrawWarUI()
{
    TextureLibrary& tlib=TextureLibrary::Instance();
    sdl2::Renderer* rdr=tlib.GetRenderer();
    //
    SDL_Rect ui1rect{Settings::screen_x*3/4,0,Settings::screen_x*1/4,Settings::screen_y*4/5};
    rdr->CopyFromEx(tlib.GetTexture("ui_menu1").texture,nullptr,&ui1rect);

    SDL_Rect ui2rect{0,Settings::screen_y*4/5,Settings::screen_x,Settings::screen_y*1/5};
    rdr->CopyFromEx(tlib.GetTexture("ui_menu2").texture,nullptr,&ui2rect);
    //
    DrawTextOnScreen(string("FPS:"+to_string(ward.now_fps)),PPoint({0,0}),SDL_Color({0x5d,0xac,0xff}),FontSize::Size_24);
    DrawTextOnScreen(string("CWTS:"+to_string(ward.cw)),PPoint({0,20}),SDL_Color({0x5d,0xac,0xff}),FontSize::Size_24);
    DrawTextOnScreen(string("GAME_POS:("+to_string(ward.xc)+","+to_string(ward.yc)+")"),PPoint({0,40}),SDL_Color({0x5d,0xac,0xff}),FontSize::Size_24);
    DrawTextOnScreen(string("SELECTED_CHUNK:("+to_string(ward.mselected.x)+","+to_string(ward.mselected.y)+")"),PPoint({0,60}),SDL_Color({0x5d,0xac,0xdf}),FontSize::Size_24);
}
void CalcFPS(int interval)
{
    static int waited_time=0;
    waited_time+=interval;
    if(waited_time<1000)return;
    ward.now_fps=ward.fps_couter;
    ward.fps_couter=0;
    waited_time=0;
}
void war_scene()
{

    TextureLibrary& tlib=TextureLibrary::Instance();
    sdl2::Renderer* rdr=tlib.GetRenderer();

    ward.vdr.SetChunkR(64);
    ward.vdr.SetRenderer(tlib.GetRenderer());
    ward.vdr.SetGameCenter(GamePoint({0,0}));
    ward.vdr.SetSize(Settings::screen_x,Settings::screen_y);


    int steady_timer_interval=Settings::wait_of_notice;
    ward.steady_timer.Start(steady_timer_interval,ward.steady_timer_code);

    TimeCenter::Instance().RegisterCallback(std::function<void(int)>(CalcFPS));
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
                case SDL_MOUSEWHEEL:
                    {
                        double ty=event.wheel.y*(event.wheel.direction==SDL_MOUSEWHEEL_NORMAL?1:-1);
                        ward.cw+=ty*-0.4;
                        if(ward.cw<0.2)ward.cw=0.2;
                        else if(ward.cw>30)ward.cw=30;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if(ward.is_touching==false)
                    {
                        ward.is_touching=true;
                        ward.mosx=event.button.x;
                        ward.mosy=event.button.y;
                        ward.mosvx=ward.xc;
                        ward.mosvy=ward.yc;
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    if(ward.is_touching==true)
                    {
                        if(abs(event.button.x-ward.mosx)<Settings::enabled_click_fix&&
                           abs(event.button.y-ward.mosy)<Settings::enabled_click_fix)//是点击
                        {

                        }
                        ward.is_touching=false;
                    }
                    break;
                case SDL_MOUSEMOTION:
                    {
                            PPoint tppoint=PPoint({event.button.x,event.button.y});
                            GamePoint tgpoint=ward.vdr.TranslatePPoint(tppoint);
                            //cout<<"PPOINT:("<<tppoint.x<<","<<tppoint.y<<") GAMEPOINT:("<<tgpoint.x<<","<<tgpoint.y<<")"<<endl;
                            //ward.gmap.FromChunkPoint(ward.gmap.FromGamePoint(tgpoint)).ok=false;
                            ward.mselected=ward.gmap.FromGamePoint(tgpoint);
                    }
                    if(ward.is_touching==true)
                    {

                        int detax=ward.mosx-event.motion.x,detay=ward.mosy-event.motion.y;
                        int vdx=ward.vdr.TranslateLengthToGame(detax),vdy=ward.vdr.TranslateLengthToGame(detay);
                        ward.xc=ward.mosvx+vdx;ward.yc=ward.mosvy+vdy;
                    }
                    break;
                case SDL_USEREVENT:
                {
                    //cout<<6<<endl;
                    if(event.user.code==ward.steady_timer_code)
                    {
                        TimeCenter::Instance().OnTimer(Settings::wait_of_notice);
                    }
                }
            }
        }
        //cout<<"T_FPS:"<<ward.now_fps<<endl;
        DrawWarMap();
        DrawWarUI();
        ward.vdr.SetGameCenter(GamePoint({ward.xc,ward.yc}));
        ward.vdr.SetCWTS(ward.cw);
        rdr->Present();
        ward.fps_couter++;
    }
}
}
