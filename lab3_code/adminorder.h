#ifndef ADMINORDER_H
#define ADMINORDER_H

#include <QDialog>
#include <QSqlTableModel>

namespace Ui {
class AdminOrder;
}

class AdminOrder : public QDialog
{
    Q_OBJECT

public:
    explicit AdminOrder(QWidget *parent = 0);
    ~AdminOrder();

private slots:
    void on_BtnClose_clicked();



    void on_BtnRefreah_clicked();

    void on_tableView_clicked(const QModelIndex &index);



private:
    Ui::AdminOrder *ui;

    QSqlTableModel *ticketModel;

    void createLeftLayout();

};

#endif // ADMINORDER_H
