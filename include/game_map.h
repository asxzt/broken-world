#ifndef GAME_MAP_H_INCLUDED
#define GAME_MAP_H_INCLUDED

#include<map>
#include<iostream>
#include<cmath>
#include "game_settings.h"

namespace Game
{
struct GamePoint
{
    int x,y;
};
struct ChunkPoint
{
    bool operator<(ChunkPoint const& other)const
    {
        if(this->x!=other.x)
                return this->x<other.x;
        else
            return this->y<other.y;
    }
    bool operator==(ChunkPoint const& other)const
    {
        return (this->x==other.x&&this->y==other.y);
    }
    int x,y;
};
struct GameChunk
{
    bool ok=true;
};
struct GameMap
{
    GameMap()
        :min_point(ChunkPoint({-10,-10})),max_point(ChunkPoint({10,10}))
    {}
    GameMap(int minx,int miny,int maxx,int maxy)
        :min_point(ChunkPoint({minx,miny})),max_point(ChunkPoint({maxx,maxy}))
    {}
    GameChunk& FromChunkPoint(ChunkPoint cp)
    {
        if(cp.x>=min_point.x&&cp.x<=max_point.x&&cp.y>=min_point.y&&cp.y<=max_point.y)
            return gmap[cp];
        else
            throw 114514;
    }
    ChunkPoint FromGamePoint(GamePoint gp)
    {
        gp.x+=Settings::chunk_r,gp.y+=Settings::chunk_r;
        int dsx=(gp.x)/(Settings::chunk_r*2),dsy=(gp.y)/(Settings::chunk_r*2);
        ChunkPoint theone({0,0});
        for(int i=dsx-3;i<=dsx+3;i++)
        {
            for(int j=dsy-3;j<=dsy+3;j++)
            {
                //std::cout<<dsx<<" "<<dsy<<std::endl;
                if(IsPointInChunk(ChunkPoint({i,j}),gp.x,gp.y))
                {
                    return ChunkPoint({i,j});
                }
            }
        }
        return theone;
    }
    bool IsPointInChunk(ChunkPoint cp,int px,int py)
	{
	    GamePoint cpc=CalcChunkCenter(cp);
		int dx = std::abs(cpc.x-px);
		int dy = std::abs(cpc.y-py);
		if (dx <=Settings::chunk_r/2)
		{
			return dy<=Settings::chunk_r*2/2 * sqrt(3);
		}
		else
		{
			int maxy =-sqrt(3) * (dx-Settings::chunk_r*2/2) + Settings::chunk_r*2/2 * sqrt(3);
			return dy < maxy;
		}
	}
    static GamePoint CalcChunkCenter(ChunkPoint cp)
    {
        return GamePoint({int(cp.x*Settings::chunk_r*2*3/4),
                         int(Settings::chunk_r*2*cp.y+(abs(cp.x)%2==1?(Settings::chunk_r*2/2):0))});
                         //+(sqrt(Settings::chunk_r*Settings::chunk_r-0.5*Settings::chunk_r*0.5*Settings::chunk_r))
    }
    static double CalcLineLength(GamePoint a,GamePoint b)
    {
        return sqrt(abs(a.x-b.x)*abs(a.x*b.x)+abs(a.y-b.y)*abs(a.y-b.y));
    }
private:
    ChunkPoint min_point,max_point;
    std::map<ChunkPoint,GameChunk> gmap;
};
}

#endif // GAME_MAP_H_INCLUDED
