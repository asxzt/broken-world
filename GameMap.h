#ifndef GAMEMAP_H_INCLUDED
#define GAMEMAP_H_INCLUDED

#include <map>
using BlockID=unsigned int;
struct Block
{
    BlockID ci;
};
struct Chunk
{
public:
    Chunk()
        :data(nullptr)
    {}
    explicit Chunk(Chunk const &other)
    {
        if(Init())
            for(int i=0;i<16*16;i++)
                (this->data)[i]=(other.data)[i];
    }
    Chunk& operator=(const Chunk &other)
    {
        if(other.data==this->data)
        {
            return *this;
        }
        if(!this->data)
        {
            if(!Init())
                return *this;//nullptr
        }
        for(int i=0;i<16*16;i++)
            (this->data)[i]=(other.data)[i];
        return *this;
    }
    ~Chunk()
    {
        if(data)
            delete[] data;
    }
    bool Init()
    {
        if(data!=nullptr)return false;
        try
        {
            data=new Block[16*16];
        }
        catch(...)
        {
            data=nullptr;
            return false;
        }
        return true;
    }
    Block Get(int x,int y)const
    {
        return data[x*16+y];
    }
    void Set(int x,int y,Block c)
    {
        data[x*16+y]=c;
    }
    Block* data;
};
struct ChunkCoordinate
{
    unsigned int x,y;
};
struct GameMap
{
    GameMap()
    {}
    ~GameMap()
    {}
private:
    std::map<ChunkCoordinate,Chunk> _m;
};
#endif // GAMEMAP_H_INCLUDED
