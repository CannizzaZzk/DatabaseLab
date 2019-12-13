#include "addproduct.h"
#include "ui_addproduct.h"
#include <QSqlRecord>
#include <QSqlField>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QMessageBox>
#include <QtDebug>
#include <QTime>
#include <QDateTime>

AddProduct::AddProduct(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddProduct)
{
    ui->setupUi(this);
    setWindowTitle("新增航班");
}

AddProduct::~AddProduct()
{
    delete ui;
}

void AddProduct::on_buttonBox_accepted()
{
    QString Fid = ui->txtFID->text();
    QString Start = ui->txtStart->text();
    QString End = ui->txtEnd->text();
    QString Location = ui->txtLocation->text();
    QString Year = ui->txtYear->text();
    QString Month = ui->txtMonth->text();
    QString Day = ui->txtDay->text();
    QString Hour = ui->txtHour->text();
    QString Minute = ui->txtMinute->text();


    //确保时间字段是12位的数字串
    if(Month.toInt()<10 && Month.at(0)!= '0')
          Month.insert(0,"0");
    if(Day.toInt()<10 && Day.at(0)!= '0')
          Day.insert(0,"0");
    if(Hour.toInt()<10 && Hour.at(0)!= '0')
          Hour.insert(0,"0");
    if(Minute.toInt()<10 && Minute.at(0)!= '0')
          Minute.insert(0,"0");


    //确保时间值合法
    while(Month.toInt()>12||Day.toInt()>31||Hour.toInt()>23||Minute.toInt()>59)
    {
        QMessageBox::warning(this,tr("警告"),tr("起飞时间无效!"),QMessageBox::Yes);
        this->ui->txtYear->clear();
        this->ui->txtMonth->clear();
        this->ui->txtDay->clear();
        this->ui->txtHour->clear();
        this->ui->txtMinute->clear();
        this->ui->txtYear->setFocus();
        return ;
    }

    QString hm = QTime().currentTime().toString("hhmm");
    QString ymd = QDateTime().currentDateTime().toString("yyyyMMdd");
    QString Ymd = Year + Month + Day;
    QString Hm = Hour + Minute;
    qDebug()<<"Year: "<<Year<<"Month： "<<Month<<"Day： "<<Day;
    qDebug()<<"Ymd == "<<Ymd<<endl;
    qDebug()<<"ymd == "<<ymd<<endl;
    while(Ymd.toInt() - ymd.toInt() <= 0)
    {
        QMessageBox::warning(this,tr("警告"),tr("起飞时间无效!"),QMessageBox::Yes);
        this->ui->txtYear->clear();
        this->ui->txtMonth->clear();
        this->ui->txtDay->clear();
        this->ui->txtHour->clear();
        this->ui->txtMinute->clear();
        this->ui->txtYear->setFocus();
        return ;
   }
    while(Ymd.toInt() - ymd.toInt() == 1 && Hm.toInt() <= hm.toInt())
    {
        QMessageBox::warning(this,tr("警告"),tr("需要提前24小时安排航班!"),QMessageBox::Yes);
        this->ui->txtYear->clear();
        this->ui->txtMonth->clear();
        this->ui->txtDay->clear();
        this->ui->txtHour->clear();
        this->ui->txtMinute->clear();
        this->ui->txtYear->setFocus();
        return ;
   }



    QString Time = Year.append(Month).append(Day).append(Hour).append(Minute);

    QSqlRecord record;
    QSqlField f1("FID", QVariant::Int);
    QSqlField f2("FSTART", QVariant::String);
    QSqlField f3("FEND", QVariant::String);
    QSqlField f4("FTIME", QVariant::String);
    QSqlField f5("FLOCATION", QVariant::Int);


    f1.setValue(QVariant(Fid));
    f2.setValue(QVariant(Start));
    f3.setValue(QVariant(End));
    f4.setValue(QVariant(Time));
    f5.setValue(QVariant(Location));


    record.append(f1);
    record.append(f2);
    record.append(f3);
    record.append(f4);
    record.append(f5);


    QSqlTableModel *comModel = new QSqlTableModel(this);
    comModel->setTable("FLIGHTS");
    comModel->select();
    if(!comModel->insertRecord(-1, record)){
        QMessageBox::warning(this,tr("警告"),tr("添加失败!"),QMessageBox::Yes);
    }
    comModel->setSort(0, Qt::AscendingOrder);//设置升序排列
    comModel->select();

    //在SEAT表中添加座位
    int Raw = ui->txtRaw->text().toInt();
    int Column = ui->txtColumn->text().toInt();
    int HStart = ui->txtRawHeadS->text().toInt();
    int HEnd = ui->txtRawHeadE->text().toInt();
    int HPrice = ui->txtHeadPrice->text().toInt();
    int NPrice = ui->txtEcoPrice->text().toInt();

    if(!(HStart>0&&HEnd<Raw))
    {
       QMessageBox::warning(this,tr("警告"),tr("无效的头等舱范围!"),QMessageBox::Yes);

    }

    char temp;
    QString clm;

    QSqlQuery query;
    for(int i = 1;i <= Raw; i++ ){
        for (int j = 1;j <= Column;j++) {
            //将列号转换为字母
            temp = j + 64;
            clm = QString(temp);
            if(i <= HEnd && i >= HStart)
                query.exec(QString("insert into SEAT values(%1,'%2',1,NULL,'%3',NULL,%4,1) ").arg(i,0,10).arg(clm).arg(Fid).arg(HPrice,0,10));
            else
                query.exec(QString("insert into SEAT values(%1,'%2',1,NULL,'%3',NULL,%4,0) ").arg(i,0,10).arg(clm).arg(Fid).arg(NPrice,0,10));
         }
     }

}
