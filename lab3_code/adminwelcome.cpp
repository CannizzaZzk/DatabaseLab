#include "adminwelcome.h"
#include "ui_adminwelcome.h"
#include "adminflight.h"
#include "register.h"
#include "adminorder.h"
#include <QDateTime>
#include <QTime>
#include <QSqlQuery>


AdminWelcome::AdminWelcome(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminWelcome)
{
    ui->setupUi(this);
    setMaximumSize(450,400);
    setMinimumSize(450,400);
    upDate();
}

AdminWelcome::~AdminWelcome()
{
    delete ui;
}

void AdminWelcome::on_pushButton_clicked()
{
    this->hide();
    AdminFlight ah;
    ah.show();
    ah.exec();
    this->show();
}

void AdminWelcome::on_pushButton_2_clicked()
{
    this->hide();
    AdminOrder ao;
    ao.show();
    ao.exec();
    this->show();
}

void AdminWelcome::on_pushButton_3_clicked()
{
    int flag = 1;
    Register re(&flag);
    re.show();
    re.exec();

}

void AdminWelcome::upDate()
{
    QSqlQuery flight,query;
    flight.exec(QString("select * from FLIGHTS;"));
    QString Ftime;
    QString TimeNow;
    while(flight.next())
    {

        TimeNow = QDateTime().currentDateTime().toString("yyyyMMdd");
        TimeNow = TimeNow + QTime().currentTime().toString("hhmm");

        Ftime = flight.value(3).toString();
        if(TimeNow.mid(0,8).toInt()>Ftime.mid(0,8).toInt())
            Delete(flight.value(0).toString());
        else if (TimeNow.mid(0,8).toInt() == Ftime.mid(0,8).toInt()) {
            if(TimeNow.mid(8,4).toInt() > Ftime.mid(8,4).toInt())
                Delete(flight.value(0).toString());
        }
    }
}
void AdminWelcome::Delete(QString fid)
{
    QString Fid = fid;
    QSqlQuery query;
    query.exec(QString("delete from ANOUNCEMENT where FID = '%1';").arg(Fid));
    query.exec(QString("delete from BILL where FID = '%1';").arg(Fid));
    query.exec(QString("delete from TICKETS where FID = '%1';").arg(Fid));
    query.exec(QString("delete from SEAT where FID = '%1';").arg(Fid));
    query.exec(QString("delete from FLIGHTS where FID = '%1';").arg(Fid));
    return;
}

void AdminWelcome::on_pushButton_4_clicked()
{
    this->close();
}
