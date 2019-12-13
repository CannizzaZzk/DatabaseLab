#ifndef AdminFlight_H
#define ADMINFLIGHT_H

#include <QDialog>
#include <QSqlTableModel>

namespace Ui {
class AdminFlight;
}

class AdminFlight : public QDialog
{
    Q_OBJECT

public:
    explicit AdminFlight(QWidget *parent = 0);
    ~AdminFlight();

private slots:
    void on_BtnClose_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_txtSearch_returnPressed();

    void on_BtnRefreah_clicked();

    void on_BtnDelete_clicked();

    void on_BtnAdd_clicked();

private:
    Ui::AdminFlight *ui;
    QSqlTableModel *comModel;

    void createLeftLayout();
    void searchFid();
    void searchStart();
    void searchEnd();
};

#endif
