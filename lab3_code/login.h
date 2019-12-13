#ifndef LOGIN_H
#define LOGIN_H
#include <QDebug>
#include <QDialog>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(int *flag,int *id,QWidget *parent = 0);
    ~Login();

private slots:
    void on_BtnLogin_clicked();

    void on_BtnRegister_clicked();

    void on_txtPass_returnPressed();

    void on_txtName_returnPressed();

private:
    Ui::Login *ui;

    int *ret;
    int *idRcd;
    bool judge();
    int findmark();
    int decideType();
};

#endif // LOGIN_H
