#include "userolpay.h"
#include "ui_userolpay.h"

userOLPay::userOLPay(int uid,int tid,QString fid,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::userOLPay)
{
    ui->setupUi(this);
    setWindowTitle("在线支付");
    UidNow = uid;
    this->tid = tid;
    FlightId = fid;
}

userOLPay::~userOLPay()
{
    delete ui;
}

void userOLPay::on_pushButton_2_clicked()
{
    //删除账单，更新状态
    QSqlQuery query;
    query.exec(QString("delete from BILL where UID = %1 and FID = '%2' and TID = %3;").arg(UidNow,0,10).arg(FlightId).arg(this->tid,0,10));
    query.exec(QString("update ANOUNCEMENT set TSTATE = 1 where UID = %1 and FID = '%2' and TID = %3;").arg(UidNow,0,10).arg(FlightId).arg(this->tid,0,10));
    query.exec(QString("update TICKETS set TSTATE = 1 where UID = %1 and FID = '%2' and TID = %3;").arg(UidNow,0,10).arg(FlightId).arg(this->tid,0,10));
    this->close();

}

void userOLPay::on_quitbtn_clicked()
{
    this->close();
}
