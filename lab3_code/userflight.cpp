#include "userflight.h"
#include "ui_userflight.h"
#include <QSqlRecord>
#include <QSqlField>
#include <QDialog>
#include <QDialogButtonBox>
#include <QLabel>
#include <QMessageBox>
#include "userbuyticket.h"
#include <QDebug>

UserFlight::UserFlight(int *flag,int id,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserFlight),
    idNow(id)
{
    ui->setupUi(this);
    resize(680,700);

    FltModel = new QSqlTableModel(this);
    FltModel->setTable("FLIGHTS");

    FltModel->select();

    qDebug()<<"uid now is : "<<idNow<<endl;
    setWindowTitle("航班查询");
    createLeftLayout();
    IDflag = flag;
}

void UserFlight::createLeftLayout()
{
    ui->tableView->setSortingEnabled(true);//开启排序
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置为不可编辑状态
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);//每次选择一行
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);//单机选择
    ui->tableView->setShowGrid(true);
    ui->tableView->setAlternatingRowColors(true);
    ui->tableView->verticalHeader()->setVisible(false);


    FltModel->setHeaderData(0, Qt::Horizontal, tr("航班号"));
    FltModel->setHeaderData(1, Qt::Horizontal, tr("出发"));
    FltModel->setHeaderData(2, Qt::Horizontal, tr("目的地"));
    FltModel->setHeaderData(3, Qt::Horizontal, tr("起飞时间"));
    FltModel->setHeaderData(4, Qt::Horizontal, tr("登机口"));


    ui->tableView->setModel(FltModel);
}

UserFlight::~UserFlight()
{
    delete ui;
}

void UserFlight::on_BtnClose_clicked()
{
    this->close();
}

void UserFlight::on_BtnRefreah_clicked()
{
    FltModel->setTable("FLIGHTS");
    FltModel->setSort(0, Qt::AscendingOrder);
    FltModel->setHeaderData(0, Qt::Horizontal, tr("航班号"));
    FltModel->setHeaderData(1, Qt::Horizontal, tr("出发"));
    FltModel->setHeaderData(2, Qt::Horizontal, tr("目的地"));
    FltModel->setHeaderData(3, Qt::Horizontal, tr("起飞时间"));
    FltModel->setHeaderData(4, Qt::Horizontal, tr("登机口"));
    FltModel->select();
}

void UserFlight::on_BtnSearch_clicked()
{
    QString Start = ui->txtStart->text();
    QString End = ui->txtEnd->text();
    if(!Start.isEmpty()&&!End.isEmpty()){
        qDebug()<<Start<<" 测试 "<<End<<endl;
        FltModel->setFilter(QObject::tr("FSTART = '%1'").arg(Start));
        FltModel->setFilter(QObject::tr("FEND = '%1'").arg(End));
        //ui->tableView->setModel(FltModel);
        FltModel->select();
    }

}


void UserFlight::on_BtnBuy_clicked()
{
    QModelIndexList select = ui->tableView->selectionModel()->selectedRows();

    if(!select.empty())
    {
        QModelIndex idIndex = select.at(0);//得到选中行的id索引
        QString start = idIndex.sibling(idIndex.row(), 1).data().toString();
        QString end = idIndex.sibling(idIndex.row(), 2).data().toString();
        QString fid = idIndex.sibling(idIndex.row(), 0).data().toString();
        QMessageBox::StandardButton button;
        button = QMessageBox::question(this, tr("购票"), QString(tr("你确定购买 '%1'至'%2' 的'%3'航班吗?").arg(start.trimmed()).arg(end.trimmed()).arg(fid.trimmed())), QMessageBox::Yes|QMessageBox::No);
        if(button == QMessageBox::Yes)
        {
            int flag;
            UserBuyTicket buyTicket(fid,idNow);
            buyTicket.show();
            buyTicket.exec();

        }
    }
}

