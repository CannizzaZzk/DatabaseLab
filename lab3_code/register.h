#ifndef REGISTER_H
#define REGISTER_H

#include <QDialog>
#include <string>

namespace Ui {
class Register;
}

class Register : public QDialog
{
    Q_OBJECT

public:
    explicit Register(int *flag,QWidget *parent = 0);
    ~Register();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Register *ui;
    int *type;
    int judge();
    QString createstring();//生成随机的验证码
    void addNewUser();//新用户添加至数据库
    void addNewAdmin();
};

#endif // REGISTER_H
