#include "http_c.h"
#include"mainwindow.h"
extern MainWindow *p;
http_c::http_c()
{   
    qt_name.clear();
    android_name.clear();
    url_list.clear();
}
bool http_c::start_down_load(QString url,QString path,QString qt_path)
{
    if(path!="")
    {
       file =new QFile(path);
       if(file->exists())
       {
           file->deleteLater();
           file=NULL;
           qDebug()<<"file---"<<path<<"exist";
           return false;
       }
    }
    if(qt_path!="")
    {
        qt_file=new QFile(qt_path);
        if(qt_file->exists())
        {
            qt_file->deleteLater();
            qt_file=NULL;
             qDebug()<<"qt_file---"<<qt_file<<"exist";
            return false;
        }
    }
    url_list.append(url);
    return true;

   }

void http_c::loadProgress(qint64 bytesSent, qint64 bytesTotal)
 {
 qDebug()<<"3333333333333333333";
   progess=bytesSent;
   qDebug()<<"c--progess"<<progess;
    qDebug()<<"c--bytesTotal"<<bytesTotal;
     // emit write_log("loadProgress---file_name="+file->fileName()+";progess="+QString::number(progess)
     //               +";bytesTotal="+QString::number(bytesTotal));
 }
void http_c::readContent()
{
    QByteArray tmp=reply->readAll();
    buffer+=tmp;


}
void http_c::replyFinished(QNetworkReply*)
{
    if(file->open(QIODevice::ReadWrite|QIODevice::Append)){
      file->write(buffer);
       file->flush();
       file->close();
     }
    if(qt_file->open(QIODevice::ReadWrite|QIODevice::Append)){
      qt_file->write(buffer);
       qt_file->flush();
       qt_file->close();
     }

  if(file!=NULL)
  {

  file->deleteLater();
  file=NULL;
  }
  if(qt_file!=NULL)
  {
  qt_file->deleteLater();
  qt_file=NULL;
  }
  m_bytesCurrentReceived=0;
  buffer.clear();
  if(accessManager!=NULL)
  {
       accessManager->deleteLater();
       accessManager = NULL;
  }
  if(reply->error() == QNetworkReply::NoError)
  {
      if(reply!=NULL)
      {
      reply->abort();
       reply->deleteLater();
       reply = NULL;
      }
  }

  else
  {
      reply->deleteLater();
      reply = NULL;
  }
  emit finish_down_load();


}
void http_c::loadError(QNetworkReply::NetworkError)    //传输中的错误输出
{
    if(file!=NULL)
    {
    file->flush(); file->close();
    file->deleteLater();
    file=NULL;
    }
    if(qt_file!=NULL)
    {
    qt_file->flush(); qt_file->close();
    qt_file->deleteLater();
    qt_file=NULL;
    }
    m_bytesCurrentReceived=0;
    buffer.clear();
    if(accessManager!=NULL)
    {
         accessManager->deleteLater();
         accessManager = NULL;
    }
    if(reply->error() == QNetworkReply::NoError)
    {
        if(reply!=NULL)
        {
        reply->abort();
         reply->deleteLater();
         reply = NULL;
        }
    }

    else
    {
        reply->deleteLater();
        reply = NULL;
    }
   m_bytesCurrentReceived=0;
   emit transport_error();
}

void http_c::delaymsec(int msec)
{
    QTime delayTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < delayTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void http_c::stop_down_load()
{
   if(reply!=NULL)
   {
   reply->abort();
    reply->deleteLater();
    reply = NULL;   
   }
   if(accessManager!=NULL)
   {
        accessManager->deleteLater();
        accessManager = NULL;
   }
}

void http_c::run()
{

    while(true)
  {
    if(url_list.size()>0)
    {
    accessManager = new QNetworkAccessManager();
    accessManager->setNetworkAccessible(QNetworkAccessManager::Accessible);
    QUrl Url(url_list.takeFirst());
    QNetworkRequest request(Url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/octet-stream");
     request.setHeader(QNetworkRequest::UserAgentHeader, "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:89.0) Gecko/20100101 Firefox/89.0");
   QString strRange = QString("bytes=%1-").arg(m_bytesCurrentReceived);
   request.setRawHeader("Range", strRange.toLatin1());
    reply = accessManager->get(request);
    connect((QObject *)reply, SIGNAL(readyRead()), this, SLOT(readContent()));
    connect(reply, SIGNAL(downloadProgress(qint64 ,qint64)), this, SLOT(loadProgress(qint64 ,qint64)));
    connect(accessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),this,SLOT(loadError(QNetworkReply::NetworkError)));
   }
  // qDebug()<<QDateTime::currentDateTime()<<"0------------";
   delaymsec(50);
    }

}
