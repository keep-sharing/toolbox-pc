#ifndef TABLEVIEWDELEGATE_H
#define TABLEVIEWDELEGATE_H
#include <QStyledItemDelegate>
#include <QStyleOption>
#include <QLineEdit>
#include <QDebug>
#include <QComboBox>
#include <QItemDelegate>
class EmptyDelegate : public QStyledItemDelegate
{
public:
    EmptyDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) { }
    QWidget *createEditor(QWidget *pWidget, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        pWidget->setFocusPolicy(Qt::NoFocus);
        Q_UNUSED(option)
        Q_UNUSED(index)
        return nullptr;
    }
};

class LineEditDelegateForIP : public QStyledItemDelegate
{
    Q_OBJECT
public:
    LineEditDelegateForIP(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor,  const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor,const QStyleOptionViewItem &option, const QModelIndex &index) const;
signals:
    void SolelyModifyIp(int index) const;
private:
    QMap<QModelIndex, QStyleOptionFocusRect*> m_lineEdit;
};

class LineEditDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    LineEditDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {
        CurrentIndex =0;
    }
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor,  const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, QModelIndex &index);
    void updateEditorGeometry(QWidget *editor,const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void getCurrentRow(int row);
    QVariantList isCurrentRowRunning;

signals:

    void SnTextChange(int index, QString snText) const;

    void SnCurrentRow(int row) const;

public slots:
    void lineEditChanged(QString sn);
private:
    QMap<QModelIndex, QStyleOptionFocusRect*> m_lineEdit;
    int CurrentIndex;



};
#if 1
class ButtonDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    ButtonDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);
    void buttonTextChanged(QString text, QModelIndex index);
signals:
    void startBurnClicked(int row, int column,QString btnText);

private:
//    QMap<QModelIndex, QStyleOptionButton*> m_btns;
    typedef QMap<QModelIndex, QPair<QStyleOptionButton*, QStyleOptionButton*>* >  collButtons;
    collButtons m_btns;


};

class ButtonDelegate2 : public QStyledItemDelegate
{
    Q_OBJECT
public:
    ButtonDelegate2(QObject *parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);
//    void buttonTextChanged(QString text, QModelIndex index);
signals:
    void LogClicked(int row);

private:
//    QMap<QModelIndex, QStyleOptionButton*> m_btns;
    typedef QMap<QModelIndex, QPair<QStyleOptionButton*, QStyleOptionButton*>* >  collButtons;
    collButtons m_btns;

};

class ButtonDelegate3 : public QStyledItemDelegate
{
    Q_OBJECT
public:
    ButtonDelegate3(QObject *parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);
//    void buttonTextChanged(QString text, QModelIndex index);
signals:
    void TalkingClicked(int row);

private:
//    QMap<QModelIndex, QStyleOptionButton*> m_btns;
    typedef QMap<QModelIndex, QPair<QStyleOptionButton*, QStyleOptionButton*>* >  collButtons;
    collButtons m_btns;

};


class ProgressDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    ProgressDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QWidget *createEditor(QWidget *pWidget, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        Q_UNUSED(pWidget)
        Q_UNUSED(option)
        Q_UNUSED(index)
        return nullptr;
    }

signals:
//    void startBurnClicked(int row, int column);

private:

};

//性别列，利用QComboBox委托对输入进行限制
//这一列的单元格只能输入Male或Female
class CBXDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    CBXDelegate(QObject *parent = nullptr);

//    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,const QModelIndex &index) const;

    void setEditorData(QWidget *editor, const QModelIndex &index)const;

    void setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const;

    void updateEditorGeometry(QWidget *editor,const QStyleOptionViewItem &option, const QModelIndex &index) const;

    QStringList getSoundList(QStringList soundList);

private:
//    typedef QMap<QModelIndex, QPair<QStyleOptionComboBox*, QStyleOptionComboBox*>* >  collCombobox;
//    collCombobox m_cbxs;
    QStringList m_soundList;
};

#if 1
class PictureDelegate : public QItemDelegate
{
public:
    PictureDelegate(QString pic);
    void paint(QPainter * painter,
            const QStyleOptionViewItem & option,
            const QModelIndex & index) const;
    bool editorEvent(QEvent * event,
        QAbstractItemModel * model,
        const QStyleOptionViewItem & option,
        const QModelIndex & index);
private:
    QPixmap favouritePixmap;
    QString picPath;
};
#endif

#endif
#endif // TABLEVIEWDELEGATE_H
