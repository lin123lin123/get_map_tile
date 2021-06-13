#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<qmath.h>
MainWindow *p=NULL;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    p=this;
    ui->setupUi(this);
    Thread_loop=new thread_loop(this);
   init_connection();

}

MainWindow::~MainWindow()
{
    Thread_loop->quit();
    Thread_loop->wait();
    delete ui;
}

bool MainWindow::get_tile(double lon, double lat, int zoom)
{
    int x;
    x=long2tilex(lon,zoom);
    qDebug()<<x;
    int y;
   y= lat2tiley(lat,zoom);
   qDebug()<<y;

    QString str_zoom=QString::number(zoom);
    QString str_x=QString::number(x);
    QString str_y=QString::number(y);
   QString url="http://tile.openstreetmap.org/@/#/$.png";
   url=url.replace("@",str_zoom);
    url=url.replace("#",str_x);
     url=url.replace("$",str_y);
     qDebug()<<"url="<<url;
   QString file_name="f:/map/osm_100-l-1-@-#-$.png";
   file_name=file_name.replace("@",str_zoom);
    file_name=file_name.replace("#",str_x);
     file_name=file_name.replace("$",str_y);
       qDebug()<<"file_name="<<file_name;
       if(pre_url==url)
         {
           finish_down_png=true;
           qDebug()<<"posion is same return;";
           return false;

       }
       else if(http_list.contains(url))
       {
           finish_down_png=true;
           qDebug()<<"http cmd hava this http;";
           return false;

       }
        else{
           pre_url=url;
            qDebug()<<"start down_load;";
            http_list.append(url);
            QFile F(file_name);
            if(F.exists())
            {
                finish_down_png=true;
                 qDebug()<<"file exist;"+file_name;
                return false;
            }else
            {
          http_pro.start_down_load(url,file_name);
          cmd_cuurrent=url;
           return true;
            }
       }


}

void MainWindow::init_connection()
{
    connect(&http_pro, SIGNAL(finish_down_load()),this,SLOT(finish_down_load_slot()));
     connect(&http_pro, SIGNAL(transport_error()),this,SLOT(transport_error_slot()));
    connect(Thread_loop, SIGNAL(poll_loop()),this,SLOT(poll_loop_slot()));
    connect(this, SIGNAL(write_log(QString)),this,SLOT(write_log_slot(QString)));
}

void MainWindow::write_log_slot(QString log)
{
    QFile file("f:/log/erro.log");
    if(file.open(QIODevice::WriteOnly|QIODevice::Append|QIODevice::Text))
    {
        QString log_tmp = QDateTime::currentDateTime().toString("hh:mm:ss")+log+"\n";
        file.write(log_tmp.toUtf8());
        file.flush();
        file.close();
    }
}

void MainWindow::transport_error_slot()
{
    emit write_log("transpor error"+cmd_cuurrent);
    http_repeat=0;
    finish_down_png=true;
}

void MainWindow::poll_loop_slot()
{

      if(http_repeat>5000)
      {
          emit write_log(cmd_cuurrent);
          http_repeat=0;
          finish_down_png=true;

      }

              if(!finish_down_png)
               {
                  qDebug()<<"while_return"<<lat_mix<<";"<<lon_mix;
                  http_repeat++;
                  return;
              }
           if(lat_mix<lat_max)
            {               
               if(lon_mix<lon_max)
               {
                   if( get_tile(lon_mix,lat_mix,zoom))
                    {
                       finish_down_png=false;

                    }
                   else {
                       if(zoom==10)
                       {
                       lon_mix=lon_mix+(1.0000/6.0000);
                       }
                       if(zoom==7)
                       {
                       lon_mix=lon_mix+1.0000;
                       }
                       qDebug()<<"get_tile false ;return"<<lat_mix<<";"<<lon_mix;
                       }
                    if(zoom==10)
                    {
                    lon_mix=lon_mix+(1.0000/6.0000);
                    }
                    if(zoom==7)
                    {
                    lon_mix=lon_mix+1.0000;
                    }
               }
               else
               {
                lon_mix= ui->textEdit_W->toPlainText().toDouble();
                 if(zoom==10)
                 {
                 lat_mix=lat_mix+(1.0000/6.0000);
                 }
                 if(zoom==7)
                 {
                 lat_mix=lat_mix+1.0000;
                 }

                }
            }
 }

int MainWindow::long2tilex(double lon, int z)
{
    return (int)(floor((lon + 180.0) / 360.0 * (1 << z)));
}

int MainWindow::lat2tiley(double lat, int z)
{
    double latrad = lat * M_PI/180.0;
    return (int)(floor((1.0 - asinh(tan(latrad)) / M_PI) / 2.0 * (1 << z)));
}


void MainWindow::on_pushButton_clicked()
{


qDebug()<<"on_pushButton_clicked";
   lat_max= ui->textEdit_N->toPlainText().toDouble();
   lat_mix= ui->textEdit_S->toPlainText().toDouble();
   lon_max= ui->textEdit_E->toPlainText().toDouble();
   lon_mix= ui->textEdit_W->toPlainText().toDouble();
   zoom= ui->textEdit_zoom->toPlainText().toInt();
    is_start=true;
   Thread_loop->start();

}
void MainWindow::finish_down_load_slot()
{

     http_pro.stop_down_load();
     http_repeat=0;
      finish_down_png=true;

}
void MainWindow::delaymsec(int msec)
{
    QTime delayTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < delayTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void MainWindow::on_pushButton_3_clicked()
{
    is_start=false;
    finish_down_png=true;
    http_list.clear();
}
