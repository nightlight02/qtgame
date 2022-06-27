#include "mainscreen.h"
#include "ui_mainscreen.h"

#include "config.h"

#include "qpainter.h"
#include "QKeyEvent"

#include "firstwin.h"
#include "goldbuy.h"
#include "youlose.h"

int map[24][24];

mainscreen::mainscreen(QWidget *parent) : QWidget(parent), ui(new Ui::mainscreen)
{
  ui->setupUi(this);
  init();
  gamestart();
}

mainscreen::~mainscreen()
{
  delete ui;
}

void mainscreen::init()//初始化
{
  setFixedSize(XSIZE, YSIZE);
  setWindowTitle(TITLE);
  Timer.setInterval(GAME_TICK);
  Mapinit();
  drawgold();
}

void mainscreen::Mapinit(){//地图初始化
    for(int i=0;i<24;i++)
    for(int j=23;j>20;j--) map[i][j]=1;
    for(int i=0;i<17;i++)map[i][19]=1;
    for(int i=23;i>17;i--)map[i][18]=1;
    for(int i=7;i<22;i++)map[i][16]=1;
    for(int i=0;i<14;i++)map[i][13]=1;
    for(int i=4;i<9;i++)map[i][5]=1;
    for(int i=0;i<3;i++)map[i][2]=1;

    map[4][18]=map[20][15]=map[13][14]=map[16][14]=
    map[17][14]=map[18][14]=map[21][14]=map[22][13]=
    map[22][12]=map[20][12]=map[19][12]=map[18][12]=
    map[2][11]=map[3][11]=map[22][11]=map[13][10]=
    map[16][10]=map[17][10]=map[21][10]=map[0][9]=
    map[1][9]=map[6][9]=map[7][9]=map[5][9]=
    map[12][9]=map[19][9]=map[20][9]=map[21][9]=
    map[11][8]=map[15][8]=map[16][8]=map[2][7]=
    map[3][7]=map[10][7]=map[9][6]=map[17][6]=
    map[18][6]=map[19][6]=map[23][6]=map[15][5]=
    map[14][5]=map[20][5]=map[22][5]=map[12][4]=
    map[13][4]=map[22][4]=map[4][3]=map[5][3]=
    map[11][3]=map[10][2]=map[9][1]=map[9][0]=1;

    map[17][16]=map[18][16]=0;
    map[1][1]=2;
    map[1][17]=map[10][15]=map[21][15]=map[15][12]=
    map[2][10]=map[11][6]=map[2][4]=map[23][4]=
    map[16][3]=3;
    map[15][20]=4;

    mons[0].is_alive=1,mons[0].x=4*B,mons[0].y=0;
    mons[1].is_alive=1,mons[1].x=4*B,mons[1].y=20*B;
}

void mainscreen::gamestart()//主循环
{
  Timer.start();
  connect(&Timer, &QTimer::timeout, [=]()
          {//每帧执行任务
            labelblood1->setText(QString::number(pl.blood));
            label1->setText(QString::number(pl.goldnum));
            if(!pl.is_ground())pl.is_jump=1;
            for (int i=0;i<MSTRNUM;i++){
                if(mons[i].is_alive){
                if(!mons[i].is_ground())mons[i].fall();
                else mons[i].move();
                }
            }
            if(pl.is_jump)pl.fall();
            if(leftpress){
                background.mappositionl();
                pl.left();
            }
            if(rightpress){
                background.mappositionr();
                pl.right();
            }
            if(pl.wincheck())
            {
                gamewin();
                close();
                Timer.stop();
            }
            if(pl.goldcheck())
            {
                pl.goldnum++;
                pl.allgoldnum++;
                map[pl.x/B][pl.y/B]=0;
            }
            if(pl.dicicheck())
              {
                   pl.blood-=2;
              }
            if(pl.blood == 0)
                        {
               gamelose();
               close();
               Timer.stop();
                        }
        update(); });
}

void mainscreen::paintEvent(QPaintEvent *event) //绘制事件
{
  QPainter painter(this);
  painter.drawPixmap(background.map1_x, 0,XSIZE,YSIZE, background.map1); //绘制背景图
  painter.drawPixmap(background.map2_x, 0,XSIZE,YSIZE, background.map2);
  painter.drawPixmap(background.map3_x, 0,XSIZE,YSIZE, background.map3);
  painter.drawPixmap(pl.x, pl.y, W, H, pl.picture); //绘制角色
  block1.load(BLOCK1);//地图绘制
  block2.load(BLOCK2);
  block3.load(BLOCK3);
  block4.load(BLOCK4);
    for(int i=0;i<24;i++)
        for(int j=0;j<24;j++)
            switch(map[i][j]){
            case 1:
                painter.drawPixmap(i*B, j*B,W,W, block1);
                break;
            case 2:
                painter.drawPixmap(i*B, j*B,W,W, block2);
                break;
            case 3:
                painter.drawPixmap(i*B, j*B,W,W, block3);
                break;
            case 4:
                painter.drawPixmap(i*B, j*B,W,W, block4);
                break;
            }
  for(int i=0;i<MSTRNUM;i++)if(mons[i].is_alive)painter.drawPixmap(mons[i].x, mons[i].y, W, H, mons[i].picture);
}

void mainscreen::drawgold()//金币label
{
    label1 =new QLabel(this);
    label2 =new QLabel(this);
    font.setFamily("SimHei");//字体
    font.setPointSize(10);//文字大小
    label1->setText(QString::number(pl.goldnum));
    label1->setStyleSheet("color: black");
    label1->move(620,20);
    label1->setFont(font);
    label1->show();
    label2->setText("金币数");
    label2->setStyleSheet("color: black");
    label2->move(520,20);
    label2->setFont(font);
    label2->show();

    labelblood1 =new QLabel(this);
       labelblood2 =new QLabel(this);
       labelblood1->setText(QString::number(pl.blood));
       labelblood1->setStyleSheet("color: black");
       labelblood1->move(650,50);
       labelblood1->setFont(font);
       labelblood1->show();
       labelblood2->setText("目前血量");
       labelblood2->setStyleSheet("color: black");
       labelblood2->move(520,50);
       labelblood2->setFont(font);
       labelblood2->show();

}

void mainscreen::keyPressEvent(QKeyEvent *event) //按键事件
{
  if (event->key() == Qt::Key_A && event->type())
  {
    leftpress = 1;
  }
  if (event->key() == Qt::Key_D)
  {
    rightpress = 1;
  }
  if (event->key() == Qt::Key_K && !pl.is_jump)
  {
    pl.jump();
  }
  if (event->key() == Qt::Key_J) //可能会有的攻击
  {
  }
  update();
}

void mainscreen::keyReleaseEvent(QKeyEvent *event)//松开按键事件
{
  if (event->key() == Qt::Key_A && event->type())
  {
    leftpress = 0;
  }
  if (event->key() == Qt::Key_D)
  {
    rightpress = 0;
  }
  update();
}

void mainscreen::gamewin()//胜利界面
{
    firstwin *win= new firstwin(pl.allgoldnum);
    win->show();
}

void mainscreen::on_pushButton_clicked()//金币商店part
{
    goldbuy *buy= new goldbuy(pl);
    buy->show();
    pl.goldnum=buy->nowgold();
        update();
}

void mainscreen::gamelose()  //失败界面待补充，暂时先用成功界面替着
{
    youlose *lose= new youlose(pl.allgoldnum);
    lose->show();
}
