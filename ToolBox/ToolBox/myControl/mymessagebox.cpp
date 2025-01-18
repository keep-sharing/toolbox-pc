#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QEvent>
#include <QApplication>
#include <QSettings>
#include "mymessagebox.h"
#include "ui_mymessagebox.h"

MyMessageBox::MyMessageBox(QWidget *parent, const QString &title, const int &type, const QString &text,
                           QMessageBox::StandardButtons buttons, QMessageBox::StandardButton defaultButton) :
    QDialog(parent),
    ui(new Ui::MyMessageBox)
{
    ui->setupUi(this);
//    setWindowIcon(QIcon(":/Images/logo"));

    setMinimumSize(300, 130);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

    ui->buttonBox->setStandardButtons(QDialogButtonBox::StandardButtons(int(buttons)));
    setDefaultButton(defaultButton);

    QPushButton *pYesButton = ui->buttonBox->button(QDialogButtonBox::Ok);

    if (pYesButton != nullptr)
    {
        pYesButton->setStyle(QApplication::style());
    }

    m_iniPath = QApplication::applicationDirPath()+"/config.ini";
    m_type = type;
    switch (type) {
    case TYPE_NONE:{
        ui->displayAgain_frame->setVisible(false);
        break;
    }
    case TYPE_RESET:{
        QSettings settings(m_iniPath, QSettings::IniFormat);
        settings.beginGroup("CloseTipAgain");
        bool again= settings.value("reset").toBool();
        settings.endGroup();
        ui->displayAgain_frame->setVisible(again);
        break;
    }
    case TYPE_DELETE_CMD:{
        QSettings settings(m_iniPath, QSettings::IniFormat);
        settings.beginGroup("CloseTipAgain");
        bool again= settings.value("deleteCommand").toBool();
        settings.endGroup();
        ui->displayAgain_frame->setVisible(again);
        break;
    }
    case TYPE_CLOSE_WND:{
        QSettings settings(m_iniPath, QSettings::IniFormat);
        settings.beginGroup("CloseTipAgain");
        bool again= settings.value("again").toBool();
        settings.endGroup();
        ui->displayAgain_frame->setVisible(again);
        break;
    }
    }

    ui->titleTips->setText(title);
    ui->messageTips->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    ui->messageTips->setOpenExternalLinks(true);
    ui->messageTips->setText(text);

    translateUI();

    connect(ui->buttonBox, SIGNAL(clicked(QAbstractButton*)), this, SLOT(onButtonClicked(QAbstractButton*)));
}

MyMessageBox::~MyMessageBox()
{
    delete ui;
}

void MyMessageBox::changeEvent(QEvent *event)
{
    switch (event->type())
    {
    case QEvent::LanguageChange:
        translateUI();
        break;
    default:
        break;
    }
}

void MyMessageBox::translateUI()
{
    QPushButton *pYesButton = ui->buttonBox->button(QDialogButtonBox::Yes);
    if (pYesButton != nullptr)
        pYesButton->setText(tr("Yes"));

    QPushButton *pNoButton = ui->buttonBox->button(QDialogButtonBox::No);
    if (pNoButton != nullptr)
        pNoButton->setText(tr("No"));

    QPushButton *pOkButton = ui->buttonBox->button(QDialogButtonBox::Ok);
    if (pOkButton != nullptr)
        pOkButton->setText(tr("Ok"));

    QPushButton *pCancelButton = ui->buttonBox->button(QDialogButtonBox::Cancel);
    if (pCancelButton != nullptr)
        pCancelButton->setText(tr("Cancel"));
}

QMessageBox::StandardButton MyMessageBox::standardButton(QAbstractButton *button) const
{
    return (QMessageBox::StandardButton)ui->buttonBox->standardButton(button);
}

QAbstractButton *MyMessageBox::clickedButton() const
{
    return m_pClickedButton;
}

int MyMessageBox::execReturnCode(QAbstractButton *button)
{
    int nResult = ui->buttonBox->standardButton(button);
    return nResult;
}

void MyMessageBox::onButtonClicked(QAbstractButton *button)
{
    QSettings settings(m_iniPath, QSettings::IniFormat);

    if((QMessageBox::StandardButton)ui->buttonBox->standardButton(button) == QMessageBox::Ok){
        settings.beginGroup("CloseTipAgain");
        if(m_type == TYPE_DELETE_CMD){
            settings.setValue("deleteCommand",!ui->displayAgain_cb->isChecked());
        }else if(m_type == TYPE_CLOSE_WND){
            settings.setValue("again",!ui->displayAgain_cb->isChecked());
        }else if(m_type == TYPE_RESET){
            settings.setValue("reset",!ui->displayAgain_cb->isChecked());
        }
        settings.endGroup();
    }

    m_pClickedButton = button;
    done(execReturnCode(button));
}

