#ifndef HTTP_H_C
#define HTTP_H_C

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QUrl>
#include <QFile>
#include<QObject>
#include <QCoreApplication>
#include <QThread>
class http_c: public QThread
{
     Q_OBJECT
public:
    http_c();
   bool start_down_load(QString url,QString path,QString qt_path);
   void delaymsec(int msec);
    void stop_down_load();
 private:
    QFile *file=NULL;
    QFile *qt_file=NULL;
    QNetworkReply *reply=NULL;
    quint64 m_bytesCurrentReceived=0;
    quint64 progess=0;
    QNetworkAccessManager *accessManager;
    QByteArray buffer;
    QStringList qt_name;
    QStringList android_name;
    QStringList  url_list;
     virtual void  run();
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

#endif // HTTP_H_C
