#ifndef MYWINDOWSTYTLE_H
#define MYWINDOWSTYTLE_H

#include <QWidget>
#include <QKeyEvent>

class MyWindowStytle : public QWidget
{
    Q_OBJECT
public:
    explicit MyWindowStytle(QWidget *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event);

signals:

};

#endif // MYWINDOWSTYTLE_H
