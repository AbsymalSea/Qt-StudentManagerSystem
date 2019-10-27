#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>

/********************************************
 ** 名称：“主界面” 类——构造函数
 ** 功能：在数据库中建表，设置界面、图标、按钮
 ** 信号：---
 ** 参数：---
 *********************************************/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    model = new QSqlTableModel(this);
    model->setTable("student");
    model->select();

    // 设置编辑策略
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView->setModel(model);

    // 设置主界面
    setTableViewTitle();
    setWindowTitle(tr("学生综合评测系统1.0.0"));
    MainWindow::countRank();
    MainWindow::countScore();

    // 设置主界面按钮图标大小
    ui->undoBtn->setIconSize(QSize(40, 40));
    ui->modifyBtn->setIconSize(QSize(40, 40));
    ui->addBtn->setIconSize(QSize(40, 40));
    ui->deleteBtn->setIconSize(QSize(40, 40));
    ui->ascendingOrderBtn->setIconSize(QSize(40, 40));
    ui->descedingOrderBtn->setIconSize(QSize(40, 40));
    ui->reloadBtn->setIconSize(QSize(40, 40));
    ui->searchByIdBtn->setIconSize(QSize(40, 40));
    ui->searchByNameBtn->setIconSize(QSize(40, 40));


    // 设置主界面按钮图标来源
    ui->undoBtn->setIcon(QIcon(":/myImages/images/undoBundle.png"));
    ui->modifyBtn->setIcon(QIcon(":/myImages/images/handinputBundle.png"));
    ui->addBtn->setIcon(QIcon(":/myImages/images/addBundle.png"));
    ui->deleteBtn->setIcon(QIcon(":/myImages/images/screencaptureBundle.png"));
    ui->ascendingOrderBtn->setIcon(QIcon(":/myImages/images/inputstatisticsBundle.png"));
    ui->descedingOrderBtn->setIcon(QIcon(":/myImages/images/inputstatisticsBundle2.png"));
    ui->reloadBtn->setIcon(QIcon(":/myImages/images/scdWEbBundle.png"));
    ui->searchByIdBtn->setIcon(QIcon(":/myImages/images/searchById.png"));
    ui->searchByNameBtn->setIcon(QIcon(":/myImages/images/searchByName.png"));

    // 设置主界面按钮可用性
    ui->searchByIdBtn->setEnabled(false);
    ui->searchByNameBtn->setEnabled(false);

}

/********************************************
 ** 名称：“主界面” 类——析构函数
 ** 功能：析构
 ** 信号：---
 ** 参数：---
 *********************************************/
MainWindow::~MainWindow()
{
    delete ui;
}

/********************************************
 ** 名称：“主界面” 类——标题栏设置函数
 ** 功能：将数据库中的英文标题栏转为中文
 ** 信号：---
 ** 参数：---
 *********************************************/
void MainWindow::setTableViewTitle()
{
    model->setHeaderData(0, Qt::Horizontal, tr("学号"));
    model->setHeaderData(1, Qt::Horizontal, tr("姓名"));
    model->setHeaderData(2, Qt::Horizontal, tr("性别"));
    model->setHeaderData(3, Qt::Horizontal, tr("地址"));
    model->setHeaderData(4, Qt::Horizontal, tr("手机号码"));
    model->setHeaderData(5, Qt::Horizontal, tr("语文"));
    model->setHeaderData(6, Qt::Horizontal, tr("数学"));
    model->setHeaderData(7, Qt::Horizontal, tr("英语"));
    model->setHeaderData(8, Qt::Horizontal, tr("三科平均分"));
    model->setHeaderData(9, Qt::Horizontal, tr("考试名次"));
    model->setHeaderData(10, Qt::Horizontal, tr("品德成绩"));
    model->setHeaderData(11, Qt::Horizontal, tr("教师评分"));
    model->setHeaderData(12, Qt::Horizontal, tr("同学互评分"));
    model->setHeaderData(13, Qt::Horizontal, tr("综合测评总分"));
    model->setHeaderData(14, Qt::Horizontal, tr("综合测评排名"));
}

/********************************************
 ** 名称：“添加记录” 按钮——槽函数
 ** 信号：单击鼠标左键
 ** 参数：---
 *********************************************/
