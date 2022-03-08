#include "thread_loop.h"
#include"mainwindow.h"
extern MainWindow *p;
thread_loop::thread_loop(QObject *parent)
{

}

void thread_loop::myThreadSlot(const int)
{

}

void thread_loop::run()
{
    while(p->is_start)
    {

        emit poll_loop();
         delaymsec(10);
    //     qDebug()<<"thread_loop::run()--------------";
    }

}

void thread_loop::delaymsec(int msec)
{
    QTime delayTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < delayTime)
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}


