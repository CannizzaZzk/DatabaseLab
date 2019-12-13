#ifndef DATACONNECT_H
#define DATACONNECT_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QApplication>
#include<QSql>
#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include<QSqlError>
#include<QSqlDatabase>
#include<QSqlQuery>

class DataConnect
{
public:
    DataConnect();

    void createDB();//建立数据库
    void initTable();//初始化建立数据表
    bool connectDB();//连接数据库
};

#endif // DATACONNECT_H
