#include "waitingwnd.h"
#include "ui_waitingwnd.h"
#include <QDebug>
#include <QPainter>
WaitingWnd::WaitingWnd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WaitingWnd)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Tool | Qt::FramelessWindowHint);

    this->setAttribute(Qt::WA_TranslucentBackground, true);

    QMovie *movie = new QMovie(":/new/image/waiting.gif");
    ui->label->setMovie(movie);
    movie->start();

    this->setFixedSize(QSize(parent->width(), parent->height()));
    this->setParent(parent);
    this->move(parent->x(), parent->y());

}

WaitingWnd::~WaitingWnd()
{
    delete ui;
}

//WaitingWnd::paintEvent(QPaintEvent *)
//{

//}

void WaitingWnd::setPoint(QPoint pos)
{
    move(pos);
}

void WaitingWnd::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.fillRect(this->rect(), QColor(0, 0, 0, 80));
}


void WaitingWnd::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {

        m_pressed = true;
        m_pos = event->pos();
//        qDebug()<<__LINE__<<m_pos;
//        emit mouseClickChanged(m_pos);
    }
    movePoint = event->globalPos() - pos();
}

void WaitingWnd::mouseMoveEvent(QMouseEvent *event)
{
    if(m_pressed)
    {
//        move(event->pos() - m_pos + this->pos());

        QPoint movePos = event->globalPos();
        move(movePos - movePoint);
        windowPos = this->pos();
//        qDebug()<<__LINE__<<windowPos;
        emit mouseClickChanged(windowPos);
    }
}

void WaitingWnd::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)// avoid the warnning that 'event' is unused while building the project
    m_pressed = false;
}
