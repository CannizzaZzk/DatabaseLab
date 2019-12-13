#include "userreset.h"
#include "ui_userreset.h"
#include <QTime>
#include <QMessageBox>
#include <QSqlField>
#include <QSqlTableModel>
#include <QSqlRecord>

UserReset::UserReset(int *flag, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserReset)
{
    IDflag = flag;
    ui->setupUi(this);
    ui->txtVer->setText(createstring());
    ui->txtVer->setEnabled(false);
    setMinimumSize(345,350);
    setMaximumSize(345,350);
}

QString UserReset::createstring(){
    int maxn= 4;
    QString tmp = QString("0123456789ABCDEFGHIJKLMNOPQRSTUVWZYZ");
    QString str = QString();
    QTime t;
    t= QTime::currentTime();
    qsrand(t.msec()+t.second()*1000);
    for(int i=0;i<maxn;i++) {
         int ir = qrand()%tmp.length();
         str[i] = tmp.at(ir);
    }
    return str;
}

UserReset::~UserReset()
{
    delete ui;
}

int UserReset::judge()
{
    if(ui->txtPass->text().trimmed()!=ui->txtRePass->text().trimmed())
        return 1;
    else if(ui->txtVer->text().trimmed()!=ui->txtReVer->text().trimmed())
        return 2;
    else
        return 0;
}

void UserReset::on_buttonBox_accepted()
{
    int temp = judge();
    if(temp == 0){
        addNewUser();
        this->close();
        QMessageBox::about(NULL, "提示", "修改成功！");
    }
    else if(temp == 1){
        QMessageBox::warning(this,tr("警告"),tr("密码不一致!"),QMessageBox::Yes);
    }
    else if(temp == 2){
        QMessageBox::warning(this,tr("警告"),tr("验证码错误!"),QMessageBox::Yes);
    }
}

void UserReset::addNewUser(){
    QSqlTableModel *comModel = new QSqlTableModel();
    comModel->setTable("user");
    comModel->select();

    comModel->removeRow((*IDflag)-1);
    int id=(*IDflag);
    QString username = ui->txtName->text();
    QString password = ui->txtPass->text();

    QSqlRecord record;
    QSqlField f1("id", QVariant::Int);
    QSqlField f2("username", QVariant::String);
    QSqlField f3("password", QVariant::String);

    f1.setValue(QVariant(id));
    f2.setValue(QVariant(username));
    f3.setValue(QVariant(password));

    record.append(f1);
    record.append(f2);
    record.append(f3);

    comModel->insertRecord(-1, record);
}

void UserReset::on_buttonBox_rejected()
{
    this->close();
}
