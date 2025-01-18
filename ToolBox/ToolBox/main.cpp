#include "toolbox.h"
#include <QApplication>

static QString current_date;
void customMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
#if UNP_LOG_DEBUG

    QByteArray localMsg = msg.toLocal8Bit();
//Qunp::pn532_recv_data(uint8_t*, uint16_t))
    const char *file = context.file ? context.file : "";
    const char *function = /*context.function ? context.function :*/ "";
    char fn[30],*p;
    strcpy(fn,(p=strrchr(file,'\\')) ? p+1 : file);
    switch (type) {
    case QtDebugMsg:
        fprintf(stderr, "Debug:(%s:%u, %s) %s \n", fn, context.line, function, localMsg.constData());
        break;
    case QtInfoMsg:
        fprintf(stderr, "Info:(%s:%u, %s) %s \n", fn, context.line, function, localMsg.constData());
        break;
    case QtWarningMsg:
        fprintf(stderr, "Warning:(%s:%u, %s) %s \n", fn, context.line, function, localMsg.constData());
        break;
    case QtCriticalMsg:
        fprintf(stderr, "Critical:(%s:%u, %s) %s \n", fn, context.line, function, localMsg.constData());
        break;
    case QtFatalMsg:
        fprintf(stderr, "Fatal:(%s:%u, %s) %s \n", fn, context.line, function, localMsg.constData());
        break;
    }
#if 0
    QString txt;

    QDateTime current_date_time;
    QDir *dir = new QDir(QApplication::applicationDirPath());

    bool exist = dir->exists("log");
    if(!exist)
        dir->mkdir("log");

    static int timeFlag = 0;

    txt = QString("%1").arg(msg);
    if(timeFlag == 0)
    {
        current_date_time = QDateTime::currentDateTime();
        current_date = current_date_time.toString("yyyy-MM-dd hh.mm");
        timeFlag = 1;
    }

    QFile outFile(QApplication::applicationDirPath() + "/log/"+ current_date +".txt");
    outFile.open(QIODevice::WriteOnly|QIODevice::Append);
    QTextStream ts(&outFile);
    ts << txt << endl;
#endif

#endif
}
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qInstallMessageHandler(customMessageHandler);

    QString qssFileName = ":/new/image/toolboxElement.qss";
    QString qss;
    QFile qssFile(qssFileName);
    qssFile.open(QFile::ReadOnly);
    if(qssFile.isOpen()){
        qss = QLatin1String(qssFile.readAll());
        qApp->setStyleSheet(qss);
        qssFile.close();
    }
//    static QTranslator* translator = new QTranslator;
//    QString runPath = QApplication::applicationDirPath();
//    QString qmFilename = runPath + "/translations/ToolBox_zh_CN.qm";

//    if (translator->load(qmFilename)){
//        qApp->installTranslator(translator);
//    }
    ToolBox w;
    w.show();
    return a.exec();
}