void MyMessageBox::setDefaultButton(QPushButton *button)
{
    if (!ui->buttonBox->buttons().contains(button))
        return;
    m_pDefaultButton = button;
    button->setDefault(true);
    button->setFocus();
}

void MyMessageBox::setDefaultButton(QMessageBox::StandardButton button)
{
    setDefaultButton(ui->buttonBox->button(QDialogButtonBox::StandardButton(button)));
}

void MyMessageBox::setTitle(const QString &title)
{
    setWindowTitle(title);
}

void MyMessageBox::setText(const QString &text)
{
    ui->messageTips->setText(text);
}

void MyMessageBox::setIcon(const QString &icon)
{
//    ui->toolButton_2->setIcon(QIcon(icon));
    Q_UNUSED(icon)
}

void MyMessageBox::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if((event->pos().y() > ui->titleBar->y()) && event->pos().y() < ui->titleBar->y()+ui->titleBar->height()){
            m_pressed = true;
            m_pos = event->pos();
        }
    }
}

void MyMessageBox::mouseMoveEvent(QMouseEvent *event)
{
    if(m_pressed)
    {
        move(event->pos() - m_pos + this->pos());
    }
}

void MyMessageBox::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)// avoid the warnning that 'event' is unused while building the project
    m_pressed = false;
}

QMessageBox::StandardButton showInformation(QWidget *parent, const QString &title,
                                            const QString &text, QMessageBox::StandardButtons buttons,
                                            QMessageBox::StandardButton defaultButton)
{
    MyMessageBox msgBox(parent, title, MyMessageBox::TYPE_NONE, text, buttons, defaultButton);
    msgBox.setIcon(":/Images/information");
    if (msgBox.exec() == -1)
        return QMessageBox::Cancel;
    return msgBox.standardButton(msgBox.clickedButton());
}

QMessageBox::StandardButton showError(QWidget *parent, const QString &title,
                                      const QString &text, QMessageBox::StandardButtons buttons,
                                      QMessageBox::StandardButton defaultButton)
{
    MyMessageBox msgBox(parent, title, MyMessageBox::TYPE_NONE, text, buttons, defaultButton);
    msgBox.setIcon(":/Images/error");
    if (msgBox.exec() == -1)
        return QMessageBox::Cancel;
    return msgBox.standardButton(msgBox.clickedButton());
}

QMessageBox::StandardButton showSuccess(QWidget *parent, const QString &title,
                                        const QString &text, QMessageBox::StandardButtons buttons,
                                        QMessageBox::StandardButton defaultButton)
{
    MyMessageBox msgBox(parent, title, MyMessageBox::TYPE_NONE, text, buttons, defaultButton);
    msgBox.setIcon(":/Images/success");
    if (msgBox.exec() == -1)
        return QMessageBox::Cancel;
    return msgBox.standardButton(msgBox.clickedButton());
}

QMessageBox::StandardButton showQuestion(QWidget *parent, const QString &title, const int &type,
                                         const QString &text, QMessageBox::StandardButtons buttons,
                                         QMessageBox::StandardButton defaultButton)
{
    MyMessageBox msgBox(parent, title, type, text, buttons, defaultButton);
    msgBox.setIcon(":/Images/question");
    if (msgBox.exec() == -1)
        return QMessageBox::Cancel;
    return msgBox.standardButton(msgBox.clickedButton());
}

QMessageBox::StandardButton showWarning(QWidget *parent, const QString &title,
                                        const QString &text, QMessageBox::StandardButtons buttons,
                                        QMessageBox::StandardButton defaultButton)
{
    MyMessageBox msgBox(parent, title, MyMessageBox::TYPE_NONE, text, buttons, defaultButton);
    msgBox.setIcon(":/images/warning");
    if (msgBox.exec() == -1)
        return QMessageBox::Cancel;
    return msgBox.standardButton(msgBox.clickedButton());
}

QMessageBox::StandardButton showCritical(QWidget *parent, const QString &title,
                                         const QString &text, QMessageBox::StandardButtons buttons,
                                         QMessageBox::StandardButton defaultButton)
{
    MyMessageBox msgBox(parent, title, MyMessageBox::TYPE_NONE, text, buttons, defaultButton);
    msgBox.setIcon(":/Images/warning");
    if (msgBox.exec() == -1)
        return QMessageBox::Cancel;
    return msgBox.standardButton(msgBox.clickedButton());
}



