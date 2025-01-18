#include "tableviewdelegate.h"

#include <QApplication>
#include <QMouseEvent>
#include <QMessageBox>
#include <QPainter>
#include <QStyleOption>
#include <QDesktopWidget>
#include <QDebug>
//#include <QApplication>
#include <QPalette>
#include<QPushButton>
#include <QMessageBox>
#include <QMutex>
#if 1
ButtonDelegate::ButtonDelegate(QObject *parent)
    : QStyledItemDelegate(parent){
}

void ButtonDelegate::buttonTextChanged(QString text, QModelIndex index)
{
//    qDebug()<<"buttonTextChanged"<<text;

    m_btns.value(index)->first->text = text;

    return ;
}

void ButtonDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QPair<QStyleOptionButton*, QStyleOptionButton*>* buttons = m_btns.value(index);
    if (!buttons) {
        QStyleOptionButton* button1 = new QStyleOptionButton();
        button1->text = QString::fromLocal8Bit("开始");
        button1->state |= QStyle::State_Enabled;

        QStyleOptionButton* button2 = new QStyleOptionButton();
        button2->text = "Y";
        button2->state |= QStyle::State_Enabled;
        buttons =new  QPair<QStyleOptionButton*, QStyleOptionButton*>(button1, button2);
        (const_cast<ButtonDelegate *>(this))->m_btns.insert(index, buttons);
    }
    buttons->first->rect = option.rect.adjusted(4, 4, -4 , -4); //
    painter->save();

    if (option.state & QStyle::State_Selected) {
        painter->fillRect(option.rect, option.palette.highlight());
    }
    painter->restore();
    QApplication::style()->drawControl(QStyle::CE_PushButton, buttons->first, painter);

}

bool ButtonDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{

    Q_UNUSED(model)
    Q_UNUSED(option)
    if (event->type() == QEvent::MouseButtonRelease) {
        QMouseEvent* e =(QMouseEvent*)event;

        if (m_btns.contains(index)) {
            QPair<QStyleOptionButton*, QStyleOptionButton*>* btns = m_btns.value(index);
            if (btns->first->rect.contains(e->x(), e->y())) {
                btns->first->state &= (~QStyle::State_Sunken);
                if(m_btns.value(index)->first->text == QString::fromLocal8Bit("停止")){
                    m_btns.value(index)->first->text = QString::fromLocal8Bit("开始");
                }
                else{
                     m_btns.value(index)->first->text = QString::fromLocal8Bit("停止");
                }
                startBurnClicked(index.row(),index.column(),m_btns.value(index)->first->text);
            }
        }
    }
    return true;
}


ButtonDelegate2::ButtonDelegate2(QObject *parent)
    : QStyledItemDelegate(parent){
}

void ButtonDelegate2::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

    QPair<QStyleOptionButton*, QStyleOptionButton*>* buttons = m_btns.value(index);
    if (!buttons) {
        QStyleOptionButton* button1 = new QStyleOptionButton();
        //button1->rect = option.rect.adjusted(4, 4, -(option.rect.width() / 2 + 4) , -4); //
        button1->text = QString::fromLocal8Bit("");
        button1->state |= QStyle::State_Enabled;

        QStyleOptionButton* button2 = new QStyleOptionButton();
        //button2->rect = option.rect.adjusted(button1->rect.width() + 4, 4, -4, -4);
        button2->text = "Y";
        button2->state |= QStyle::State_Enabled;
        buttons =new  QPair<QStyleOptionButton*, QStyleOptionButton*>(button1, button2);
        (const_cast<ButtonDelegate2 *>(this))->m_btns.insert(index, buttons);
    }
    buttons->first->rect = option.rect.adjusted(4, 4, -4 , -4); //
//    buttons->second->rect = option.rect.adjusted(buttons->first->rect.width() + 4, 4, -4, -4);
    painter->save();

    if (option.state & QStyle::State_Selected) {
        painter->fillRect(option.rect, option.palette.highlight());

    }
    painter->restore();
    QApplication::style()->drawControl(QStyle::CE_PushButton, buttons->first, painter);
//    QApplication::style()->drawControl(QStyle::CE_PushButton, buttons->second, painter);
}

