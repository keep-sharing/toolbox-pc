#ifndef UPGRADEWND_H
#define UPGRADEWND_H

#include <QDialog>
#include "radiusprogressbar.h"
namespace Ui {
class UpgradeWnd;
}

class UpgradeWnd : public QDialog
{
    Q_OBJECT

public:
    explicit UpgradeWnd(QWidget *parent = nullptr);
    ~UpgradeWnd();

    void setTipText(QString txt);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

public slots:
    void onProgressChanged(int progress);

    void changeEvent(QEvent *e);
private:
    Ui::UpgradeWnd *ui;
    QPoint move_point; //移动的距离//
    bool mouse_press; //按下鼠标左键//

};

#endif // UPGRADEWND_H
