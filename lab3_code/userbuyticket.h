#ifndef USERBUYTICKET_H
#define USERBUYTICKET_H

#include <QDialog>
#include <QSqlQuery>
#include <QTableView>
#include <QStandardItemModel>
#include <QSqlTableModel>
#include <QSqlRecord>

namespace Ui {
class UserBuyTicket;
}

class UserBuyTicket : public QDialog
{
    Q_OBJECT

public:
    explicit UserBuyTicket(QString fid,int uid,QWidget *parent = nullptr);
    ~UserBuyTicket();

private slots:
    void on_pushButton_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::UserBuyTicket *ui;
    void createLeftLayout();
    QSqlTableModel *SEATModel;
    QSqlRecord seatRecord;
    void TimeOp(QString &Atime);

    QString  FlightId;
    int UidNow;
    QStandardItemModel * item_model;
};

#endif // USERBUYTICKET_H
