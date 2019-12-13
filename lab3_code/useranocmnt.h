#ifndef USERANOCMNT_H
#define USERANOCMNT_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlQuery>
#include <QTableView>
#include <QStandardItemModel>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QDebug>
#include <QDateTime>

namespace Ui {
class userAnocmnt;
}

class userAnocmnt : public QDialog
{
    Q_OBJECT

public:
    explicit userAnocmnt(int uid,QWidget *parent = nullptr);
    ~userAnocmnt();

private slots:
    void on_dlbtn_clicked();

    void on_refreshbtn_clicked();

    void on_quitbtn_clicked();

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::userAnocmnt *ui;
    int UidNow;
    QSqlTableModel *ANMTModel;
    QSqlRecord anmtRecord;
    QStandardItemModel * item_model;

    void createLeftLayout();
};

#endif // USERANOCMNT_H
