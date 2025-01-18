#ifndef DRAGDIALOG_H
#define DRAGDIALOG_H

#include <QDialog>
#include <QPoint>

class DragDialog : public QDialog
{
    Q_OBJECT
public:
    DragDialog(QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    QPoint move_point; //移动的距离//
    bool mouse_press; //按下鼠标左键//

};

#endif // DRAGDIALOG_H
