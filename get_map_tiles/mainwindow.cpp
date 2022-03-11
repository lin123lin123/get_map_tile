#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<qmath.h>
#include <stdio.h>
#include<QDir>
#include<QMessageBox>
MainWindow *p=NULL;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    p=this;
    ui->setupUi(this);
    Thread_loop=new thread_loop(this);
    qmlRegisterType<rec_qmldata>("lin.com",1,1,"Lin_mode");
    Log_thread.start();
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
    //    // emit write_log("get_tile---x="+QString::number(x));
    int y;
    y= lat2tiley(lat,zoom);
    qDebug()<<y;
    //   // emit write_log("get_tile---y="+QString::number(y));

    QString str_zoom=QString::number(zoom);
    QString str_x=QString::number(x);
    QString str_y=QString::number(y);
    QString url="http://tile.openstreetmap.org/@/#/$.png";
    url=url.replace("@",str_zoom);
    url=url.replace("#",str_x);
    url=url.replace("$",str_y);
    qDebug()<<"url="<<url;
    //     // emit write_log("get_tile---url:"+url);
    if(android_select)
    {
        QDir *folder = new QDir();
        QString t1="f:/map/"+str_zoom;
        if(folder->exists(t1))
        {
            QDir *folder1 = new QDir();
            QString t2="f:/map/"+str_zoom+"/"+str_x;
            //   // emit write_log("get_tile---t1 exist="+t1);
            if(folder1->exists(t2))
            {
                file_name="f:/map/"+str_zoom+"/"+str_x+"/"+str_y+".png";
                qDebug()<<"1"<<file_name;
                //         // emit write_log("get_tile---t2 exist="+file_name);
//                QFile f(file_name);
//                if(f.exists())
//                {
//                    return false;
//                }
            }
            else
            {
                folder->mkdir(t2);
                file_name="f:/map/"+str_zoom+"/"+str_x+"/"+str_y+".png";
                qDebug()<<"2"<<file_name;
                //       // emit write_log("get_tile---t2 not exist="+file_name);
//                QFile f(file_name);
//                if(f.exists())
//                {
//                    return false;
//                }
            }
        }
        else {
            folder->mkdir(t1);
            QDir *folder1 = new QDir();
            QString t2="f:/map/"+str_zoom+"/"+str_x;
            //     // emit write_log("get_tile---t1 not exist="+t1);
            if(folder1->exists(t2))
            {
                file_name="f:/map/"+str_zoom+"/"+str_x+"/"+str_y+".png";
                qDebug()<<"3"<<file_name;
                //           // emit write_log("get_tile---t2 exist="+file_name);
                QFile f(file_name);
//                if(f.exists())
//                {
//                    return false;
//                }
            }
            else
            {
                folder->mkdir(t2);
                file_name="f:/map/"+str_zoom+"/"+str_x+"/"+str_y+".png";
                qDebug()<<"4"<<file_name;
                //              // emit write_log("get_tile---t2 not exist="+file_name);
                QFile f(file_name);
//                if(f.exists())
//                {
//                    return false;
//                }
            }
        }
    }
    if(qt_select)
    {
        qt_file_name="f:/map/osm_100-l-1-@-#-$.png";
        qt_file_name=qt_file_name.replace("@",str_zoom);
        qt_file_name=qt_file_name.replace("#",str_x);
        qt_file_name=qt_file_name.replace("$",str_y);
        qDebug()<<"qt_file_name="<<qt_file_name;
    }
    if(pre_url==url)
    {
        finish_down_png=true;
        qDebug()<<"posion is same return;";
        // emit write_log("get_tile---posion is same return;file name="+file_name);
        return false;

    }
    else if(http_list.contains(url))
    {
        finish_down_png=true;
        qDebug()<<"http cmd hava this http;";
        // emit write_log("http cmd hava this http,file name="+file_name);
        return false;

    }
    else{
        pre_url=url;
        qDebug()<<"start down_load;";
        // emit write_log("start down_load;file_name="+file_name);
        http_list.append(url);
       if(http_pro.start_down_load(url,file_name,qt_file_name))
       {
           cmd_cuurrent=url;
          return true;
        }else
       {
             cmd_cuurrent=url;
            return false;
       }
    }


}

