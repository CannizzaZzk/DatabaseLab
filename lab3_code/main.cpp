#include "login.h"
#include "dataconnect.h"
#include "adminwelcome.h"
#include "userwelcome.h"
#include <QDialog>
#include <QApplication>
#include <QTime>
#include <QtDebug>
#include <QDateTime>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //连接数据库(初次启动)
    DataConnect dataconnect;
    dataconnect.connectDB();

    qDebug()<<QTime().currentTime().toString("hhmm")<<endl;
    qDebug()<<QDateTime().currentDateTime().toString("yyyyMMdd")<<endl;
    //程序启动
    int flag = 0;//用户参数
    int uid = -1;
    Login lw(&flag,&uid);
    lw.show();
    lw.exec();
    if(flag == 0)
       return a.exec();


    //创建用户及管理员窗口

    AdminWelcome aw;
    UserWelcome uw(&flag,uid);
    if(flag == 1)
        aw.show();
    else
        uw.show();
    return a.exec();
}
