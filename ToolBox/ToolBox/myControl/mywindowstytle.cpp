#include "mywindowstytle.h"

MyWindowStytle::MyWindowStytle(QWidget *parent) : QWidget(parent)
{

}

void MyWindowStytle::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Escape:
        break;
    }
}
