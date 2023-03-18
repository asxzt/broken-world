#ifndef GAMEMAP_H_INCLUDED
#define GAMEMAP_H_INCLUDED

#include <map>
using CubeID=unsigned int;
struct Cube
{
    CubeID ci;
};
struct Block
{
public:
    Block()
        :data(nullptr)
    {}
    Block(Block const &other)
    {
        if(this->data&&other.data!=this->data)
        {
            for(int i=0;i<16*16;i++)
                (this->data)[i]=(other.data)[i];
        }
    }
    Block& operator=(const Block &other)
    {
        if(other.data==this->data||!this->data)
        {
            return *this;
        }
        for(int i=0;i<16*16;i++)
            (this->data)[i]=(other.data)[i];
        return *this;
    }
    ~Block()
    {
        if(!data)
            delete[] data;
    }
    bool Init()
    {
        try
        {
            data=new Cube[16*16];
        }
        catch(...)
        {
            data=nullptr;
            return false;
        }
        return true;
    }
    Cube Get(int x,int y)const
    {
        return data[x*16+y];
    }
    void Set(int x,int y,Cube c)
    {
        data[x*16+y]=c;
    }
    Cube* data;
};
struct GameMap
{
    //fuck!!!
};
#endif // GAMEMAP_H_INCLUDED
