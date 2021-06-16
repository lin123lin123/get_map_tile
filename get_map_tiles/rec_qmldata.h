#ifndef REC_QMLDATA_H
#define REC_QMLDATA_H
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include<QObject>
#include<QDebug>
#include<QQuickItem>
#include<QQuickView>

class rec_qmldata:public QObject
{

     Q_OBJECT
public:
    rec_qmldata();
    Q_PROPERTY(int operation READ getoperation WRITE setoperation NOTIFY operationChanged)
     int operation;
    int getoperation();
    Q_INVOKABLE  void setoperation(int adr);
signals:
    Q_INVOKABLE void operationChanged();
public slots:
    Q_INVOKABLE void  rec_operation_slot(int msg);
};

#endif // REC_QMLDATA_H
