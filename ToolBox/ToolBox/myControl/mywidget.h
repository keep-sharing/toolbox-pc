#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>

class myWidget : public QWidget
{
    Q_OBJECT
public:
    explicit myWidget(QWidget *parent = nullptr);
    void setText(QString text);
    void setError(QString text);
    void setErrorVisible(bool visible);

signals:

private:
    QLineEdit *lineedit;
    QLabel *label;
};

#endif // MYWIDGET_H
