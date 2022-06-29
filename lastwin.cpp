#include "lastwin.h"
#include "ui_lastwin.h"
#include "widget.h"
#include "config.h"
#include "mainscreen_second.h"
#include "dialog.h"

lastwin::lastwin(int allgold_,double alltime_,QWidget *parent) :
    QDialog(parent),allgold(allgold_),alltime(alltime_),
    ui(new Ui::lastwin)
{
    ui->setupUi(this);
    setWindowTitle(TITLE);
    setWindowIcon(QIcon(GAMEICON));
    int width = 768;
    int height = 768;
    this->setFixedSize(width,height); //设置窗体固定大小
    drawgold();
}

lastwin::~lastwin()
{
    delete ui;
}

void lastwin::drawgold()
{
    label2 =new QLabel(this);
    font.setFamily("Fusion Pixel");//字体
    font.setBold(true);
    font.setPointSize(15);//文字大小

    print="恭喜你通关了!\n\n""通关用时为：";
    print+=QString::number(alltime,'lf',2).append('s');
    print+="\n";
    print+="\n你共获得的金币为：";
    print+=QString::number(allgold).append('/');
    print+=QString::number(GOLDFIRST+GOLDSECOND);

    label2->setText(print);
    label2->setStyleSheet("color: black");
    label2->move(200,200);
    label2->setFont(font);
    label2->show();
}


void lastwin::on_pushButton_clicked() //再来一局
{
    mainscreen *d = new mainscreen;
    d->setAttribute(Qt::WA_DeleteOnClose, true);
    d->show();
    close();
}

void lastwin::on_pushButton_2_clicked()  //返回主菜单
{
    Widget *w = new Widget;
    w->setAttribute(Qt::WA_DeleteOnClose, true);
    w->music->stop();
    w->show();
    close();
}
