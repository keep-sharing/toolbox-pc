#include "upgradewnd.h"
#include "ui_upgradewnd.h"
#include <QMouseEvent>

UpgradeWnd::UpgradeWnd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UpgradeWnd)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Tool | Qt::FramelessWindowHint);
}

UpgradeWnd::~UpgradeWnd()
{
    delete ui;
}

void UpgradeWnd::setTipText(QString txt)
{
    ui->label->setText(txt);
}

void UpgradeWnd::onProgressChanged(int progress)
{
    if(progress == -1){
        close();
        return;
    }
    ui->bar1->setValue(progress);
}


void UpgradeWnd::changeEvent(QEvent *e)
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

void UpgradeWnd::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        mouse_press = true;
    }

    move_point = event->globalPos() - pos();
}

void UpgradeWnd::mouseReleaseEvent(QMouseEvent *)
{
    mouse_press = false;
}

void UpgradeWnd::mouseMoveEvent(QMouseEvent *event)
{
    if(mouse_press)
    {
        QPoint move_pos = event->globalPos();
        move(move_pos - move_point);
    }
}