bool ButtonDelegate2::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    Q_UNUSED(model)
    Q_UNUSED(option)
    if (event->type() == QEvent::MouseButtonRelease) {
        QMouseEvent* e =(QMouseEvent*)event;

        if (m_btns.contains(index)) {
            QPair<QStyleOptionButton*, QStyleOptionButton*>* btns = m_btns.value(index);
            if (btns->first->rect.contains(e->x(), e->y())) {
                btns->first->state &= (~QStyle::State_Sunken);
                LogClicked(index.row());
            } else if(btns->second->rect.contains(e->x(), e->y())) {
                btns->second->state &= (~QStyle::State_Sunken);
            }
        }
    }
    return true;
}

ButtonDelegate3::ButtonDelegate3(QObject *parent)
    : QStyledItemDelegate(parent){
}
void ButtonDelegate3::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

    QPair<QStyleOptionButton*, QStyleOptionButton*>* buttons = m_btns.value(index);
    if (!buttons) {
        QStyleOptionButton* button1 = new QStyleOptionButton();
        //button1->rect = option.rect.adjusted(4, 4, -(option.rect.width() / 2 + 4) , -4); //
        button1->text = QString::fromLocal8Bit("通话");
        button1->state |= QStyle::State_Enabled;

        QStyleOptionButton* button2 = new QStyleOptionButton();
        //button2->rect = option.rect.adjusted(button1->rect.width() + 4, 4, -4, -4);
        button2->text = "Y";
        button2->state |= QStyle::State_Enabled;
        buttons =new  QPair<QStyleOptionButton*, QStyleOptionButton*>(button1, button2);
        (const_cast<ButtonDelegate3 *>(this))->m_btns.insert(index, buttons);
    }
    buttons->first->rect = option.rect.adjusted(4, 4, -4 , -4); //
//    buttons->second->rect = option.rect.adjusted(buttons->first->rect.width() + 4, 4, -4, -4);
    painter->save();

    if (option.state & QStyle::State_Selected) {
        painter->fillRect(option.rect, option.palette.highlight());

    }
    painter->restore();
    QApplication::style()->drawControl(QStyle::CE_PushButton, buttons->first, painter);
//    QApplication::style()->drawControl(QStyle::CE_PushButton, buttons->second, painter);
}
bool ButtonDelegate3::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    Q_UNUSED(model)
    Q_UNUSED(option)
    if (event->type() == QEvent::MouseButtonRelease) {
        QMouseEvent* e =(QMouseEvent*)event;

        if (m_btns.contains(index)) {
            QPair<QStyleOptionButton*, QStyleOptionButton*>* btns = m_btns.value(index);
            if (btns->first->rect.contains(e->x(), e->y())) {
                btns->first->state &= (~QStyle::State_Sunken);
//                LogClicked(index.row());
                TalkingClicked(index.row());
            } else if(btns->second->rect.contains(e->x(), e->y())) {
                btns->second->state &= (~QStyle::State_Sunken);
            }
        }
    }
    return true;
}


QWidget *LineEditDelegateForIP::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)
//    parent->setFocusPolicy(Qt::NoFocus);
    QLineEdit* label = new QLineEdit(parent);
    QRegExp regExp("(\\d{1,3}\\.){3}\\d{1,3}");
    label->setValidator(new QRegExpValidator(regExp, parent));
    return label;
}
void LineEditDelegateForIP::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString text = index.model()->data(index, Qt::EditRole).toString();
    QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
//    qDebug()<<"setEditorData lineEdit.."<<text;
    lineEdit->setText(text);
    emit SolelyModifyIp(index.row()) ;
}
void LineEditDelegateForIP::setModelData(QWidget *editor, QAbstractItemModel *model, QModelIndex &index) const
{
    QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
    QString text = lineEdit->text();
//    qDebug()<<"setModelData...LineEditDelegateForIP text."<<text;
    model->setData(index, text, Qt::EditRole);
    emit SolelyModifyIp(index.row()) ;
}
void LineEditDelegateForIP::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index)
    editor->setGeometry(option.rect);
}

