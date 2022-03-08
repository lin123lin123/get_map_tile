#ifndef HTTP_H
#define HTTP_H

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QUrl>
#include <QFile>
#include<QObject>
#include <QCoreApplication>
class http: public QObject
{
     Q_OBJECT
public:
    http();
   void start_down_load(QString url,QString path,QString qt_path);
   void delaymsec(int msec);
    void stop_down_load();
 private:
    QFile *file=NULL;
    QFile *qt_file=NULL;
    QNetworkReply *reply;
    quint64 m_bytesCurrentReceived=0;
    quint64 progess=0;
    QNetworkAccessManager *accessManager;
private slots:
    void replyFinished(QNetworkReply*);
    void loadError(QNetworkReply::NetworkError);
    void readContent();
    void loadProgress(qint64 bytesSent, qint64 bytesTotal);
 signals:
    void  finish_down_load();
    void  transport_error();
    void write_log(QString log);


};

#endif // HTTP_H
