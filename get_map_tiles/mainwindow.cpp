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
   init_connection();

}

MainWindow::~MainWindow()
{
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
          http_pro.start_down_load(url,file_name);
           return true;
       }


}

void MainWindow::init_connection()
{
    connect(&http_pro, SIGNAL(finish_down_load()),this,SLOT(finish_down_load_slot()));
     connect(&Thread_loop, SIGNAL(poll_loop()),this,SLOT(poll_loop_slot()));
}

void MainWindow::poll_loop_slot()
{

              if(!finish_down_png)
               {
                  qDebug()<<"while_return"<<lat_mix<<";"<<lon_mix;
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
                       lon_mix=lon_mix+(1.0000/60.0000);
                       qDebug()<<"get_tile false ;return"<<lat_mix<<";"<<lon_mix;
                       }
                    lon_mix=lon_mix+(1.0000/60.0000);
               }
               else
               {
                lon_mix= ui->textEdit_W->toPlainText().toDouble();
                 lat_mix=lat_mix+(1.0000/60.0000);

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
   Thread_loop.start();

}
void MainWindow::finish_down_load_slot()
{
    finish_down_png=true;
     http_pro.stop_down_load();

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
    http_list.clear();
}
