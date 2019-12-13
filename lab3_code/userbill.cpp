#include "userbill.h"
#include "ui_userbill.h"
#include "userolpay.h"

userBill::userBill(int uid,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::userBill)
{
    ui->setupUi(this);
    UidNow = uid;
    setWindowTitle("账单");
    setMinimumSize(750,500);
    setMaximumSize(750,500);
    createLeftLayout();
}

userBill::~userBill()
{
    delete ui;
}

void userBill::createLeftLayout()
{
    ui->tableView->setSortingEnabled(true);//开启排序
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);//每次选择一行
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);//单机选择
    ui->tableView->setShowGrid(true);
    ui->tableView->setAlternatingRowColors(true);
    ui->tableView->verticalHeader()->setVisible(false);

    BILLModel = new QSqlTableModel(this);
    BILLModel->setTable("BILL");
    BILLModel->setFilter(QObject::tr("UID = %1").arg(UidNow));
    BILLModel->select();


    //qDebug()<<"测试："<<endl;
    //列出机票数据
    QStringList title;
    title<<"航班"<<"出发"<<"目的地"<<"座位"<<"应付";
    QSqlQuery query;
    QSqlQuery flight;
    QSqlQuery seat;
    query.exec(QString("select count(*) from BILL where UID = %1; ").arg(UidNow));
    query.next();
    int numRaw = query.value(0).toInt();
    item_model = new QStandardItemModel(numRaw,5);
    QString FlightId;
    QString FStart;
    QString FEnd;
    QString SeatNum;
    QString Price;
    int tid;
    int count = 0;
    item_model->setHorizontalHeaderLabels(title);
    query.exec(QString("select * from BILL where UID = %1; ").arg(UidNow));
    while(query.next())
    {
        tid = query.value(0).toInt();
        FlightId = query.value(1).toString();
        Price = query.value(3).toString();
        flight.exec(QString("select * from FLIGHTS where FID = '%1';").arg(FlightId));
        flight.next();
        FStart = flight.value(1).toString();
        FEnd = flight.value(2).toString();
        seat.exec(QString("select SRAW,SCOLUMN from SEAT where FID = '%1' and TID = %2;").arg(FlightId).arg(tid,0,10));
        seat.next();
        SeatNum = seat.value(0).toString() + seat.value(1).toString();


        //qDebug()<<Price<<endl;
        item_model->setItem(count,0,new QStandardItem(FlightId));
        item_model->setItem(count,1,new QStandardItem(FStart));
        item_model->setItem(count,2,new QStandardItem(FEnd));
        item_model->setItem(count,3,new QStandardItem(SeatNum));
        item_model->setItem(count,4,new QStandardItem(Price));
        count++;
    }


    ui->tableView->setModel(item_model);


}

void userBill::on_OFLbtn_clicked()
{
    QMessageBox::about(NULL, "正在打印", "请凭取票通知到指定地点缴费并取票！");
}

void userBill::on_OLbtn_clicked()
{
    //解析选中数据
    QString FlightID = billRecord.value("FID").toString();
    int tid = billRecord.value("TID").toInt();

    userOLPay OLpay(UidNow,tid,FlightID);
    OLpay.show();
    OLpay.exec();

    createLeftLayout();
}

void userBill::on_quitbtn_clicked()
{
    this->close();
}

void userBill::on_tableView_clicked(const QModelIndex &index)
{
    QSqlRecord record = BILLModel->record(index.row());
    billRecord = record;
}
