#include "mywidget.h"
#include "QDebug"
myWidget::myWidget(QWidget *parent) : QWidget(parent)
{

    qDebug()<<this->objectName()<<this->width()<<this->height()<<
              this->x()<<this->y();

//    lineedit = new QLineEdit(this);
//    lineedit->setGeometry(0,0,this->width(),this->height()/3*2);
//    qDebug()<<lineedit->width()<<lineedit->height();
//    label = new QLabel(this);
//    label->setGeometry(0,this->height()/3*2+3,this->width(),this->height()/3);
//    label->setText("DDDDD");
//    label->setStyleSheet("color: rgb(255, 0, 0);");//

}

void myWidget::setText(QString text)
{
    lineedit->setText(text);
}

void myWidget::setError(QString text)
{
    label->setText(text);
}

void myWidget::setErrorVisible(bool visible)
{
    label->setVisible(visible);
}
