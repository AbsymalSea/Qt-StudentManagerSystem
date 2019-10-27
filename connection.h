#ifndef CONNECTION_H
#define CONNECTION_H

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>

/********************************************
 ** 名称：连接数据库函数
 ** 功能：连接数据库创建student 表并赋缺省值
 ** 信号：---
 ** 参数：---
 *********************************************/
static bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName("localhost");
    db.setDatabaseName("mydata");
    db.setUserName("root");
    db.setPassword("root");

    if (!db.open())
    {
        QMessageBox::critical(0, QObject::tr("无法打开数据库"),
            "无法创建数据库连接！", QMessageBox::Cancel);
        return false;
    }

    // 下面的代码用来创建表
    // 如果MySQL 数据库中已经存在同名的表,那么下面的代码不会执行
    QSqlQuery query(db);

    // 使数据库支持中文
    query.exec("SET NAMES 'Latin1'");

    // 创建password 表
    query.exec("create table password(id varchar(20) primary key, pwd varchar(50))");
    query.exec("insert into password values('01', '123456')");

    // 创建student 表
    query.exec("create table student (id varchar(10) primary key, "
                            "name varchar(10), sexual varchar(10), "
                            "address varchar(20), phoneNumber varchar(20), "
                            "ChineseScore double, mathScore double, EnglishScore double, "
                            "averageScore double, testRank int, moralScore double, "
                            "teacherScore double, mateScore double, comboScore double, "
                            "comboRank int)");
    // 填充缺省值
    query.exec("insert into student values('10001',"
                            "'小明', '男',"
                            "'江西省南昌市青山湖区', '199-1000-2000',"
                            "80, 90, 90,"
                            "0, 0, 96,"
                            "90, 98, 6211,"
                            "1)");
    query.exec("insert into student values('10002',"
                            "'小红', '女',"
                            "'江西省南昌市青山湖区', '199-1001-2000',"
                            "80, 80, 70,"
                            "0, 0, 96,"
                            "90, 98, 6211,"
                            "2)");
    query.exec("insert into student values('10003',"
                            "'小黑', '男',"
                            "'江西省南昌市青山湖区', '199-1002-2000',"
                            "70, 90, 90,"
                            "0, 00, 96,"
                            "90, 9, 6211,"
                            "3)");

    return true;
}

#endif // CONNECTION_H
