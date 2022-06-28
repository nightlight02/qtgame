#include "player.h"
#include "mainscreen.h"
#include "config.h"
#include "stdio.h"
#include "dialog.h"
#include "qtimer.h"

extern int map[24][24];
player::player()
{
  x = X, y = Y, h = H, w = W;
  blood = INIT_HP;
  is_jump = 0;
  v0 = 0, t = 0;
  hittimer=0;
  goldnum = 0;
  allgoldnum=0;
  picture.load(PLAYER_PIC);
}
bool player::is_ground()
{
          if(map[(x+5)/B][(y+H)/B]!=0||map[(x+w-5)/B][(y+H)/B]!=0)
          {
              if(map[(x+5)/B][(y+H)/B]==1||map[(x+w-5)/B][(y+H)/B]==1)
                return 1;
          }
      return 0;
}
bool player::right_touch(){
    if(map[x/B+1][y/B]!=1)return 0;
    else return 1;
}
bool player::left_touch(){
    if(map[(x-5)/B][y/B]!=1)return 0;
    else return 1;
}
bool player::head_touch(){
   if( map[(x+5)/B][(y)/B]==1||map[(x+w-5)/B][(y)/B]==1)
       return 1;
   else return 0;
}
void player::right()
{
    if(!right_touch())
     x = (x + MOVE_SPEED < XSIZE - w) ? x + MOVE_SPEED : XSIZE - w;
}
void player::left()
{
    if(!left_touch())
     x = (x - MOVE_SPEED > 0) ? x - MOVE_SPEED : 0;
}
void player::jump()
{
      v0 = -sqrt(2 * G * HIGHT);
      is_jump = 1;
      fall();
}
void player::fall()
{
      t = sqrt(2 * HIGHT / G) / 14;
      h1=v0*t+G*pow(t,2)/2;
      y+=(int)(h1+0.5);
      if(v0>0){
      if(is_ground()){
           y=y/B*B;
           v0=0;
           is_jump=0;
      }
      }
      else {
          if(head_touch()){
                    v0 = 0;
                    h1 = 0;
                    y = y / h * h + h;
                }
          y+=(int)(h1+0.5);
      }
          v0=v0+G*t;
}
bool player::wincheck()
{
    if(map[x/B][y/B]==2||map[(x+W)/B][y/B]==2)  //到达id为2的方块时获胜
    {
        return true;
    }
    return false;
}
int player::goldcheck()
{
    if(map[x+5/B][y/B]==3)  //到达id为3的方块时获取金币
    {
        map[x+5/B][y/B]=0;
        return 1;
    }
    else if(map[(x+W-5)/B][y/B]==3)
    {
        map[(x+W-5)/B][y/B]=0;
        return 2;
    }
    return 0;
}
bool player::dicicheck()//到达id为4的方块时,视为站在地刺上，以每秒10滴血的速度掉血
{
    if(map[x/B][y/B]==4||map[(x+W)/B][y/B]==4)
    {
        return true;
    }
    return false;
}
bool player::touch(player mons){
    if(x+5>mons.x&&x+5<mons.x+W&&y+5>mons.y&&y+5<mons.y+H)return 1;
    if(x+W-5>mons.x&&x+W-5<mons.x+W&&y+5>mons.y&&y+5<mons.y+H)return 1;
    if(x+5>mons.x&&x+5<mons.x+W&&y+H-5>mons.y&&y+H-5<mons.y+H)return 1;
    if(x+W-5>mons.x&&x+W-5<mons.x+W&&y+H-5>mons.y&&y+H-5<mons.y+H)return 1;
    return 0;
}
void player::injure(){
    qDebug("%dhittimer:",hittimer);
    if(hittimer==0){
        blood-=10;
        hittimer++;
    }
}
