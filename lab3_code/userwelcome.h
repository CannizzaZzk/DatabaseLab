#ifndef USERWELCOME_H
#define USERWELCOME_H

#include <QMainWindow>

namespace Ui {
class UserWelcome;
}

class UserWelcome : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserWelcome(int *flag,int id, QWidget *parent = 0);
    ~UserWelcome();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_billbtn_clicked();

    void on_billbtn_2_clicked();

    void on_billbtn_3_clicked();

private:
    Ui::UserWelcome *ui;

    int *IDflag;
    int idNow;
    void upDate();
    void Delete(QString fid);
};

#endif // USERWELCOME_H
