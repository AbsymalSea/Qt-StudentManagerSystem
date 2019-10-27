#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QDateTime>

/********************************************
 ** 名称：“登录界面” 类——构造函数
 ** 功能：设置登录界面标题、按钮、显示时间
 ** 信号：---
 ** 参数：---
 *********************************************/
LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    // setFixedSize(700, 400);

    // 设置登录界面标题
    setWindowTitle(tr("欢迎进入登录界面"));

    // 设置登录界面按钮图标大小
    ui->loginBtn->setIconSize(QSize(40, 40));
    ui->quitBtn->setIconSize(QSize(40, 40));
    ui->ensureChangePwdBtn->setIconSize(QSize(40, 40));
    ui->undoChangePwdBtn->setIconSize(QSize(40, 40));


    // 设置登录界面按钮图标来源
    ui->loginBtn->setIcon(QIcon(":/myImages/images/exinputBundle.picfaceCom.png"));
    ui->quitBtn->setIcon(QIcon(":/myImages/images/exinputBundle.asciiCom.png"));
    ui->ensureChangePwdBtn->setIcon(QIcon(":/myImages/images/configBundle.configCom.png"));
    ui->undoChangePwdBtn->setIcon(QIcon(":/myImages/images/undoBundle.png"));

    // 设置登录界面显示时间
    ui->timeLabel->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd"));

    // 设置登录界面按钮可用性
    ui->pwdLineEdit->setFocus();
    ui->loginBtn->setEnabled(false);
    ui->ensureChangePwdBtn->setEnabled(false);
    ui->loginBtn->setDefault(true);

}

/********************************************
 ** 名称：“登录界面” 类——析构函数
 ** 功能：析构
 ** 信号：---
 ** 参数：---
 *********************************************/
LoginDialog::~LoginDialog()
{
    delete ui;
}

/********************************************
 ** 名称：“密码输入框” 文本编辑——槽函数
 ** 功能：按下回车登录
 ** 信号：回车
 ** 参数：---
 *********************************************/
void LoginDialog::on_pwdLineEdit_returnPressed()
{
    if (ui->pwdLineEdit->text().isEmpty())
    {
        QMessageBox::information(this, tr("请输入密码"),
                                    tr("请先输入密码再登录！"), QMessageBox::Ok);
        ui->pwdLineEdit->setFocus();
    }
    else
    {
        LoginDialog::on_loginBtn_clicked();
    }
}

/********************************************
 ** 名称：“密码输入框” 文本编辑——槽函数
 ** 功能：没有输入密码时，无法点击登录按钮
 ** 信号：输入文字
 ** 参数：---
 *********************************************/
void LoginDialog::on_pwdLineEdit_textChanged(const QString &str)
{
    if (str == "")
    {
        ui->loginBtn->setEnabled(false);
    }
    else
    {
        ui->loginBtn->setEnabled(true);
    }
}

/********************************************
 ** 名称：“登录” 按钮——槽函数
 ** 功能：比对数据库中密码，如果正确则登录
 ** 信号：单击鼠标左键
 ** 参数：---
 *********************************************/
void LoginDialog::on_loginBtn_clicked()
{
    // 输入密码后，从数据库中获取密码
    QSqlQuery query;
    query.exec("select pwd from password");
    query.next();

    // 如果输入的密码与库中密码相同，进入下一界面
    if (query.value(0).toString() == ui->pwdLineEdit->text())
    {
        QDialog::accept();
    }
    // 登录失败后，清空内容并定位光标到用户名输入框中
    else
    {
        QMessageBox::warning(this, tr("密码错误"),
                                tr("请输入正确的密码再登录！"), QMessageBox::Ok);
        ui->pwdLineEdit->clear();
        ui->pwdLineEdit->setFocus();
    }

}

/********************************************
 ** 名称：“退出” 按钮——槽函数
 ** 功能：退出程序
 ** 信号：单击鼠标左键
 ** 参数：---
 *********************************************/
void LoginDialog::on_quitBtn_clicked()
{
    QDialog::reject();
}

/********************************************
 ** 名称：“显示密码” 按钮——槽函数
 ** 功能：显示登录界面输入的密码
 ** 信号：单击鼠标左键
 ** 参数：---
 *********************************************/
