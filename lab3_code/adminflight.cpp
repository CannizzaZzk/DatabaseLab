#include "adminflight.h"
#include "ui_adminflight.h"
#include "addproduct.h"
#include <QSqlRecord>
#include <QModelIndexList>
#include <QMessageBox>
#include <QSqlQuery>


AdminFlight::AdminFlight(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminFlight)
{
    ui->setupUi(this);
    resize(1200,700);

    comModel = new QSqlTableModel(this);
    comModel->setTable("FLIGHTS");
    comModel->select();

    comModel->setHeaderData(0, Qt::Horizontal, tr("航班号"));
    comModel->setHeaderData(1, Qt::Horizontal, tr("出发"));
    comModel->setHeaderData(2, Qt::Horizontal, tr("目的地"));
    comModel->setHeaderData(3, Qt::Horizontal, tr("起飞时间"));
    comModel->setHeaderData(4, Qt::Horizontal, tr("登机口"));

    setWindowTitle("航班管理");
    createLeftLayout();
}

void AdminFlight::createLeftLayout()
{
    ui->tableView->setSortingEnabled(true);//开启排序
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);//每次选择一行
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);//单机选择
    ui->tableView->setShowGrid(true);
    ui->tableView->setAlternatingRowColors(true);
    ui->tableView->verticalHeader()->setVisible(false);
    comModel->setHeaderData(0, Qt::Horizontal, tr("航班号"));
    comModel->setHeaderData(1, Qt::Horizontal, tr("出发"));
    comModel->setHeaderData(2, Qt::Horizontal, tr("目的地"));
    comModel->setHeaderData(3, Qt::Horizontal, tr("起飞时间"));
    comModel->setHeaderData(4, Qt::Horizontal, tr("登机口"));
    ui->tableView->setModel(comModel);
}

AdminFlight::~AdminFlight()
{
    delete ui;
}

void AdminFlight::on_BtnClose_clicked()
{
    this->close();
}

void AdminFlight::on_tableView_clicked(const QModelIndex &index)
{
    ui->txtMessage->clear();
    //获取选中行数据表中的数据并分离出来
    QSqlRecord record = comModel->record(index.row());
    QString Fid = record.value("FID").toString();
    QString Start = record.value("FSTART").toString();
    QString End = record.value("FEND").toString();
    QString Time = record.value("FTIME").toString();
    QString Location = record.value("FLOCATION").toString();
    QString year,month,day,hour,minute;
    year = Time.mid(0,4);
    month = Time.mid(4,2);
    day = Time.mid(6,2);
    hour = Time.mid(8,2);
    minute = Time.mid(10,2);
    Time = " ";
    Time.append(year).append("年 ").append(month).append("月 ").append(day).append("日 ");
    Time.append(hour).append("时 ").append(minute).append("分 ");
    QSqlQuery seat;
    seat.exec(QString("select count(*) from SEAT where FID = '%1';").arg(Fid));
    seat.next();
    int Fm,Fz;
    Fm = seat.value(0).toInt();
    seat.exec(QString("select count(*) from SEAT where FID = '%1' and SVALID = 0;").arg(Fid));
    seat.next();
    Fz = seat.value(0).toInt();

    ui->txtMessage->setText(tr("航班号: %1\n出发地: %2\n目的地: %3\n起飞时间:%4\n登机口: %5\n航班满座率: %6/%7\n")
                  .arg(Fid).arg(Start).arg(End).arg(Time).arg(Location).arg(Fz,0,10).arg(Fm,0,10));
}

void AdminFlight::on_txtSearch_returnPressed()
{
    switch(ui->comSearch->currentIndex())
    {
    case 0:
        searchFid();
        break;
    case 1:
        searchStart();
        break;
    case 2:
        searchEnd();
        break;
    }
}


void AdminFlight::searchFid()
{
    QString Fid = ui->txtSearch->text();
    if(!Fid.isEmpty())
    {
        comModel->setFilter(QObject::tr("FID = '%1'").arg(Fid));
        comModel->select();
    }
    else
        return;
}


void AdminFlight::searchStart()
{
    QString Start = ui->txtSearch->text();
    if(!Start.isEmpty())
    {
        comModel->setFilter(QObject::tr("FSTART = '%1'").arg(Start));
        comModel->select();
    }
    else
        return;
}


void AdminFlight::searchEnd()
{
    QString End = ui->txtSearch->text();
    if(!End.isEmpty())
    {
        comModel->setFilter(QObject::tr("FEND = '%1'").arg(End));
        comModel->select();
    }
    else
        return;
}

//刷新列表
void AdminFlight::on_BtnRefreah_clicked()
{

    comModel->setTable("FLIGHTS");
    comModel->setSort(0, Qt::AscendingOrder);
    comModel->setHeaderData(0, Qt::Horizontal, tr("航班号"));
    comModel->setHeaderData(1, Qt::Horizontal, tr("出发"));
    comModel->setHeaderData(2, Qt::Horizontal, tr("目的地"));
    comModel->setHeaderData(3, Qt::Horizontal, tr("起飞时间"));
    comModel->setHeaderData(4, Qt::Horizontal, tr("登机口"));
    comModel->select();
}

//删除航班
void AdminFlight::on_BtnDelete_clicked()
{
    QModelIndexList select = ui->tableView->selectionModel()->selectedRows();
    QSqlQuery query;
    if(!select.empty())
    {
        QModelIndex idIndex = select.at(0);//得到选中行的id索引
        QString fid = idIndex.sibling(idIndex.row(), 0).data().toString();
        QMessageBox::StandardButton button;
        button = QMessageBox::question(this, tr("删除"), QString(tr("你确定删除 '%1' 吗?").arg(fid.trimmed())), QMessageBox::Yes|QMessageBox::No);
        if(button == QMessageBox::Yes)
        {
            query.exec(QString("delete from SEAT where FID = '%1'").arg(fid));
            query.exec(QString("delete from TICKETS where FID = '%1'").arg(fid));
            comModel->removeRow(idIndex.row());
            comModel->submitAll();
            comModel->select();
        }
    }
}

void AdminFlight::on_BtnAdd_clicked()
{
    AddProduct ap;
    ap.show();
    ap.exec();
    on_BtnRefreah_clicked();
}
