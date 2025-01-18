#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

//#include "dragdialog.h"
#include "qdebug.h"
#include "QSettings"
#include <QDialog>
#include <QMouseEvent>
namespace Ui {
class Message;
}

class Message : public QDialog
{
    Q_OBJECT
public:
    enum StandardButton { cancelButton = 0, okButton = 1 };
    enum MessageType { information= 1, closeButton , deleteCommand, resetButton, tipButton,frequencResetButton,confirmButton };
    enum SKIN_TYPE { SKIN_BLUE = 0, SKIN_WOOD = 1, SKIN_SLIVER = 2 };
    explicit Message(QWidget *parent = nullptr,
                     QString title=tr(""),
                     QString msg=tr(""),
                     int type = information,
                     int buttons = okButton,
                     bool displayAgain = false);
    ~Message();

    Message *msgInfo(QString title=tr(""), QString msg=tr(""), int type = information);

    void re_load_interface();

protected:
    virtual void mousePressEvent(QMouseEvent *event);       // 鼠标按下
    virtual void mouseMoveEvent(QMouseEvent *event);        // 移动
    virtual void mouseReleaseEvent(QMouseEvent *event);     // 鼠标释放
    bool m_pressed;       // 判断鼠标左键是否按下
    QPoint m_pos;         // 鼠标相对于窗口的位置，不是相对屏幕的位置
private slots:
    void on_question_okBtn_clicked();

    void on_question_cancelBtn_clicked();

private:
    Ui::Message *ui;
    QPoint move_point;
    int m_type;
    QString m_iniPath;
};

#endif // MESSAGEBOX_H
