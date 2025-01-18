#ifndef MYLINEEDIT_H
#define MYLINEEDIT_H
#include <QLineEdit>
#include <QDebug>
#include <QMouseEvent>
#include <QTimer>
class MyLineedit : public QLineEdit
{
public:
    MyLineedit(QWidget *parent = NULL);
protected:
    void focusInEvent(QFocusEvent * event);
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // MYLINEEDIT_H