void LoginDialog::on_showPwdBtn_clicked()
{
    if(ui->showPwdBtn->isChecked())
    {
        ui->pwdLineEdit->setEchoMode(QLineEdit::Normal);
    }
    else
    {
        ui->pwdLineEdit->setEchoMode(QLineEdit::Password);
    }

}

/********************************************
 ** 名称：“修改密码” 按钮——槽函数
 ** 功能：进入修改密码界面
 ** 信号：单击鼠标左键
 ** 参数：---
 *********************************************/
void LoginDialog::on_changePwdBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


/********************************************
 ** 名称：“原密码输入框” 文本编辑——槽函数
 ** 功能：没有输入原密码时，无法点击修改按钮
 ** 信号：输入文字
 ** 参数：---
 *********************************************/
void LoginDialog::on_oldPwdLineEdit_textChanged(const QString &str)
{
    if (str == "")
    {
        ui->ensureChangePwdBtn->setEnabled(false);
    }
    else
    {
        ui->ensureChangePwdBtn->setEnabled(true);
    }
}

/********************************************
 ** 名称：“新密码输入框” 文本编辑——槽函数
 ** 功能：没有输入新密码时，无法点击修改按钮
 ** 信号：输入文字
 ** 参数：---
 *********************************************/
void LoginDialog::on_newPwdLineEdit_textChanged(const QString &str)
{
    if (str == "")
    {
        ui->ensureChangePwdBtn->setEnabled(false);

    }
    else
    {
        ui->ensureChangePwdBtn->setEnabled(true);

    }
}

/********************************************
 ** 名称：“修改” 按钮——槽函数
 ** 功能：确认后用新密码替换数据库中密码
 ** 信号：单击鼠标左键
 ** 参数：---
 *********************************************/
void LoginDialog::on_ensureChangePwdBtn_clicked()
{
    if (ui->oldPwdLineEdit->text().isEmpty() ||
        ui->newPwdLineEdit->text().isEmpty())
    {
            QMessageBox::warning(this, tr("警告"), tr("请先将信息填写完整！"),
            QMessageBox::Ok);
    }
    else
    {
        QSqlQuery query;
        query.exec("select pwd from password");
        query.next();
        if (query.value(0).toString() == ui->oldPwdLineEdit->text())
        {
            bool temp = query.exec(QString("update password set pwd='%1' where id='01'")
                                    .arg(ui->newPwdLineEdit->text()));
            if (temp)
            {
                QMessageBox::information(this, tr("提示"), tr("密码修改成功！"),
                QMessageBox::Ok);
                ui->oldPwdLineEdit->clear();
                ui->newPwdLineEdit->clear();
            }
            else
            {
                QMessageBox::information(this, tr("提示"),
                tr("密码修改失败，无法访问数据库！"),
                QMessageBox::Ok);
            }
        }
        else
        {
            QMessageBox::warning(this, tr("警告"), tr("原密码错误，请重新填写！"),
            QMessageBox::Ok);
            ui->oldPwdLineEdit->clear();
            ui->newPwdLineEdit->clear();
            ui->oldPwdLineEdit->setFocus();
        }
    }
}

/********************************************
 ** 名称：“返回” 按钮——槽函数
 ** 功能：取消修改密码，返回登录界面
 ** 信号：单击鼠标左键
 ** 参数：---
 *********************************************/
void LoginDialog::on_undoChangePwdBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

/********************************************
 ** 名称：“显示密码” 按钮——槽函数
 ** 功能：显示修改密码界面输入的密码
 ** 信号：单击鼠标左键
 ** 参数：---
 *********************************************/
void LoginDialog::on_showPwdBtn_2_clicked()
{
    if(ui->showPwdBtn_2->isChecked())
    {
        ui->oldPwdLineEdit->setEchoMode(QLineEdit::Normal);
        ui->newPwdLineEdit->setEchoMode(QLineEdit::Normal);
    }
    else
    {
        ui->oldPwdLineEdit->setEchoMode(QLineEdit::Password);
        ui->newPwdLineEdit->setEchoMode(QLineEdit::Password);
    }
}