void MainWindow::on_addBtn_clicked()
{
    // 获得表的行数
    int rowNum = model->rowCount();
    // 添加一行
    model->insertRow(rowNum);
    model->setData(model->index(rowNum, 0), rowNum);
}

/********************************************
 ** 名称：“提交修改” 按钮——槽函数
 ** 信号：单击鼠标左键
 ** 参数：---
 *********************************************/
void MainWindow::on_modifyBtn_clicked()
{
    // 开始事务操作
    model->database().transaction();
    if (model->submitAll())
    {
        // 提交
        model->database().commit();
        QMessageBox::information(this, tr("提示"), tr("修改成功！"), QMessageBox::Ok);

    }
    else
    {
        // 回滚
        model->database().rollback();
        QMessageBox::information(this, tr("提示"), tr("修改失败，无法访问数据库！"), QMessageBox::Ok);
    }

    qDebug() << "counted";
}

/********************************************
 ** 名称：“撤销修改” 按钮——槽函数
 ** 功能：未提交修改时，撤销修改过的内容
 ** 信号：单击鼠标左键
 ** 参数：---
 *********************************************/
void MainWindow::on_undoBtn_clicked()
{
    model->revertAll();
}

/********************************************
 ** 名称：“删除选中行” 按钮——槽函数
 ** 功能：从数据库删除相应的行
 ** 信号：单击鼠标左键
 ** 参数：---
 *********************************************/
void MainWindow::on_deleteBtn_clicked()
{

    // 获取选中的行
    int curRow = ui->tableView->currentIndex().row();

    // 删除该行
    model->removeRow(curRow);
    int ok = QMessageBox::warning(this,tr("删除当前行!"),
                    tr("你确定删除当前行吗？"), QMessageBox::Yes, QMessageBox::No);
    if(ok == QMessageBox::No)
    {
        // 如果不删除，则撤销
        model->revertAll();
    }
    else
    {
        // 否则提交，在数据库中删除该行
        if(model->submitAll())
        {
            // 提交
            model->database().commit();
            QMessageBox::information(this, tr("提示"), tr("删除成功！"), QMessageBox::Ok);
        }
        else
        {
            // 回滚
            model->database().rollback();
            QMessageBox::information(this, tr("提示"), tr("删除失败，无法访问数据库！"), QMessageBox::Ok);
        }
    }
}

/********************************************
 ** 名称：“按综测成绩升序排列” 按钮——槽函数
 ** 功能：按综测成绩升序显示
 ** 信号：单击鼠标左键
 ** 参数：---
 *********************************************/
void MainWindow::on_ascendingOrderBtn_clicked()
{
    //comboScore 属性为13 ，即第13 列（从13 开始数），升序排列
    model->setSort(13, Qt::AscendingOrder);
    model->select();
}

/********************************************
 ** 名称：“按总成绩降序排列” 按钮——槽函数
 ** 功能：按综测成绩降序显示
 ** 信号：单击鼠标左键
 ** 参数：---
 *********************************************/
void MainWindow::on_descedingOrderBtn_clicked()
{
    //comboScore 属性为13 ，即第13 列（从13 开始数），降序排列
    model->setSort(13, Qt::DescendingOrder);
    model->select();
}

/********************************************
 ** 名称：“显示全表” 按钮——槽函数
 ** 功能：查询后将只显示出一人数据，单击鼠标左键此按钮即可显示所有人
 ** 信号：单击鼠标左键
 ** 参数：---
 *********************************************/
void MainWindow::on_reloadBtn_clicked()
{
    model->setTable("student");
    model->select();
    setTableViewTitle();

    MainWindow::countScore();
    MainWindow::countRank();

}

/********************************************
 ** 名称：“按学号查询” 按钮——槽函数
 ** 功能：按学号查询并显示
 ** 信号：单击鼠标左键
 ** 参数：---
 *********************************************/
void MainWindow::on_searchByIdBtn_clicked()
{
    // trimmed() 用于去除输入字符串前后的空白字符
    QString id = ui->idSearchLineEdit->text().trimmed();
    // setFilter() 根据学号进行筛选，注意是筛选不是查找，无返回值
    model->setFilter(QString("id = '%0'").arg(id));
    model->select();

}

/********************************************
 ** 名称：“按姓名查询” 按钮——槽函数
 ** 功能：按姓名查询并显示
 ** 信号：单击鼠标左键
 ** 参数：---
 *********************************************/
