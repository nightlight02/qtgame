#include "monster.h"
#include "config.h"

extern int map[24][24];

monster::monster()
{
    is_right=1;
    picture.load(MONSTER_PIC);
}
void monster::move(){
    if(is_right&&!right_touch())right();
    else if(is_right&&right_touch())is_right=0;
    else if(!is_right&&!left_touch())left();
    else if(!is_right&&left_touch())is_right=1;
}
bool monster::right_touch(){
    if(map[x/B+1][y/B]!=1&&map[x/B+1][y/B+1]==1&&x + MONSTER_MOVE_SPEED < XSIZE - w)return 0;
    return 1;
}
bool monster::left_touch(){
    if(map[(x-5)/B][y/B]!=1&&map[(x-5)/B][y/B+1]==1&&x - MONSTER_MOVE_SPEED > 0)return 0;
    return 1;
}
void monster::right()
{
    if(!right_touch())
     x = (x + MONSTER_MOVE_SPEED < XSIZE - w) ? x + MONSTER_MOVE_SPEED : XSIZE - w;
}
void monster::left()
{
    if(!left_touch())
     x = (x - MONSTER_MOVE_SPEED > 0) ? x - MONSTER_MOVE_SPEED : 0;
}
