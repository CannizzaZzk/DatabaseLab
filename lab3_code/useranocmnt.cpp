#include "useranocmnt.h"
#include "ui_useranocmnt.h"

userAnocmnt::userAnocmnt(int uid,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::userAnocmnt)
{
    ui->setupUi(this);
    UidNow = uid;
    setWindowTitle("机票购买");
    setMinimumSize(550,500);
    setMaximumSize(550,500);
    createLeftLayout();
}

userAnocmnt::~userAnocmnt()
{
    delete ui;
}
void userAnocmnt::createLeftLayout()
{
    ui->tableView->setSortingEnabled(true);//开启排序
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);//每次选择一行
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);//单机选择
    ui->tableView->setShowGrid(true);
    ui->tableView->setAlternatingRowColors(true);
    ui->tableView->verticalHeader()->setVisible(false);

    ANMTModel = new QSqlTableModel(this);
    ANMTModel->setTable("ANOUNCEMENT");
    ANMTModel->setFilter(QObject::tr("UID = %1").arg(UidNow));
    ANMTModel->select();


    //qDebug()<<"测试："<<endl;
    //列出机票数据
    QStringList title;
    title<<"航班"<<"出发"<<"目的地"<<"支付状态";
    QSqlQuery query;
    QSqlQuery flight;
    query.exec(QString("select count(*) from ANOUNCEMENT where UID = %1; ").arg(UidNow));
    query.next();
    int numRaw = query.value(0).toInt();
    item_model = new QStandardItemModel(numRaw,4);
    QString FlightId;
    QString FStart;
    QString FEnd;
    QString STATE;
    QString TimeNow;
    QString ATime;
    int tid;
    int count = 0;
    query.exec(QString("select * from ANOUNCEMENT where UID = %1; ").arg(UidNow));
    while(query.next())
    {

        TimeNow = QDateTime().currentDateTime().toString("yyyyMMdd");
        ATime = query.value(3).toString().mid(0,8);
        if(TimeNow.toInt() >= ATime.toInt())
        {
            //qDebug()<<Price<<endl;
            //item_model->setItem(count,0,new QStandardItem(FlightId));
            //item_model->setItem(count,1,new QStandardItem(FStart));
            //item_model->setItem(count,2,new QStandardItem(FEnd));
            //item_model->setItem(count,3,new QStandardItem(STATE));

            count++;
        }

    }
    numRaw = count;
    count = 0;
    item_model = new QStandardItemModel(numRaw,4);
    item_model->setHorizontalHeaderLabels(title);
    query.exec(QString("select * from ANOUNCEMENT where UID = %1; ").arg(UidNow));
    while(query.next())
    {
        tid = query.value(0).toInt();
        FlightId = query.value(1).toString();
        if(query.value(4).toInt())
            STATE = "已支付";
        else
            STATE = "未支付";
        flight.exec(QString("select * from FLIGHTS where FID = '%1';").arg(FlightId));
        flight.next();
        FStart = flight.value(1).toString();
        FEnd = flight.value(2).toString();

        TimeNow = QDateTime().currentDateTime().toString("yyyyMMdd");
        ATime = query.value(3).toString().mid(0,8);
        if(TimeNow.toInt() >= ATime.toInt())
        {
            //qDebug()<<Price<<endl;
            item_model->setItem(count,0,new QStandardItem(FlightId));
            item_model->setItem(count,1,new QStandardItem(FStart));
            item_model->setItem(count,2,new QStandardItem(FEnd));
            item_model->setItem(count,3,new QStandardItem(STATE));

            count++;
        }
    }



    ui->tableView->setModel(item_model);


}

void userAnocmnt::on_dlbtn_clicked()
{
    QMessageBox::about(NULL, "正在打印", "请凭取票通知到指定地点缴费并取票！");
}

void userAnocmnt::on_refreshbtn_clicked()
{
    createLeftLayout();
}

void userAnocmnt::on_quitbtn_clicked()
{
    this->close();
}

void userAnocmnt::on_tableView_clicked(const QModelIndex &index)
{

}
