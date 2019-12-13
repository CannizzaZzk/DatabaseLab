#include "register.h"
#include "ui_register.h"
#include <QTime>
#include <QSqlRecord>
#include <QSqlField>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QDebug>
#include <QSqlDatabase>

Register::Register(int *flag,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Register)
{
    type = flag;
    qDebug()<<"权限测试： "<<*type<<endl;
    ui->setupUi(this);
    ui->txtVer->setText(createstring());
    ui->txtVer->setEnabled(false);
    setWindowTitle("注册");
    setMinimumSize(345,350);
    setMaximumSize(345,350);
}

Register::~Register()
{
    delete ui;
}

int Register::judge(){
   /*信息未填写
   */
   if(ui->txtPass->text().trimmed()!=ui->txtRePass->text().trimmed())
   {


           return 1;

   }
   else if(ui->txtVer->text().trimmed()!=ui->txtReVer->text().trimmed())
       return 2;
   else if (*type == 1)
       return 3;
   else
       return 0;
}

QString Register::createstring(){
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

void Register::on_buttonBox_accepted()
{
    int temp = judge();
    qDebug()<<"权限测试： temp= "<<temp<<endl;
    if(temp == 0){
        addNewUser();
        this->close();

    }
    else if(temp == 3){
        addNewAdmin();
        this->close();

    }
    else if(temp == 1){
        QMessageBox::warning(this,tr("警告"),tr("密码不一致!"),QMessageBox::Yes);
    }
    else if(temp == 2){
        QMessageBox::warning(this,tr("警告"),tr("验证码错误!"),QMessageBox::Yes);
    }
}

void Register::addNewUser(){


    QSqlQuery query;
    query.exec(QString("select * from USERS order by UID DESC"));
    query.next();
    qDebug()<<"test: "<<query.value(0).toInt() <<query.value(1).toString() <<query.value(2).toString();

    int uid = query.value(0).toInt() + 1;
    QString username = ui->txtName->text();
    QString password = ui->txtPass->text();
    query.exec(QString("select count(*) from USERS where UNAME = '%1';").arg(username.trimmed()));
    query.next();
    qDebug()<<"重名测试： "<<query.value(0).toInt()<<endl;
    if(query.value(0).toInt())
    {
        QMessageBox::warning(this,tr("警告"),tr("用户名已存在!"),QMessageBox::Yes);
        return;
    }
    query.exec(QString("insert into USERS values('%1','%2','%3',2)").arg(uid,0,10).arg(username.trimmed(),password.trimmed()));
     QMessageBox::about(NULL, "提示", "注册成功！");

    //======================================================================

}

void Register::addNewAdmin(){


    QSqlQuery query;
    query.exec(QString("select * from USERS order by UID DESC"));
    query.next();


    int uid = query.value(0).toInt() + 1;
    QString username = ui->txtName->text();
    QString password = ui->txtPass->text();
    query.exec(QString("select count(*) from USERS where UNAME = '%1';").arg(username.trimmed()));
    query.next();
    if(query.value(0).toInt())
    {
        QMessageBox::warning(this,tr("警告"),tr("用户名已存在!"),QMessageBox::Yes);
        return;
    }
    query.exec(QString("insert into USERS values('%1','%2','%3',1)").arg(uid,0,10).arg(username.trimmed(),password.trimmed()));

    QMessageBox::about(NULL, "提示", "注册成功！");
    //======================================================================

}
