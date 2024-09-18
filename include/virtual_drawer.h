#ifndef VIRTUAL_DRAWER_H_INCLUDED
#define VIRTUAL_DRAWER_H_INCLUDED

#include <cmath>

#include "SDLPP/sdl_renderer.h"
#include "game_map.h"
#include "texture_library.h"

namespace Game
{
struct PPoint
{
    int x,y;
};
class Vdrawer
{
public:
    Vdrawer()
        :vcent({0,0}),cwts(10),xsize(810),ysize(540),chunkr(81),rd(nullptr)
    {}
    void SetGameCenter(GamePoint _vcent){
        vcent=_vcent;
    }
    GamePoint GetGameCenter(){
        return vcent;
    }
    void SetCWTS(double c){
        cwts=c;
    }
    double GetCWTS(){
        return cwts;
    }
    void SetSize(int x,int y){
        xsize=x;ysize=y;
    }
    void SetChunkR(int r){
        chunkr=r;
    }


    void SetRenderer(sdl2::Renderer* trd)
    {
        rd=trd;
    }

    void DrawPoint(GamePoint vp)
    {
        if(rd==nullptr)return;
        PPoint tp=TranslateGamePoint(vp);
        //std::cout<<tp.x<<" "<<tp.y<<std::endl;
        rd->DrawPoint(tp.x,tp.y);
    }
    void DrawLine(GamePoint st,GamePoint ed)
    {
        if(rd==nullptr)return;
        PPoint tst=TranslateGamePoint(st),ted=TranslateGamePoint(ed);
        rd->DrawLine(tst.x,tst.y,ted.x,ted.y);
    }
    void DrawRect(GamePoint _lu,GamePoint _rd)
    {
        if(rd==nullptr)return;
        PPoint nlu=TranslateGamePoint(_lu);
        SDL_Rect rect({nlu.x,nlu.y,int(TranslateLength(_rd.x-_lu.x)),int(TranslateLength(_rd.y-_lu.y))});
        rd->DrawRect(rect);
    }
    void FillRect(GamePoint _lu,GamePoint _rd)
    {
        if(rd==nullptr)return;
        PPoint nlu=TranslateGamePoint(_lu);
        SDL_Rect rect({nlu.x,nlu.y,int(TranslateLength(_rd.x-_lu.x)),int(TranslateLength(_rd.y-_lu.y))});
        rd->FillRect(rect);
    }
    void FillHexagon(GamePoint _c,int r)
    {
        if(rd==nullptr)return;
        int xt=sqrt(r*r-0.5*r*0.5*r);
        GamePoint _lu({int(_c.x-0.5*r),_c.y-xt}),_rd({int(_c.x+0.5*r),_c.y+xt});
        this->FillRect(_lu,_rd);
        int sxt=xt*2,sxt2=xt*2;
        for(int i=r/2;i>=0;i--)
        {
            _lu.x--;_lu.y++;
            sxt-=2;
            this->DrawLine(_lu,GamePoint({_lu.x,_lu.y+sxt}));
        }
        for(int i=r/2;i>=0;i--)
        {
            _rd.x++;_rd.y--;
            sxt2-=1;
            this->DrawLine(_rd,GamePoint({_rd.x,_rd.y-sxt}));
        }
    }
    void CopyFromSimple(std::string name,GamePoint lus)
    {
        PPoint tp=TranslateGamePoint(lus);
        int wxs,wys;
        if(!TextureLibrary::Instance().GetTexture(name).GetSize(&wxs,&wys))return;
        int twxs=TranslateLength(wxs),twys=TranslateLength(wys);
        SDL_Rect rect({tp.x,tp.y,twxs,twys});
        rd->CopyFromEx(TextureLibrary::Instance().GetTexture(name).texture,nullptr,&rect);
    }
    void CopyFromPlus(std::string name,GamePoint lus,GamePoint rds)
    {
        PPoint tp=TranslateGamePoint(lus);
        PPoint tu=TranslateGamePoint(rds);
        //int wxs,wys;
        //if(!TextureLibrary::Instance().GetTexture(name).GetSize(&wxs,&wys))return;
        //int twxs=TranslateLength(wxs),twys=TranslateLength(wys);
        SDL_Rect rect({tp.x,tp.y,tu.x,tu.y});
        rd->CopyFromEx(TextureLibrary::Instance().GetTexture(name).texture,nullptr,&rect);
    }
    PPoint TranslateGamePoint(GamePoint tp)
    {
        GamePoint leftupp({int(vcent.x-CalcVX()/2),int(vcent.y-CalcVY()/2)});
        int dtx=tp.x-leftupp.x,dty=tp.y-leftupp.y;
        int trux=dtx*(xsize*1.0/CalcVX()),truy=dty*(ysize*1.0/CalcVY());

        return PPoint({trux,truy});
    }
    GamePoint TranslatePPoint(PPoint tp)
    {
        GamePoint leftupp({int(vcent.x-CalcVX()/2),int(vcent.y-CalcVY()/2)});
        int dtx=tp.x,dty=tp.y;
        int trux=leftupp.x+dtx*(CalcVX()*1.0/xsize),truy=leftupp.y+dty*(CalcVY()*1.0/ysize);

        return GamePoint({trux,truy});
    }
    double TranslateLength(double gamelen)
    {
        double ans=xsize*1.0/CalcVX()*gamelen;
        return ans;
    }
    double TranslateLengthToGame(double reallen)
    {
        double ans=CalcVX()*1.0/xsize*reallen;
        return ans;
    }
private:
    double CalcVX()
    {
        //std::cout<<chunkr*cwts<<std::endl;
        return chunkr*cwts;
    }
    double CalcVY()
    {
        double t=CalcVX()*1.0;
        return t/xsize*ysize;
    }
private:
    GamePoint vcent;
    double cwts;//chunk wants to show(heng)
    int xsize,ysize;
    int chunkr;

    sdl2::Renderer* rd;
};
}

#endif // VIRTUAL_DRAWER_H_INCLUDED
