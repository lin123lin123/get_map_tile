#ifndef LOG_THREAD_H
#define LOG_THREAD_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include<QThread>
#include<QMutex>
#include<QFile>
#include<QTime>
#include<QCoreApplication>
#include<QEvent>
class log_thread  :public QThread
{
     Q_OBJECT
public:
    log_thread();
   virtual void  run();
    void delaymsec(int msec);
     QStringList log_list;
     QFile file;
private:
       QMutex lock;


public slots:
   void  log_thread_slot(QString info);

};

#endif // LOG_THREAD_H
