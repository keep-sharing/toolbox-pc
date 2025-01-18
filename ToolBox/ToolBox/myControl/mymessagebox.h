#ifndef MYMESSAGEBOX_H
#define MYMESSAGEBOX_H

#include <QDialog>
#include <QMessageBox>
#include <QDialogButtonBox>
#include <QGridLayout>
#include <QMouseEvent>

namespace Ui {
class MyMessageBox;
}



class MyMessageBox : public QDialog
{
    Q_OBJECT

public:

    enum WND_TYPE{
        TYPE_NONE,
        TYPE_CLOSE_WND,
        TYPE_DELETE_CMD,
        TYPE_RESET
    };

    explicit MyMessageBox(QWidget *parent = nullptr, const QString &title = tr("Tip") ,const int &type=TYPE_NONE, const QString &text = "",
                            QMessageBox::StandardButtons buttons = QMessageBox::Ok, QMessageBox::StandardButton defaultButton = QMessageBox::Ok);
    ~MyMessageBox();
    QAbstractButton *clickedButton() const;
    QMessageBox::StandardButton standardButton(QAbstractButton *button) const;
    void setDefaultButton(QPushButton *button);
    void setDefaultButton(QMessageBox::StandardButton button);
    void setTitle(const QString &title);
    void setText(const QString &text);
    void setIcon(const QString &icon);


protected:
    // 多语言翻译
    void changeEvent(QEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);       // 鼠标按下
    virtual void mouseMoveEvent(QMouseEvent *event);        // 移动
    virtual void mouseReleaseEvent(QMouseEvent *event);     // 鼠标释放
    bool m_pressed;       // 判断鼠标左键是否按下
    QPoint m_pos;         // 鼠标相对于窗口的位置，不是相对屏幕的位置
private slots:
    void onButtonClicked(QAbstractButton *button);

private:
    void translateUI();
    int execReturnCode(QAbstractButton *button);
private:
    Ui::MyMessageBox *ui;

    QAbstractButton *m_pClickedButton;
    QAbstractButton *m_pDefaultButton;
    QString m_iniPath;
    int m_type;
};

QMessageBox::StandardButton showInformation(QWidget *parent, const QString &title,
                                            const QString &text, QMessageBox::StandardButtons buttons=QMessageBox::Ok,
                                            QMessageBox::StandardButton defaultButton=QMessageBox::Ok);

QMessageBox::StandardButton showError(QWidget *parent, const QString &title,
                                      const QString &text, QMessageBox::StandardButtons buttons=QMessageBox::Ok,
                                      QMessageBox::StandardButton defaultButton=QMessageBox::Ok);

QMessageBox::StandardButton showSuccess(QWidget *parent, const QString &title,
                                        const QString &text, QMessageBox::StandardButtons buttons=QMessageBox::Yes,
                                        QMessageBox::StandardButton defaultButton=QMessageBox::Yes);

QMessageBox::StandardButton showQuestion(QWidget *parent, const QString &title, const int &type,
                                         const QString &text, QMessageBox::StandardButtons buttons=QMessageBox::Ok | QMessageBox::Cancel,
                                         QMessageBox::StandardButton defaultButton=QMessageBox::Cancel);

QMessageBox::StandardButton showWarning(QWidget *parent, const QString &title,
                                        const QString &text, QMessageBox::StandardButtons buttons=QMessageBox::Ok,
                                        QMessageBox::StandardButton defaultButton=QMessageBox::Ok);

QMessageBox::StandardButton showCritical(QWidget *parent, const QString &title,
                                         const QString &text, QMessageBox::StandardButtons buttons,
                                         QMessageBox::StandardButton defaultButton);

QMessageBox::StandardButton showCheckBoxQuestion(QWidget *parent, const QString &title,
                                                 const QString &text, QMessageBox::StandardButtons buttons,
                                                 QMessageBox::StandardButton defaultButton);


#endif // MYMESSAGEBOX_H
