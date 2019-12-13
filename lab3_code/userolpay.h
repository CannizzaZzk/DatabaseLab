#ifndef USEROLPAY_H
#define USEROLPAY_H

#include <QDialog>
#include <QDialog>
#include <QMessageBox>
#include <QSqlQuery>
#include <QTableView>
#include <QStandardItemModel>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QDebug>

namespace Ui {
class userOLPay;
}

class userOLPay : public QDialog
{
    Q_OBJECT

public:
    explicit userOLPay(int uid,int tid,QString fid,QWidget *parent = nullptr);
    ~userOLPay();

private slots:
    void on_pushButton_2_clicked();

    void on_quitbtn_clicked();

private:
    Ui::userOLPay *ui;
    QString FlightId;
    int UidNow;
    int tid;
};

#endif // USEROLPAY_H
