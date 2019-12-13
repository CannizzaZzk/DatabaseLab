#ifndef USERBILL_H
#define USERBILL_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlQuery>
#include <QTableView>
#include <QStandardItemModel>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QDebug>


namespace Ui {
class userBill;
}

class userBill : public QDialog
{
    Q_OBJECT

public:
    explicit userBill(int uid,QWidget *parent = nullptr);
    ~userBill();

private slots:
    void on_OFLbtn_clicked();

    void on_OLbtn_clicked();

    void on_quitbtn_clicked();

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::userBill *ui;
    int UidNow;
    QSqlTableModel *BILLModel;
    QSqlRecord billRecord;
    QStandardItemModel * item_model;

    void createLeftLayout();
};

#endif // USERBILL_H
