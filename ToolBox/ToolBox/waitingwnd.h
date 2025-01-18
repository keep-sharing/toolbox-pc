#ifndef WAITINGWND_H
#define WAITINGWND_H

#include <QWidget>
#include <QMovie>
#include <QMouseEvent>

namespace Ui {
class WaitingWnd;
}

class WaitingWnd : public QWidget
{
    Q_OBJECT

public:
    explicit WaitingWnd(QWidget *parent = nullptr);
    ~WaitingWnd();
    void setPoint(QPoint pos);

signals:
    void mouseClickChanged(QPoint pos);

protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);       // 鼠标按下
    virtual void mouseMoveEvent(QMouseEvent *event);        // 移动
    virtual void mouseReleaseEvent(QMouseEvent *event);     // 鼠标释放
    bool m_pressed;       // 判断鼠标左键是否按下
    QPoint m_pos;         // 鼠标相对于窗口的位置，不是相对屏幕的位置

private slots:
private:
    Ui::WaitingWnd *ui;
    QPoint windowPos;
    QPoint movePoint;
    QWidget* m_pMainWidget{ Q_NULLPTR };
};

#endif // WAITINGWND_H
