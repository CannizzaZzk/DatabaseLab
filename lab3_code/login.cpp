#include "login.h"
#include "ui_login.h"
#include "register.h"
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>

Login::Login(int *flag, int *id,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    idRcd = id;
    ret = flag;
    ui->setupUi(this);
    ui->txtPass->setEchoMode(QLineEdit::Password);
    setWindowTitle("登陆");
    setMaximumSize(415,350);
    setMinimumSize(415,350);
}

Login::~Login()
{
    delete ui;
}

bool Login::judge(){
    QSqlQuery query;
    query.exec(QString("select UPASS,UID from USERS where UNAME='%1' ").arg(this->ui->txtName->text()));
    query.next();
    if(query.value(0).toString().trimmed()==this->ui->txtPass->text()){
        *idRcd = query.value(1).toInt();
        qDebug()<<"true"<<endl;
        return true;
    }
    else
    {
      qDebug()<<query.value(0)<<endl;
      qDebug()<<"false"<<endl;
      return false;
    }
}

int Login::decideType(){
    QSqlQuery query;
    query.exec(QString("select UTYPE from USERS where UNAME='%1' ").arg(this->ui->txtName->text()));
    query.next();
    qDebug()<<"blank test:  "<<query.value(0).toInt()<<endl;
    return query.value(0).toInt();
}

void Login::on_BtnLogin_clicked()
{
    if(judge())
    {
        *ret = decideType();
        if(*ret == 0)
           {

            QMessageBox::warning(this,tr("警告"),tr("用户名或密码不能为空!"),QMessageBox::Yes);
            this->ui->txtName->clear();
            this->ui->txtPass->clear();
            this->ui->txtName->setFocus();

        }

       if(*ret != 0)
        this->close();
    }
    else
    {
        QMessageBox::warning(this,tr("警告"),tr("用户名或密码错误!"),QMessageBox::Yes);
        this->ui->txtName->clear();
        this->ui->txtPass->clear();
        this->ui->txtName->setFocus();
    }
}

void Login::on_BtnRegister_clicked()
{
    int flag = 0;
    Register re(&flag);
    re.show();
    re.exec();
}

void Login::on_txtName_returnPressed()
{
    on_BtnLogin_clicked();
}

void Login::on_txtPass_returnPressed()
{
    on_BtnLogin_clicked();
}
