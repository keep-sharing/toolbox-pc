#include "mylineedit.h"
#include <QLabel>
MyLineedit::MyLineedit(QWidget *parent): QLineEdit(parent)
{
}


void MyLineedit::focusInEvent(QFocusEvent *event)
{
    QTimer::singleShot(0,this,SLOT(selectAll()));
    QLineEdit::focusInEvent(event);
}

void MyLineedit::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        this->selectAll();
    }
}
