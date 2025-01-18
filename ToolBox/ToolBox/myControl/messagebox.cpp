#include "messagebox.h"
#include "ui_messagebox.h"

Message::Message(QWidget *parent, QString title, QString msg, int type, int buttons, bool displayAgain)
    : QDialog(parent), ui(new Ui::Message)
{
	ui->setupUi(this);
    setWindowModality(Qt::WindowModal);
    setAttribute(Qt::WA_DeleteOnClose);
//    setWindowFlags(Qt::FramelessWindowHint);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

    m_iniPath = QApplication::applicationDirPath()+"/config.ini";

    ui->titleTips->setText(title);
    ui->messageTips->setText(msg);

    ui->tip_okBtn->show();
    ui->question_cancelBtn->hide();
    ui->question_okBtn->hide();

    ui->question_okBtn->setText("OK");
    ui->displayAgain_frame->setVisible(displayAgain);
    m_type = type;

    if(type == confirmButton){
        ui->question_okBtn->setText(tr("Confirm"));
    }
    if(type == closeButton){
        QSettings settings(m_iniPath, QSettings::IniFormat);
        settings.beginGroup("CloseTipAgain");
        bool again= settings.value("again").toBool();
        settings.endGroup();
        ui->displayAgain_frame->setVisible(again);
    }
    if(type == deleteCommand){
        QSettings settings(m_iniPath, QSettings::IniFormat);
        settings.beginGroup("CloseTipAgain");
        bool again= settings.value("deleteCommand").toBool();
        settings.endGroup();
        ui->displayAgain_frame->setVisible(again);
    }
    if(type == resetButton){
        QSettings settings(m_iniPath, QSettings::IniFormat);
        settings.beginGroup("CloseTipAgain");
        bool again= settings.value("reset").toBool();
        settings.endGroup();
        ui->displayAgain_frame->setVisible(again);
    }

    if(buttons == cancelButton){
        ui->question_cancelBtn->show();
        ui->question_okBtn->show();
        ui->tip_okBtn->hide();
    }
    if(buttons == tipButton){
        ui->question_cancelBtn->hide();
        ui->question_okBtn->hide();
        ui->tip_okBtn->hide();
    }
}

Message::~Message()
{
    delete ui;
}

Message *Message::msgInfo(QString title, QString msg, int type)
{
    Q_UNUSED(type)

    ui->titleTips->setText(title);
    ui->messageTips->setText(msg);

    bool again = false;
    QSettings settings(m_iniPath, QSettings::IniFormat);
    settings.beginGroup("CloseTipAgain");
    if(type == closeButton){
        again= settings.value("again").toBool();
    }

    if(type == deleteCommand){
        QSettings settings(m_iniPath, QSettings::IniFormat);
        again= settings.value("deleteCommand").toBool();
    }

    if(type == resetButton){
        QSettings settings(m_iniPath, QSettings::IniFormat);
        again = settings.value("reset").toBool();
    }
    ui->displayAgain_frame->setVisible(again);
    settings.endGroup();

    ui->question_cancelBtn->show();
    ui->question_okBtn->show();
    ui->tip_okBtn->hide();


    return this;
}

void Message::re_load_interface()
{
    ui->retranslateUi(this);
}

void Message::on_question_okBtn_clicked()
{
    bool checked = ui->displayAgain_cb->isChecked();
    QString m_iniPath = QApplication::applicationDirPath()+"/config.ini";
    QSettings settings(m_iniPath, QSettings::IniFormat);
    settings.beginGroup("CloseTipAgain");
    if(m_type == deleteCommand){
        settings.setValue("deleteCommand",!checked);
    }else if(m_type == closeButton){
        settings.setValue("again",!checked);
    }else if(m_type == resetButton){
        settings.setValue("reset",!checked);
    }
    settings.endGroup();

    hide();
}

void Message::on_question_cancelBtn_clicked()
{
    hide();
}

void Message::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if((event->pos().y() > ui->titleBar->y()) && event->pos().y() < ui->titleBar->y()+ui->titleBar->height()){
            m_pressed = true;
            m_pos = event->pos();
        }
    }
}

void Message::mouseMoveEvent(QMouseEvent *event)
{
    if(m_pressed)
    {
        move(event->pos() - m_pos + this->pos());
    }
}

void Message::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)// avoid the warnning that 'event' is unused while building the project
    m_pressed = false;
}

