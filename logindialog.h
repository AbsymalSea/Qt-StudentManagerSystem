#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

private slots:

    void on_pwdLineEdit_returnPressed();

    void on_loginBtn_clicked();

    void on_quitBtn_clicked();

    void on_showPwdBtn_clicked();

    void on_changePwdBtn_clicked();

    void on_ensureChangePwdBtn_clicked();

    void on_undoChangePwdBtn_clicked();

    void on_showPwdBtn_2_clicked();

    void on_pwdLineEdit_textChanged(const QString &str);

    void on_newPwdLineEdit_textChanged(const QString &str);

    void on_oldPwdLineEdit_textChanged(const QString &str);

private:
    Ui::LoginDialog *ui;
};

#endif // LOGINDIALOG_H