void MainWindow::on_searchByNameBtn_clicked()
{
    // trimmed() 用于去除输入字符串前后的空白字符
    QString name = ui->nameSearchLineEdit->text().trimmed();
    // setFilter() 根据学号进行筛选，注意是筛选不是查找，无返回值
    model->setFilter(QString("name = '%0'").arg(name));
    model->select();

}

/********************************************
 ** 名称：“按学号查询” 文本编辑——槽函数
 ** 功能：按学号查询并显示
 ** 信号：回车
 ** 参数：---
 *********************************************/
void MainWindow::on_idSearchLineEdit_returnPressed()
{
    MainWindow::on_searchByIdBtn_clicked();
}

/********************************************
 ** 名称：“按姓名查询” 文本编辑——槽函数
 ** 功能：按姓名查询并显示
 ** 信号：回车
 ** 参数：---
 *********************************************/
void MainWindow::on_nameSearchLineEdit_returnPressed()
{
    MainWindow::on_searchByNameBtn_clicked();
}

/********************************************
 ** 名称：综测成绩计算函数
 ** 功能：计算并更新数据库中的综测成绩
 ** 信号：---
 ** 参数：---
 *********************************************/
void MainWindow::countScore()
{
    QSqlQuery query;
    int i = 0;
    int row = model->rowCount();
    double averageScore[row];
    double comboScore[row];
    QString id[row];

    query.exec("select ChineseScore, mathScore, EnglishScore, moralScore, teacherScore, mateScore, id from student");
    while(query.next())
    {
        id[i] = query.value(6).toString();
        averageScore[i] = (query.value(0).toDouble() + query.value(1).toDouble() + query.value(2).toDouble()) / 3;
        comboScore[i] = averageScore[i] * 0.6 +  query.value(3).toDouble() * 0.1 +  query.value(4).toDouble() * 0.2 +  query.value(5).toDouble() * 0.1;
        i++;
    }
    for(i = 0; i < row; i++)
    {
        query.exec(QString("update student set averageScore = %0, "
                           "comboScore = %1 where id = '%2'").arg(averageScore[i]).arg(comboScore[i]).arg(id[i]));
    }
}

/********************************************
 ** 名称：综测排名计算函数
 ** 功能：计算并更新数据库中的综测排名
 ** 信号：---
 ** 参数：---
 *********************************************/
void MainWindow::countRank()
{
    QSqlQuery query;
    int row = model->rowCount();
    QString rank[row];

    int i = 0;
    query.exec("select id from student group by id order by averageScore desc");
    while(query.next())
    {
        rank[i] = query.value(0).toString();
        i++;
    }
    for(i = 0; i < row; i++)
    {
        query.exec(QString("update student set testRank = %0 where id = '%1'").arg(i + 1).arg(rank[i]));
    }

    i = 0;
    query.exec("select id from student group by id order by comboScore desc");
    while(query.next())
    {
        rank[i] = query.value(0).toString();
        i++;
    }
    for(i = 0; i < row; i++)
    {
        query.exec(QString("update student set comboRank = %0 where id = '%1'").arg(i + 1).arg(rank[i]));
    }
}

/********************************************
 ** 名称：“按学会查询” 文本编辑——槽函数
 ** 功能：没有输入学号时，无法点击按学号查询按钮
 ** 信号：输入文字
 ** 参数：---
 *********************************************/
void MainWindow::on_idSearchLineEdit_textChanged(const QString &str)
{

    if (str == "")
    {
        ui->searchByIdBtn->setEnabled(false);
        ui->searchByNameBtn->setEnabled(false);
    }
    else
    {
        ui->searchByIdBtn->setEnabled(true);
    }
}

/********************************************
 ** 名称：“按姓名查询” 文本编辑——槽函数
 ** 功能：没有输入姓名时，无法点击按姓名查询按钮
 ** 信号：输入文字
 ** 参数：---
 *********************************************/
void MainWindow::on_nameSearchLineEdit_textChanged(const QString &str)
{
    if (str == "")
    {
        ui->searchByIdBtn->setEnabled(false);
        ui->searchByNameBtn->setEnabled(false);
    }
    else
    {
        ui->searchByNameBtn->setEnabled(true);
    }
}
