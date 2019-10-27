#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
class QSqlTableModel;
}

// 前置声明
class QSqlTableModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

private slots:
    void setTableViewTitle();

    void on_addBtn_clicked();

    void on_modifyBtn_clicked();

    void on_undoBtn_clicked();

    void on_deleteBtn_clicked();

    void on_ascendingOrderBtn_clicked();

    void on_descedingOrderBtn_clicked();

    void on_reloadBtn_clicked();

    void on_searchByNameBtn_clicked();

    void on_searchByIdBtn_clicked();

    void countScore();

    void countRank();

    void on_idSearchLineEdit_textChanged(const QString &str);

    void on_nameSearchLineEdit_textChanged(const QString &str);

    void on_idSearchLineEdit_returnPressed();

    void on_nameSearchLineEdit_returnPressed();

private:
    Ui::MainWindow *ui;

    QSqlTableModel *model;

};

#endif // MAINWINDOW_H