////////////LineEdit
QWidget *LineEditDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)
//    parent->setFocusPolicy(Qt::NoFocus);
    QLineEdit* label = new QLineEdit(parent);
    QRegExp regExp("[0-Z]{0,12}");

    connect(label,SIGNAL(textChanged(QString)),this,SLOT(lineEditChanged(QString)));
    label->setValidator(new QRegExpValidator(regExp, parent));
    return label;
}

void LineEditDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString text = index.model()->data(index, Qt::EditRole).toString();
    QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
//    qDebug()<<"setEditorData lineEdit.."<<text<<index.row();
//    mutex.lock();
    emit SnCurrentRow(index.row());
//    mutex.unlock();
    lineEdit->setText(text);
}
void LineEditDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index)
    editor->setGeometry(option.rect);
}
void LineEditDelegate::getCurrentRow(int row)
{
    CurrentIndex =row;
//    qDebug()<<"getCurrentRow.."<<CurrentIndex;
}
void LineEditDelegate::lineEditChanged(QString sn)
{
//    qDebug()<<"111234";
    if(sn.length() == 12){
//        qDebug()<<"lineEditChanged....."<<sn<<CurrentIndex;
        emit SnTextChange(CurrentIndex,sn);
    }
}
void LineEditDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,  QModelIndex &index)
{
    QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
    QString text = lineEdit->text();
//    qDebug()<<"setModelData...lineEdit text."<<text;
    model->setData(index, text, Qt::EditRole);
//    emit SnTextChange(index.row(),sn);
}


ProgressDelegate::ProgressDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}
void ProgressDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    int progress = index.data().toInt();
    QStyleOptionProgressBar progressBar;
    progressBar.rect = option.rect;
    progressBar.minimum = 0;
    progressBar.maximum = 100;
    progressBar.progress = progress;
//    progressBar.text = QString::number(progress)+"%";
    progressBar.textVisible = false;
    QApplication::style()->drawControl(QStyle::CE_ProgressBar, &progressBar, painter);
}
#endif


CBXDelegate::CBXDelegate(QObject *parent)
    : QStyledItemDelegate(parent){
}

QStringList CBXDelegate::getSoundList(QStringList soundList)
{
    return m_soundList = soundList;
}

QWidget *CBXDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)
    QComboBox *editor = new QComboBox(parent);
    qDebug()<<"CBXDelegate::createEditor"<<index.row();
    editor->addItems(m_soundList);
//    editor1->addItem("Female");
//    editor1->addItem("Male");

    return editor;
}

void CBXDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    qDebug()<<"setEditorData";
    QString text = index.model()->data(index, Qt::EditRole).toString();
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    int tindex = comboBox->findText(text);
    comboBox->setCurrentIndex(tindex);
}
void CBXDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    qDebug()<<"setModelData";
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    QString text = comboBox->currentText();
    model->setData(index, text, Qt::EditRole);
}
void CBXDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index)
    editor->setGeometry(option.rect);
}

#if 01
PictureDelegate::PictureDelegate(QString pic)
    :picPath(pic)
{
    favouritePixmap=QPixmap(picPath);
}

void PictureDelegate::paint(QPainter * painter,
                           const QStyleOptionViewItem & option,
                           const QModelIndex & index) const
{
    const QAbstractItemModel * model=index.model();
    QVariant var=model->data(index,Qt::CheckStateRole);
    if(var.isNull()) var=false;
    QPixmap star1;
    QRect rect=option.rect;
    star1 = favouritePixmap.scaled(23,30);
    int width=star1.width();
    int height=star1.height();

    int x=rect.x()+rect.width()/2-width/2;
    int y=rect.y()+rect.height()/2-height/2;
    painter->drawPixmap(x,y,star1);
}

bool PictureDelegate::editorEvent(QEvent * event,
                                 QAbstractItemModel * model,
                                 const QStyleOptionViewItem & /*option*/,
                                 const QModelIndex & index)
{
    if(event->type()==QEvent::MouseButtonPress &&
        index.column()==0){
            QVariant var=model->data(index,Qt::CheckStateRole);
            bool isFavourite=var.toBool();
            if(var.isValid())
                isFavourite=isFavourite?false:true;
            else
                isFavourite=true;
            model->setData(index,isFavourite,Qt::CheckStateRole);
            return true;//I have handled the event
    }

    return false;
}
#endif
