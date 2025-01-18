#include "passwordverify.h"
#include "ui_passwordverify.h"

PasswordVerify::PasswordVerify(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PasswordVerify)
{
    ui->setupUi(this);
    setWindowModality(Qt::ApplicationModal);
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint );


    ui->wrongPwd_label->setVisible(false);
    pAnimation = new QPropertyAnimation(this, "pos");
    ui->pwd_lineedit->setClearButtonEnabled(true);
    ui->pwd_lineedit->setFocus();
    pwd = "";
}

PasswordVerify::~PasswordVerify()
{
    delete ui;
}

void PasswordVerify::setExecutions(QString e)
{
    ui->pwd_lineedit->setFocus();
    executions = e;
}

void PasswordVerify::setDefaultPwd(QString m_pwd)
{
    pwd = m_pwd;
    ui->pwd_lineedit->setText(pwd.trimmed());
}

void PasswordVerify::checkPwdAgain()
{
    ui->wrongPwd_label->setVisible(true);
    ui->pwd_lineedit->clear();
    pAnimation->setDuration(500);
    pAnimation->setLoopCount(1);
    pAnimation->setKeyValueAt(0, QPoint(pos().x() - 3, pos().y() - 3));
    pAnimation->setKeyValueAt(0.1, QPoint(pos().x() + 6, pos().y() + 6));
    pAnimation->setKeyValueAt(0.2, QPoint(pos().x() - 6, pos().y() + 6));
    pAnimation->setKeyValueAt(0.3, QPoint(pos().x() + 6, pos().y() - 6));
    pAnimation->setKeyValueAt(0.4, QPoint(pos().x() - 6, pos().y() - 6));
    pAnimation->setKeyValueAt(0.5, QPoint(pos().x() + 6, pos().y() + 6));
    pAnimation->setKeyValueAt(0.6, QPoint(pos().x() - 6, pos().y() + 6));
    pAnimation->setKeyValueAt(0.7, QPoint(pos().x() + 6, pos().y() - 6));
    pAnimation->setKeyValueAt(0.8, QPoint(pos().x() - 6, pos().y() - 6));
    pAnimation->setKeyValueAt(0.9, QPoint(pos().x() + 6, pos().y() + 6));
    pAnimation->setKeyValueAt(1, QPoint(pos().x() - 3, pos().y() - 3));
    pAnimation->start();
}

void PasswordVerify::on_pwd_lineedit_returnPressed()
{
    if(ui->pwd_lineedit->text().length() == 6){
        pwd = ui->pwd_lineedit->text().trimmed();
        ui->wrongPwd_label->setVisible(false);
        accept();
    }
}

void PasswordVerify::on_enter_btn_clicked()
{
    on_pwd_lineedit_returnPressed();
}

void PasswordVerify::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if((event->pos().y() > ui->titleBar->y()) && event->pos().y() < ui->titleBar->y()+ui->titleBar->height()){
            m_pressed = true;
            m_pos = event->pos();
        }
    }
}

void PasswordVerify::mouseMoveEvent(QMouseEvent *event)
{
    if(m_pressed)
    {
        move(event->pos() - m_pos + this->pos());
    }
}

void PasswordVerify::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)// avoid the warnning that 'event' is unused while building the project
    m_pressed = false;

}

void PasswordVerify::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter){

    }
}

void PasswordVerify::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter){

    }
}

void PasswordVerify::on_close_btn_clicked()
{
    ui->wrongPwd_label->setVisible(false);
    close();
}

void PasswordVerify::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}


