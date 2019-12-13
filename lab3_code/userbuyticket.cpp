#include "userbuyticket.h"
#include "ui_userbuyticket.h"
#include <QtDebug>
#include <QMessageBox>


UserBuyTicket::UserBuyTicket(QString fid,int uid,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserBuyTicket),
    UidNow(uid)
{
    FlightId = fid;
    ui->setupUi(this);
    setWindowTitle("机票购买");
    setMinimumSize(525,400);
    setMaximumSize(525,400);
    createLeftLayout();
}

void UserBuyTicket::createLeftLayout()
{
    ui->tableView->setSortingEnabled(true);//开启排序
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);//每次选择一行
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);//单机选择
    ui->tableView->setShowGrid(true);
    ui->tableView->setAlternatingRowColors(true);
    ui->tableView->verticalHeader()->setVisible(false);

    SEATModel = new QSqlTableModel(this);
    SEATModel->setTable("SEAT");

    SEATModel->setFilter(QObject::tr("FID = '%1'and SVALID = 1;").arg(FlightId));
    SEATModel->select();


    qDebug()<<"测试："<<endl;
    //列出机票数据
    QStringList title;
    title<<"座位号"<<"舱位"<<"价格";
    QSqlQuery query;
    query.exec(QString("select count(*) from SEAT where FID = '%1' and SVALID = 1; ").arg(FlightId));
    query.next();
    int numRaw = query.value(0).toInt();
    item_model = new QStandardItemModel(numRaw,3);
    query.exec(QString("select * from SEAT where FID = '%1' and SVALID = 1").arg(FlightId));
    QString numSeat;
    QString SeatType;
    QString Price;
    int count = 0;
    item_model->setHorizontalHeaderLabels(title);
    while(query.next())
    {
        numSeat = query.value(0).toString() + query.value(1).toString();//座位号，36A之类的
        if(query.value(7).toInt()==1)
            SeatType = "头等舱";
        else
            SeatType = "经济舱";
        Price = query.value(6).toString();
        //qDebug()<<Price<<endl;
        item_model->setItem(count,0,new QStandardItem(numSeat));
        item_model->setItem(count,1,new QStandardItem(SeatType));
        item_model->setItem(count,2,new QStandardItem(Price));
        count++;
    }


    ui->tableView->setModel(item_model);




}




UserBuyTicket::~UserBuyTicket()
{
    delete ui;
}

void UserBuyTicket::on_pushButton_clicked()
{
     this->close();
}

void UserBuyTicket::on_tableView_clicked(const QModelIndex &index)
{

    //获取选中行数据表中的数据并分离出来
    QSqlRecord record = SEATModel->record(index.row());
    seatRecord = record;

}

void UserBuyTicket::on_pushButton_2_clicked()
{
     createLeftLayout();
}

void UserBuyTicket::on_pushButton_3_clicked()
{
    QString numSeat = seatRecord.value("SRAW").toString() + seatRecord.value("SCOLUMN").toString();
    int numR = seatRecord.value("SRAW").toInt();
    int price = seatRecord.value("TPRICE").toInt();
    QString numC =seatRecord.value("SCOLUMN").toString();
    QMessageBox::StandardButton button;
    button = QMessageBox::question(this, tr("订票"), QString(tr("你确定预订座位 '%1' 吗?").arg(numSeat.trimmed())), QMessageBox::Yes|QMessageBox::No);
    //加入实名认证
    QSqlQuery query;
    QString Atime;
    int tid = 1;
    if(button == QMessageBox::Yes)
    {
        query.exec(QString("select TID from SEAT where FID = '%1' order by TID DESC").arg(FlightId));
        query.next();
        tid = query.value(0).toInt();
        query.exec(QString("update SEAT set TID = %1 where FID = '%2' and SRAW = %3 and SCOLUMN = '%4';").arg(tid+1,0,10).arg(FlightId).arg(numR,0,10).arg(numC));
        query.exec(QString("update SEAT set SVALID = %1 where FID = '%2' and SRAW = %3 and SCOLUMN = '%4';").arg(0,0,10).arg(FlightId).arg(numR,0,10).arg(numC));
        query.exec(QString("update SEAT set UID = %1 where FID = '%2' and SRAW = %3 and SCOLUMN = '%4';").arg(UidNow,0,10).arg(FlightId).arg(numR,0,10).arg(numC));
        query.exec(QString("insert into TICKETS values(%1,'%2',%3,%4,0);").arg(tid+1,0,10).arg(FlightId).arg(UidNow,0,10).arg(price,0,10));
        query.exec(QString("select FTIME from FLIGHTS where FID = '%1';").arg(FlightId));
        query.next();
        Atime = query.value(0).toString();
        TimeOp(Atime);
        //qDebug()<<"Atime after"<<Atime<<endl;
        query.exec(QString("insert into ANOUNCEMENT values(%1,'%2',%3,'%4',0);").arg(tid+1,0,10).arg(FlightId).arg(UidNow,0,10).arg(Atime));
        query.exec(QString("insert into BILL values(%1,'%2',%3,%4);").arg(tid+1,0,10).arg(FlightId).arg(UidNow,0,10).arg(price,0,10));
        QMessageBox::about(NULL, "通知", "订票成功！");
        createLeftLayout();
    }
}

void UserBuyTicket::TimeOp(QString &Atime)
{
    QString Month,Day,Year;
    Year = Atime.mid(0,4);
    Month = Atime.mid(4,2);
    Day = Atime.mid(6,2);
    //qDebug()<<"Atime before  "<<Atime<<endl;
    if(Day.toInt() >= 11)
        Day = QString::number(Day.toInt()-1,10);
    else if(Day.toInt() > 1)
    {
        Day = QString::number(Day.toInt()-1,10);
        //Day.insert(0,"0");
    }
    else {

        if(Month.toInt() == 1)
        {
            Year = QString::number(Year.toInt()-1,10);
            Month = QString::number(12,10);
            Day = QString::number(31,10);
        }
        else if (Month.toInt() == 2 || Month.toInt() == 4 || Month.toInt() == 6 || Month.toInt() == 8 || Month.toInt() == 9 || Month.toInt() == 11) {
            Month = QString::number(Month.toInt()-1,10);
            Day = QString::number(31,10);
        }
        else if(Month.toInt() == 3) {
            Month = QString::number(Month.toInt()-1,10);
            Day = QString::number(28,10);
        }
        else {
            Month = QString::number(Month.toInt()-1,10);
            Day = QString::number(30,10);
        }
    }
    if(Month.length()<2)
        Month.insert(0,"0");
    if(Day.length()<2)
        Day.insert(0,"0");
    Atime.replace(0,8,Year+Month+Day);

}
