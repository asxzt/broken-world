#ifndef GAME_SETTINGS_H_INCLUDED
#define GAME_SETTINGS_H_INCLUDED

#include <map>
#include <string>
namespace Game
{
namespace Settings
{
    const int screen_x=960;
    const int screen_y=540;
    const int chunk_r=64;
    const int enabled_click_fix=15;
    const int wait_of_notice=50;//ms (tick)
    const std::map<std::string,std::string> images({
    {"hexagon","asserts/images/honxy.png"},
    {"hexagon_hlt","asserts/images/honxy_hlt.png"},
    {"ui_menu1","asserts/images/ui_menu1.png"},
    {"ui_menu2","asserts/images/ui_menu2.png"}
    });

    const int FontSizeTranslate[7]={12,18,24,36,48,60,72};
}
}

#endif // GAME_SETTINGS_H_INCLUDED
