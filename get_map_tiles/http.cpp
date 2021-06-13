#include "http.h"

http::http()
{
    accessManager = new QNetworkAccessManager(this);
}
void http::start_down_load(QString url,QString path)
{
 //   file =new QFile(dir.path()+"/update/"+file_name);
  accessManager->setNetworkAccessible(QNetworkAccessManager::Accessible);
   QUrl Url(url);
   QNetworkRequest request(Url);
   request.setHeader(QNetworkRequest::ContentTypeHeader, "application/octet-stream");
    request.setHeader(QNetworkRequest::UserAgentHeader, "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:89.0) Gecko/20100101 Firefox/89.0");
   QString strRange = QString("bytes=%1-").arg(m_bytesCurrentReceived);
    request.setRawHeader("Range", strRange.toLatin1());
   file =new QFile(path);
            if(!file->open(QIODevice::ReadWrite|QIODevice::Append)){}
   reply = accessManager->get(request);
    connect((QObject *)reply, SIGNAL(readyRead()), this, SLOT(readContent()));
    connect(reply, SIGNAL(downloadProgress(qint64 ,qint64)), this, SLOT(loadProgress(qint64 ,qint64)));
    connect(accessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),this,SLOT(loadError(QNetworkReply::NetworkError)));
   }

void http::loadProgress(qint64 bytesSent, qint64 bytesTotal)
 {
 qDebug()<<"3333333333333333333";
   progess=bytesSent;
    qDebug()<<progess;
 }
void http::readContent()
{
  file->write(reply->readAll());
  m_bytesCurrentReceived=file->size();

}
void http::replyFinished(QNetworkReply*)
{
    file->flush(); file->close();
    file->deleteLater();
    file=NULL;
    m_bytesCurrentReceived=0;
    if(reply->error() == QNetworkReply::NoError)
    {
        qDebug()<<"finiseh upload";
        emit finish_down_load();
    }

    else
    {

    }


}
void http::loadError(QNetworkReply::NetworkError)    //传输中的错误输出
{
    #ifdef debug_lin
      qDebug()<<"transport erro="<<QString::number(reply->error());
      #endif
 qDebug()<<"transport erro="<<QString::number(reply->error());
 disconnect((QObject *)reply, SIGNAL(readyRead()), this, SLOT(readContent()));
 disconnect(reply, SIGNAL(downloadProgress(qint64 ,qint64)), this, SLOT(loadProgress(qint64 ,qint64)));
disconnect(accessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
disconnect(reply, SIGNAL(error(QNetworkReply::NetworkError)),this,SLOT(loadError(QNetworkReply::NetworkError)));
 reply->abort();
 reply->deleteLater();
 reply = NULL;
  file->flush(); file->close();
  file->deleteLater();
  file=NULL;
  delaymsec(1000);
   m_bytesCurrentReceived=0;
   emit transport_error();

}

void http::delaymsec(int msec)
{
    QTime delayTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < delayTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void http::stop_down_load()
{
    disconnect((QObject *)reply, SIGNAL(readyRead()), this, SLOT(readContent()));
    disconnect(reply, SIGNAL(downloadProgress(qint64 ,qint64)), this, SLOT(loadProgress(qint64 ,qint64)));
   disconnect(accessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
   disconnect(reply, SIGNAL(error(QNetworkReply::NetworkError)),this,SLOT(loadError(QNetworkReply::NetworkError)));
    reply->abort();
    reply->deleteLater();
    reply = NULL;

}
