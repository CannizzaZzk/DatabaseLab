#include "adminorder.h"
#include "ui_adminorder.h"
#include <QSqlRecord>
#include <QSqlField>
#include <QMessageBox>
#include <QtDebug>

AdminOrder::AdminOrder(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminOrder)
{
    ui->setupUi(this);
    resize(1200,700);
    ticketModel = new QSqlTableModel(this);
    ticketModel->setTable("TICKETS");
    ticketModel->select();
    ticketModel->setHeaderData(0, Qt::Horizontal, tr("机票编号"));
    ticketModel->setHeaderData(1, Qt::Horizontal, tr("航班号"));
    ticketModel->setHeaderData(2, Qt::Horizontal, tr("用户ID"));
    ticketModel->setHeaderData(3, Qt::Horizontal, tr("票价"));
    ticketModel->setHeaderData(4, Qt::Horizontal, tr("支付状态"));


    setWindowTitle("订单管理");
    createLeftLayout();
}

void AdminOrder::createLeftLayout()
{
    ui->tableView->setSortingEnabled(true);//开启排序
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置为不可编辑状态
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);//每次选择一行
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);//单机选择
    ui->tableView->setShowGrid(true);
    ui->tableView->setAlternatingRowColors(true);

    ui->tableView->setModel(ticketModel);
    ui->tableView->verticalHeader()->setVisible(false);


}

AdminOrder::~AdminOrder()
{
    delete ui;
}

void AdminOrder::on_BtnClose_clicked()
{
    this->close();
}




void AdminOrder::on_BtnRefreah_clicked()
{

    ticketModel->setTable("TICKETS");
    ticketModel->setSort(0, Qt::AscendingOrder);
    ticketModel->setHeaderData(0, Qt::Horizontal, tr("机票编号"));
    ticketModel->setHeaderData(1, Qt::Horizontal, tr("航班号"));
    ticketModel->setHeaderData(2, Qt::Horizontal, tr("用户ID"));
    ticketModel->setHeaderData(3, Qt::Horizontal, tr("票价"));
    ticketModel->setHeaderData(4, Qt::Horizontal, tr("支付状态"));
    ticketModel->select();
}

void AdminOrder::on_tableView_clicked(const QModelIndex &index)
{
    ui->txtMessage->clear();
    //获取选中行数据表中的数据并分离出来
    QSqlRecord record = ticketModel->record(index.row());
    int userId = record.value("UID").toInt();
    int TicketId = record.value("TID").toInt();
    int price = record.value("TPRICE").toInt();
    int state = record.value("TSTATE").toInt();
    QString flight = record.value("FID").toString();
    QString State;
    if(state == 0)
        State = "未付款";
    else
        State = "已付款";


    ui->txtMessage->setText(tr("购票用户ID: %1\n航班号: %2\n机票编号: %3\n票价: %4\n付款状态: %5\n")
                  .arg(userId).arg(flight).arg(TicketId).arg(price).arg(State));
}
