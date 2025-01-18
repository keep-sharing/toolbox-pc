#include <QMouseEvent>

#include "dragdialog.h"

DragDialog::DragDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowFlags(Qt::Tool | Qt::FramelessWindowHint);
    mouse_press = false;
}


void DragDialog::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        mouse_press = true;
    }

    move_point = event->globalPos() - pos();
}

void DragDialog::mouseReleaseEvent(QMouseEvent *)
{
    mouse_press = false;
}

void DragDialog::mouseMoveEvent(QMouseEvent *event)
{
    if(mouse_press)
    {
        QPoint move_pos = event->globalPos();
        move(move_pos - move_point);
    }
}
