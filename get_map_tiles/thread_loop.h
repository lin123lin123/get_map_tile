#ifndef THREAD_485_H
#define THREAD_485_H
#include<QThread>
#include<QTime>
#include<QCoreApplication>
#include<QEvent>


class thread_loop :public QThread
{
    Q_OBJECT
  public:
     thread_loop(QObject* parent = 0);
     void delaymsec(int msec);
  signals:
      void poll_loop();
  public slots:
      void myThreadSlot(const int);
  protected:
      void run();
};

#endif // THREAD_485_H
