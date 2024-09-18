#ifndef SDL_TIMER_HPP_INCLUDED
#define SDL_TIMER_HPP_INCLUDED

#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_events.h>

namespace sdl2
{
struct Timer
{
    Timer()
        :timer_id(0),interval(0),event_code(0),user_data(nullptr)
    {}
    ~Timer()
    {
        if(timer_id!=0)
            SDL_RemoveTimer(timer_id);
    }
    explicit operator bool()const
    {
        return timer_id!=0;
    }
    Timer(Timer const&)=delete;
    Timer& operator =(Timer const&)=delete;
    bool Start(Uint32 interval,unsigned int event_code=0,void* data=nullptr)
    {
        if(timer_id!=0)
            return false;
        this->user_data=data;
        this->interval=interval;
        this->event_code=event_code;
        timer_id=SDL_AddTimer(interval,&Timer::Callback,this);
        return (0!=timer_id);

    }
    void Stop()
    {
        if(timer_id!=0)
        {
            SDL_RemoveTimer(timer_id);
            timer_id=0;
        }
    }
private:
    static Uint32 Callback(Uint32 interval,void *param)
    {
        Timer *self=static_cast<Timer*>(param);
        if(!self)return 0;
        SDL_Event event;
        event.type=SDL_USEREVENT;
        event.user.code=self->event_code;
        event.user.data1=self;
        event.user.data2=self->user_data;
        if(1!=SDL_PushEvent(&event))
        {
            self->timer_id=0;
            return 0;
        }
        return interval;
    }
private:
    SDL_TimerID timer_id;
    Uint32 interval;
    unsigned int event_code;
    void* user_data;
};
}


#endif // SDL_TIMER_HPP_INCLUDED
