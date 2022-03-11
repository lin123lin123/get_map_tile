#include "http.h"
#include"mainwindow.h"
extern MainWindow *p;
http::http()
{
    accessManager = new QNetworkAccessManager(this);
}
bool http::start_down_load(QString url,QString path,QString qt_path)
{
 //   file =new QFile(dir.path()+"/update/"+file_name);
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
       else
       {          
       if(!file->open(QIODevice::ReadWrite|QIODevice::Append)){
        emit write_log("open file error,file name="+path);         
           return false;
       }
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
        else
        {           
            if(!qt_file->open(QIODevice::ReadWrite|QIODevice::Append)){
                emit write_log("open file error,qt_file name="+qt_path);              
                return false;
            }
        }
    }
  accessManager->setNetworkAccessible(QNetworkAccessManager::Accessible);
   QUrl Url(url);
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
    return true;
   }

void http::loadProgress(qint64 bytesSent, qint64 bytesTotal)
 {
 qDebug()<<"3333333333333333333";
   progess=bytesSent;
    qDebug()<<progess;
     // emit write_log("loadProgress---file_name="+file->fileName()+";progess="+QString::number(progess)
     //               +";bytesTotal="+QString::number(bytesTotal));
 }
void http::readContent()
{
    QByteArray tmp=reply->readAll();
    if(file!=NULL)
    {
     file->write(tmp);
      m_bytesCurrentReceived=file->size();
    }
    if(qt_file!=NULL)
    {
     qt_file->write(tmp);
      m_bytesCurrentReceived=qt_file->size();
    }


}
void http::replyFinished(QNetworkReply*)
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
    if(reply->error() == QNetworkReply::NoError)
    {          
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
  if(reply->error() == QNetworkReply::NoError)
  {
       emit finish_down_load();
  }
  else{
 disconnect((QObject *)reply, SIGNAL(readyRead()), this, SLOT(readContent()));
 disconnect(reply, SIGNAL(downloadProgress(qint64 ,qint64)), this, SLOT(loadProgress(qint64 ,qint64)));
disconnect(accessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
disconnect(reply, SIGNAL(error(QNetworkReply::NetworkError)),this,SLOT(loadError(QNetworkReply::NetworkError)));
// reply->abort();
 if(reply!=NULL)
 {
 reply->deleteLater();
 reply = NULL;
 }
 if(file!=NULL)
 {
  file->flush();
  file->close();
  file->deleteLater();
  file=NULL;
 }
 if(qt_file!=NULL)
 {
  qt_file->flush();
  qt_file->close();
  qt_file->deleteLater();
  qt_file=NULL;
 } 
   m_bytesCurrentReceived=0;
   emit transport_error();

}
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
   if(reply!=NULL)
   {
   reply->abort();
    reply->deleteLater();
    reply = NULL;   
   }
}