void MainWindow::init_connection()
{
    connect(&http_pro, SIGNAL(finish_down_load()),this,SLOT(finish_down_load_slot()));
    connect(&http_pro, SIGNAL(transport_error()),this,SLOT(transport_error_slot()));
    connect(Thread_loop, SIGNAL(poll_loop()),this,SLOT(poll_loop_slot()));
    connect(this, SIGNAL(write_log(QString)),this,SLOT(write_log_slot(QString)));
    connect(this, SIGNAL(send_log(QString)),&Log_thread,SLOT(log_thread_slot(QString)));
    connect(&http_pro, SIGNAL(write_log(QString)),this,SLOT(write_log_slot(QString)));
    connect(&qml_data, SIGNAL(close_map()),this,SLOT(close_map_slot()));
}

void MainWindow::write_log_slot(QString log)
{
    QString log_tmp = QDateTime::currentDateTime().toString("hh:mm:ss")+log+"\n";
    //  log_list.append(log_tmp);
    emit send_log(log_tmp);
    //  qDebug()<<"write_log_slot"<<log_tmp;
}

void MainWindow::transport_error_slot()
{
    emit write_log("transpor error"+cmd_cuurrent+"file_name=="+file_name);
    //   http_pro.stop_down_load();
    http_repeat=0;
    finish_down_png=true;
}

