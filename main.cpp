#include "mainwindow.h"
#include "connection.h"
#include "logindialog.h"
#include <QApplication>
#include <QProcess>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 这里使用代码来运行MySQL 数据库
    QProcess process;
    process.start("C:/MySQL/bin/mysqld.exe");

    // 连接数据库失败
    if(!createConnection())
        return 0;

    MainWindow w;
    LoginDialog dlg;
    if (dlg.exec() == QDialog::Accepted)
    {
        w.show();
        return a.exec();
    }
    else
    {
        return 0;
    }
}
