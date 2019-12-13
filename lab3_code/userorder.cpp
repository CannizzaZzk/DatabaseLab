#include "userorder.h"
#include "ui_userorder.h"
#include <QSqlTableModel>
#include <QtDebug>
#include <QMessageBox>

userOrder::userOrder(int uid,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::userOrder)
{
    idNow = uid;
    ui->setupUi(this);
    setWindowTitle("未出行订单");
    setMinimumSize(1020,700);
    setMaximumSize(1020,700);
    createLeftLayout();
}

void userOrder::createLeftLayout()
{
    ui->tableView->setSortingEnabled(true);//开启排序
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);//每次选择一行
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);//单机选择
    ui->tableView->setShowGrid(true);
    ui->tableView->setAlternatingRowColors(true);
    ui->tableView->verticalHeader()->setVisible(false);

    TicketModel = new QSqlTableModel(this);
    TicketModel->setTable("TICKETS");
    TicketModel->select();

/*修改完这个订单系统，加上实名功能，更新功能
 * ===============================
 * ===============================
 * ===============================*/

    //列出机票数据
    QStringList title;
    title<<"航班"<<"出发"<<"目的地"<<"起飞时间"<<"座位号"<<"舱位"<<"价格"<<"支付状态";
    QSqlQuery query;
    query.exec(QString("select count(*) from TICKETS where UID = %1; ").arg(idNow,0,10));
    query.next();
    int numRaw = query.value(0).toInt();
    item_model = new QStandardItemModel(numRaw,8);
    QSqlQuery flight;
    QSqlQuery seat;
    QSqlQuery ticket;

    ticket.exec(QString("select * from TICKETS where UID = %1;").arg(idNow,0,10));

    QString numSeat;
    QString SeatType;
    QString Price;
    QString PayState;
    QString FStart;
    QString FEnd;
    QString Ftime,OriTime;
    QString Fid;
    int count = 0;
    item_model->setHorizontalHeaderLabels(title);
    while(ticket.next())
    {
        seat.exec(QString("select * from SEAT where TID = %1 and FID = '%2';").arg(ticket.value(0).toInt(),0,10).arg(ticket.value(1).toString().trimmed()));
        seat.next();
        numSeat = seat.value(0).toString() + seat.value(1).toString();//座位号，36A之类的
        if(seat.value(7).toInt()==1)
            SeatType = "头等舱";
        else
            SeatType = "经济舱";
        Price = seat.value(6).toString();

        if(ticket.value(4).toInt() == 0)
            PayState = "未支付";
        else
            PayState = "已支付";

        flight.exec(QString("select * from FLIGHTS where FID = '%1';").arg(ticket.value(1).toString().trimmed()));
        flight.next();
        Fid = flight.value(0).toString();
        FStart =flight.value(1).toString();
        FEnd = flight.value(2).toString();
        OriTime = flight.value(3).toString();
        Ftime = OriTime.mid(0,4).append("年").append(OriTime.mid(4,2)).append("月").append(OriTime.mid(6,2)).append("日").append(OriTime.mid(8,2)).append("时").append(OriTime.mid(10,2)).append("分");

        qDebug()<<"fid= "<<Fid<<endl;
        qDebug()<<"ORitime: "<<OriTime<<endl;
        qDebug()<<"ticket record: "<<ticket.value(0).toInt()<<ticket.value(1).toString()<<ticket.value(2).toInt()<<ticket.value(3).toInt()<<endl;

        item_model->setItem(count,0,new QStandardItem(Fid));
        item_model->setItem(count,1,new QStandardItem(FStart));
        item_model->setItem(count,2,new QStandardItem(FEnd));
        item_model->setItem(count,3,new QStandardItem(Ftime));
        item_model->setItem(count,4,new QStandardItem(numSeat));
        item_model->setItem(count,5,new QStandardItem(SeatType));
        item_model->setItem(count,6,new QStandardItem(Price));
        item_model->setItem(count,7,new QStandardItem(PayState));
        count++;
    }


    ui->tableView->setModel(item_model);

}

userOrder::~userOrder()
{
    delete ui;
}

void userOrder::on_cnlbtn_clicked()
{
    QString FStart;
    QString FEnd;
    QString Ftime,OriTime;
    QString Fid;
    int Tid;
    QString numSeat;
    QSqlQuery flight;
    QSqlQuery seat;
    QSqlQuery ticket;
    QSqlQuery query;

    Fid = ticketRecord.value("FID").toString();
    Tid = ticketRecord.value("TID").toInt();

    flight.exec(QString("select * from FLIGHTS where FID = '%1';").arg(Fid));
    flight.next();

    seat.exec(QString("select * from SEAT where FID = '%1' and TID = %2;").arg(Fid).arg(Tid,0,10));
    seat.next();

    FStart = flight.value(1).toString();
    FEnd = flight.value(2).toString();
    OriTime = flight.value(3).toString();

    numSeat = seat.value(0).toString() + seat.value(1).toString();

    Ftime =  OriTime.mid(0,4).append("年").append(OriTime.mid(4,2)).append("月").append(OriTime.mid(6,2)).append("日");

    QMessageBox::StandardButton button;
    button = QMessageBox::question(this, tr("取消订单"), QString(tr("你确定退订%1从%2飞往%3的%4航班%5号座位吗?").arg(Ftime.trimmed()).arg(FStart.trimmed()).arg(FEnd.trimmed()).arg(Fid.trimmed()).arg(numSeat)), QMessageBox::Yes|QMessageBox::No);
    if(button == QMessageBox::Yes)
    {

        query.exec(QString("delete from ANOUNCEMENT where TID = %1 and FID = '%2';").arg(Tid,0,10).arg(Fid));
        query.exec(QString("delete from BILL where TID = %1 and FID = '%2';").arg(Tid,0,10).arg(Fid));
        ticket.exec(QString("delete from TICKETS where TID = %1 and FID = '%2';").arg(Tid,0,10).arg(Fid));
        seat.exec(QString("update SEAT set UID = NULL, TID = NULL, SVALID = 1 where TID = %1 and FID = '%2';").arg(Tid,0,10).arg(Fid));
        createLeftLayout();
        if(ticketRecord.value("TSTATE").toInt()==0)
            QMessageBox::about(NULL, "通知", "退票成功！");
        else
            QMessageBox::about(NULL, "通知", "退票成功，退款已原路返还请注意查收。");
    }
}

void userOrder::on_refreshbtn_clicked()
{
    createLeftLayout();
}

void userOrder::on_quitbtn_clicked()
{
    this->close();
}

void userOrder::on_tableView_clicked(const QModelIndex &index)
{
    QSqlRecord record = TicketModel->record(index.row());
    ticketRecord = record;

}
