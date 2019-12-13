#ifndef USERFLIGHT_H
#define USERFLIGHT_H

#include <QDialog>
#include <QSqlTableModel>
#include <QLineEdit>

namespace Ui {
class UserFlight;
}

class UserFlight : public QDialog
{
    Q_OBJECT

public:
    explicit UserFlight(int *flag,int id, QWidget *parent = 0);
    ~UserFlight();

private slots:
    void on_BtnClose_clicked();

    void on_BtnRefreah_clicked();
    void on_BtnSearch_clicked();
    void on_BtnBuy_clicked();




private:
    Ui::UserFlight *ui;
    QSqlTableModel *FltModel;
    QSqlTableModel *shopModel;


    void createLeftLayout();


    int *IDflag;
    int idNow;
    int UcomId;
    QString Ucategory;
    QString Uname;
    QString Uorigin;
    int Ucount;
    double Uprice;
    QString Uquality;
    QString Uexp;

    QLineEdit *seLineEdit;
    QLineEdit *se1LineEdit;
    QLineEdit *idLineEdit;
    QLineEdit *categoryLineEdit;
    QLineEdit *nameLineEdit;
    QLineEdit *originLineEdit;
    QLineEdit *countLineEdit;
    QLineEdit *priceLineEdit;
    QLineEdit *qualityLineEdit;
    QLineEdit *expLineEdit;
};

#endif // USERFLIGHT_H
