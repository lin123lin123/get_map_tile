#include "log_thread.h"
#include"mainwindow.h"
extern MainWindow *p;
log_thread::log_thread()
{
 file.setFileName("f:/log/erro.log");
}

void log_thread::run()
{
    while(true)
    {
       if(log_list.size())
       {
        if(file.open(QIODevice::WriteOnly|QIODevice::Append|QIODevice::Text))
        {

            QString tmp=log_list.takeFirst();

            file.write(tmp.toUtf8());
            file.flush();
            file.close();
        }
        delaymsec(10);
      //  qDebug()<<"log_thread::run()----------";
       }
    }

}
void log_thread::delaymsec(int msec)
{
    QTime delayTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < delayTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void log_thread::log_thread_slot(QString info)
{

    log_list.append(info);

}
