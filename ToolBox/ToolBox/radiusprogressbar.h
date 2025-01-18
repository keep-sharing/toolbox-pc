#ifndef RADIUSPROGRESSBAR_H
#define RADIUSPROGRESSBAR_H

#include <QProgressBar>
#include <QApplication>
#include <QDebug>
class RadiusProgressBar : public QProgressBar
{
    Q_OBJECT
public:
    explicit RadiusProgressBar(QWidget *parent = NULL);

signals:

public slots:

protected:
    void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;
};

#endif // RADIUSPROGRESSBAR_H
