#ifndef TIME_CENTER_H_INCLUDED
#define TIME_CENTER_H_INCLUDED

#include <list>
#include <functional>
#include "game_settings.h"

namespace Game
{
struct TimeCenter
{
public:
    static TimeCenter& Instance()
    {
        static TimeCenter _tc;
        return _tc;
    }
    void RegisterCallback(std::function<void(int)> _cb)
    {
        _callbacks.push_back(_cb);
    }
    void OnTimer(int interval)
    {
        waited_time+=interval;
        if(waited_time<Settings::wait_of_notice)
        {
            return;
        }
        for(auto &cb:_callbacks)
        {
            cb(waited_time);
        }
        waited_time=0;
    }
private:
    int waited_time=0;//ms
    std::list<std::function<void(int)>> _callbacks;
};
}
#endif // TIME_CENTER_H_INCLUDED