void MainWindow::poll_loop_slot()
{ 
    if(http_repeat>300)
    {
        // emit write_log(cmd_cuurrent);
        http_pro.stop_down_load();
        http_repeat=0;
        finish_down_png=true;


    }

    if(!finish_down_png)
    {
       // qDebug()<<"while_return"<<lat_mix<<";"<<lon_mix;
        //     // emit write_log("while_return"+QString::number(lat_mix,'f',2)+";"+QString::number(lon_mix,'f',2));
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
                qDebug()<<"get_tile false ;return"<<lat_mix<<";"<<lon_mix;
                // emit write_log("get_tile false ;return"+QString::number(lat_mix,'f',2)+";"+QString::number(lon_mix,'f',2));
            }
            if(zoom==15)
            {
                lon_mix=lon_mix+(1.0000/60.0000);
            }
            else if(zoom==14)
            {
                lon_mix=lon_mix+(1.0000/60.0000);
            }
            else if(zoom==13)
            {
                lon_mix=lon_mix+(1.0000/60.0000);
            }
            else if(zoom==12)
            {
                lon_mix=lon_mix+(1.0000/30.0000);
            }
            else if(zoom==11)
            {
                lon_mix=lon_mix+(1.0000/12.0000);
            }
            else  if(zoom==10)
            {
                lon_mix=lon_mix+(1.0000/6.0000);
            }
            else  if(zoom==9)
            {
                lon_mix=lon_mix+(1.0000/3.0000);
            }
            else  if(zoom==8)
            {
                lon_mix=lon_mix+(1.0000/2.0000);
            }
            else if(zoom==7)
            {
                lon_mix=lon_mix+1.0000;
            }
            else if(zoom==6)
            {
                lon_mix=lon_mix+1.0000;
            }else
            {
                lon_mix=lon_mix+1.0000;
            }
            ui->log_process->setValue(lon_mix);
        }
        else
        {
            lon_mix= ui->textEdit_W->toPlainText().toDouble();
            ui->log_process->setValue(lon_mix);
            if(zoom==15)
            {
                lat_mix=lat_mix+(1.0000/60.0000);
            }
            else if(zoom==14)
            {
                lat_mix=lat_mix+(1.0000/60.0000);
            }
            else if(zoom==13)
            {
                lat_mix=lat_mix+(1.0000/60.0000);
            }
            else if(zoom==12)
            {
                lat_mix=lat_mix+(1.0000/30.0000);
            }
            else if(zoom==11)
            {
                lat_mix=lat_mix+(1.0000/12.0000);
            }
            else if(zoom==10)
            {
                lat_mix=lat_mix+(1.0000/6.0000);
            }
            else if(zoom==9)
            {
                 lat_mix=lat_mix+(1.0000/3.0000);
            }
            else if(zoom==8)
            {
                lat_mix=lat_mix+(1.0000/2.0000);
            }
            else if(zoom==7)
            {
                lat_mix=lat_mix+1.0000;
            }
            else if(zoom==6)
            {
                lat_mix=lat_mix+1.0000;
            }else
            {
                lat_mix=lat_mix+1.0000;
            }
            ui->lat_process->setValue(lat_mix);
            write_pause_info();
        }
    }else
    {
        ui->lat_process->setValue(lat_max);
        if(zoom_list.size()>0)
        {    emit write_log("zoom="+QString::number(zoom)+"finished download");
            zoom=zoom_list.takeFirst();
            ui->current_zoom->setPlainText(QString::number(zoom));
            Log_thread.file.setFileName("f:/log/"+QString::number(zoom)+"erro.log");
            finish_down_png=true;
            lat_max= ui->textEdit_N->toPlainText().toDouble();
            lat_mix= ui->textEdit_S->toPlainText().toDouble();
            lon_max= ui->textEdit_E->toPlainText().toDouble();
            lon_mix= ui->textEdit_W->toPlainText().toDouble();
            http_list.clear();
            write_pause_info();
        }else
        {
            emit write_log("zoom="+QString::number(zoom)+"finished download");
            is_start=false;
            QFile f_del;
            f_del.remove("f:/log/pause");
            QFile f_del1;
            f_del1.remove("f:/log/pause1");
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

    if((!(ui->android->isChecked()))&&(!(ui->qt->isChecked())))
    {
        QMessageBox msgBox;
        msgBox.setText("please select qt or android map source ");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();
        return;
    }

    qDebug()<<"on_pushButton_clicked";
    if(read_pause_info())
    {
        if(read_pause_info_config())
        {

        }
        else
        {
            ui->textEdit_N->setPlainText(QString::number(lat_max));
            ui->textEdit_S->setPlainText(QString::number(lat_mix));
            ui->textEdit_E->setPlainText(QString::number(lon_max));
            ui->textEdit_W->setPlainText(QString::number(lon_mix));
        }
        ui->lat_process->setRange(ui->textEdit_S->toPlainText().toDouble(),ui->textEdit_N->toPlainText().toDouble());
        ui->lat_process->setValue(lat_mix);
        ui->log_process->setRange(ui->textEdit_W->toPlainText().toDouble(),ui->textEdit_E->toPlainText().toDouble());
        ui->log_process->setValue(lon_mix);
    }
    else{
        lat_max= ui->textEdit_N->toPlainText().toDouble();
        lat_mix= ui->textEdit_S->toPlainText().toDouble();
        lon_max= ui->textEdit_E->toPlainText().toDouble();
        lon_mix= ui->textEdit_W->toPlainText().toDouble();
        write_pause_info_config();
        ui->lat_process->setRange(lat_mix,lat_max);
        ui->lat_process->setValue(lat_mix);
        ui->log_process->setRange(lon_mix,lon_max);
        ui->log_process->setValue(lon_mix);
        QString tmp_zoom= ui->textEdit_zoom->toPlainText();
        int  index=tmp_zoom.indexOf(":");
        qDebug()<<"tmp_zoom"<<tmp_zoom;
        qDebug()<<"index"<<index;
        if(!(index<0))
        {
            QStringList tmp_zoom_list=tmp_zoom.split(":");
            for(int i=0; i<tmp_zoom_list.size();i++)
            {
                QString str=tmp_zoom_list.at(i);
                zoom_list.append(str.toInt());
            }
        }else
        {
            zoom=tmp_zoom.toInt();
            if((zoom!=0x01)&&(zoom!=0x02)&&(zoom!=0x03)&&(zoom!=0x04)
                    &&(zoom!=0x05)&&(zoom!=0x06)&&(zoom!=0x07)&&(zoom!=0x08)
                    &&(zoom!=0x09)&&(zoom!=0x0a)&&(zoom!=0x0b)&&(zoom!=0x0c)
                    &&(zoom!=0x0d)&&(zoom!=0x0e)&&(zoom!=0x0f))
            {     QMessageBox msgBox;
                msgBox.setText("The zoom value error ");
                msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
                msgBox.setDefaultButton(QMessageBox::Save);
                int ret = msgBox.exec();
                return;
            }
        }
        if(zoom_list.size()>0)
        {
            zoom=zoom_list.takeFirst();
        }
    }


    is_start=true;
    Log_thread.file.setFileName("f:/log/"+QString::number(zoom)+"erro.log");
    if(ui->android->isChecked())
    {
        android_select=true;
        emit write_log("ndroid_select");
    }
    if(ui->qt->isChecked())
    {
        qt_select=true;
        emit write_log("qt_select");
    }
    ui->current_zoom->setPlainText(QString::number(zoom));
    if(!Thread_loop->isRunning())
    {
        Thread_loop->start();
    }
}
void MainWindow::finish_down_load_slot()
{

    http_pro.stop_down_load();
    http_repeat=0;
    finish_down_png=true;
    qDebug()<<"finish_down_load_slot";
    // emit write_log("finish_down_load:"+file_name);

}
void MainWindow::delaymsec(int msec)
{
    QTime delayTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < delayTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

bool MainWindow::read_pause_info()
{
    QFile f("f:/log/pause");
    if(f.exists())
    {
        if(f.open(QIODevice::ReadOnly))
        {
            QTextStream stream(&f);
            QString tmp_str;
            while (!stream.atEnd()) {
                tmp_str= stream.readLine();
            }
            f.flush();
            f.close();
            QStringList str_list=tmp_str.split(":");
            if(str_list.size()>4)
            {
                zoom_list.clear();
                for(int i=0;i<str_list.size();i++)
                {
                    QString str=str_list.at(i);
                    if(i==0)
                    {
                        lat_max=str.toFloat();
                    }
                    else if(i==1)
                    {
                        lat_mix=str.toFloat();
                    }
                    else if(i==2)
                    {
                        lon_max=str.toFloat();
                    }
                    else if(i==3)
                    {
                        lon_mix=str.toFloat();
                    }
                    else if(i==4)
                    {
                        zoom=str.toInt();
                    }else
                    {
                        zoom_list.append(str.toInt());
                    }
                }
                return true;

            }else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }else
    {
        return false;
    }
}

void MainWindow::write_pause_info()
{
    QFile pause("f:/log/pause");
    if(pause.open(QIODevice::WriteOnly|QIODevice::Text))
    {

        QString tmp=QString::number(lat_max,'f',4)+":"+QString::number(lat_mix,'f',4)+":"+QString::number(lon_max,'f',4)
                +":"+QString::number(lon_mix,'f',4)+":"+QString::number(zoom);
        for(int i=0;i<zoom_list.size();i++)
        {

            tmp+=":"+QString::number(zoom_list.at(i));
        }
        pause.write(tmp.toUtf8());
        pause.flush();
        pause.close();
    }

}

bool MainWindow::read_pause_info_config()
{
    QFile f("f:/log/pause1");
    if(f.exists())
    {
        if(f.open(QIODevice::ReadOnly))
        {
            QTextStream stream(&f);
            QString tmp_str;
            while (!stream.atEnd()) {
                tmp_str= stream.readLine();
            }
            f.flush();
            f.close();
            QStringList str_list=tmp_str.split(":");
            if(str_list.size()>3)
            {
                for(int i=0;i<str_list.size();i++)
                {
                    QString str=str_list.at(i);
                    if(i==0)
                    {
                        ui->textEdit_N->setPlainText(str);

                    }
                    else if(i==1)
                    {
                        ui->textEdit_S->setPlainText(str);
                    }
                    else if(i==2)
                    {
                        ui->textEdit_E->setPlainText(str);
                    }
                    else if(i==3)
                    {
                        ui->textEdit_W->setPlainText(str);
                    }

                }
                return true;

            }else
            {
                return false;
            }
        }
    }else
    {
        return false;
    }
}

void MainWindow::write_pause_info_config()
{
    QFile pause1("f:/log/pause1");
    if(pause1.open(QIODevice::WriteOnly|QIODevice::Text))
    {

        QString tmp=QString::number(lat_max,'f',4)+":"+QString::number(lat_mix,'f',4)+":"+QString::number(lon_max,'f',4)
                +":"+QString::number(lon_mix,'f',4);

        pause1.write(tmp.toUtf8());
        pause1.flush();
        pause1.close();
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    is_start=false;
    write_pause_info();
}

void MainWindow::on_pushButton_4_clicked()
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    engine.rootContext()->setContextProperty("mainwidget",this);
    engine.rootContext()->setContextProperty("qml_data",&qml_data);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    engine.load(url);
    this->close();
    if (engine.rootObjects().isEmpty())
    {  //qDebug()<<"load error";
        QDateTime tm=QDateTime::currentDateTime();
        qDebug()<<"qml load erro";
        return;
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    emit close_map();
}

void MainWindow::close_map_slot()
{
    qDebug()<<"close_map_slot";
    this->show();
}

void MainWindow::on_pushButton_2_clicked()
{   
    http_list.clear();
    zoom_list.clear();
    pre_url="";
    qt_select=false;
    android_select=false;
    ui->qt->setChecked(false);
    ui->android->setChecked(false);
    file_name="";
    qt_file_name="";
    ui->lat_process->setValue(lat_mix);
    ui->log_process->setValue(lon_mix);
    QFile f_del;
    f_del.remove("f:/log/pause");
    QFile f_del1;
    f_del1.remove("f:/log/pause1");
}
