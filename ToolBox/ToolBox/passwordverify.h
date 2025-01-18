#ifndef PASSWORDVERIFY_H
#define PASSWORDVERIFY_H

#include <QDialog>
#include <QPropertyAnimation>
#include <QMouseEvent>
#include "version.h"
namespace Ui {
class PasswordVerify;
}

class PasswordVerify : public QDialog
{
    Q_OBJECT

public:
    explicit PasswordVerify(QWidget *parent = nullptr);
    ~PasswordVerify();

    void checkPwdAgain();
    void setExecutions(QString e);
    void setDefaultPwd(QString m_pwd);
    QString pwd;
    QString executions;
private slots:
    void on_close_btn_clicked();

    void on_pwd_lineedit_returnPressed();

    void on_enter_btn_clicked();

    void changeEvent(QEvent *e);
protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);
    bool m_pressed;
    QPoint m_pos;

private:
    Ui::PasswordVerify *ui;
    QPropertyAnimation *pAnimation;
};

#endif // PASSWORDVERIFY_H
