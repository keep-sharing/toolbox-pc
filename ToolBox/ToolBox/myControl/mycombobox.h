#ifndef MYCOMBOBOX_H
#define MYCOMBOBOX_H

#include <QComboBox>

class MyCombobox : public QComboBox
{
public:
    explicit MyCombobox(QWidget *parent = nullptr);

protected:
    virtual void wheelEvent(QWheelEvent*){}
//  virtual void mousePressEvent(QMouseEvent*){}
//  virtual void mouseDoubleClickEvent(QMouseEvent*){
//        showPopup();
//    }
};

#endif // MYCOMBOBOX_H
