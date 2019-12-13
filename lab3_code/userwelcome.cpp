#include "userwelcome.h"
#include "ui_userwelcome.h"
#include "userflight.h"
#include "userorder.h"
#include "userbill.h"
#include "useranocmnt.h"
#include <QDateTime>
#include <QTime>

UserWelcome::UserWelcome(int *flag, int id,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UserWelcome),
    idNow(id)
{
    ui->setupUi(this);
    setMaximumSize(450,400);
    setMinimumSize(450,400);
    IDflag = flag;
    upDate();
}

UserWelcome::~UserWelcome()
{
    delete ui;
}

void UserWelcome::on_pushButton_clicked()
{
    this->hide();
    UserFlight uh(IDflag,idNow);
    uh.show();
    uh.exec();
    this->show();
}

void UserWelcome::on_pushButton_2_clicked()
{
    userOrder ur(idNow);
    ur.show();
    ur.exec();
}

void UserWelcome::on_billbtn_clicked()
{
    userBill ub(idNow);
    ub.show();
    ub.exec();
}

void UserWelcome::on_billbtn_2_clicked()
{
    userAnocmnt ua(idNow);
    ua.show();
    ua.exec();
}
void UserWelcome::upDate()
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
void UserWelcome::Delete(QString fid)
{
    QString Fid = fid;
    QSqlQuery query;
    qDebug()<<"delete 执行"<<" 删除"<<Fid<<endl;
    query.exec(QString("delete from ANOUNCEMENT where FID = '%1';").arg(Fid));
    query.exec(QString("delete from BILL where FID = '%1';").arg(Fid));
    query.exec(QString("delete from TICKETS where FID = '%1';").arg(Fid));
    query.exec(QString("delete from SEAT where FID = '%1';").arg(Fid));
    query.exec(QString("delete from FLIGHTS where FID = '%1';").arg(Fid));
    return;
}

void UserWelcome::on_billbtn_3_clicked()
{
    this->close();
}
