#ifndef USERORDER_H
#define USERORDER_H

#include <QDialog>
#include <QSqlQuery>
#include <QTableView>
#include <QStandardItemModel>
#include <QSqlTableModel>
#include <QSqlRecord>

namespace Ui {
class userOrder;
}

class userOrder : public QDialog
{
    Q_OBJECT

public:
    explicit userOrder(int uid,QWidget *parent = nullptr);
    ~userOrder();

private slots:
    void on_cnlbtn_clicked();

    void on_refreshbtn_clicked();

    void on_quitbtn_clicked();

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::userOrder *ui;
    int idNow;
    QSqlTableModel *TicketModel;
    QSqlRecord ticketRecord;
    QString  FlightId;

    QStandardItemModel * item_model;
    void createLeftLayout();

};

#endif // USERORDER_H
