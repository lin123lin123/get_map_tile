#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QDebug>
#include<QStringList>
#include"thread_loop.h"
#include"http.h"
#include<map_preview.h>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include"rec_qmldata.h"
#include"log_thread.h"
#include<QList>
//#define M_PI 3.14159265358979323846
#define andriod
typedef struct
{
    int x;
    int y;
    int z;

}title_code;



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int long2tilex(double lon, int z);
    int lat2tiley(double lat, int z);
    bool get_tile(double lon,double lat,int zoom);
    http  http_pro;
    thread_loop *Thread_loop;
    bool is_start=false;   
    log_thread Log_thread;
    quint16 http_repeat=0;
    bool finish_down_png=true;

private:
    double lat_max=0;
    double lat_mix= 0;
    double lon_max= 0;
    double lon_mix= 0;
    int x_pre=0;
    int y_pre=0;
    int z_pre=0;
    int zoom=0;
    QList<int> zoom_list;
   QString pre_url="";

    QStringList http_list;

    QString cmd_cuurrent;
    void init_connection();
     void delaymsec(int msec);
    map_preview * Map=NULL;
    QQmlApplicationEngine engine;
    rec_qmldata  qml_data;   
      QString file_name="";
     QString qt_file_name="";
      bool qt_select=true;
      bool android_select=true;
      bool read_pause_info();
      void write_pause_info();
      bool read_pause_info_config();
      void write_pause_info_config();

signals:
    void write_log(QString log);
    void close_map();
    void send_log(QString);


private slots:
    void on_pushButton_clicked();
    void finish_down_load_slot();

    void on_pushButton_3_clicked();
     void poll_loop_slot();
     void write_log_slot(QString log);
     void transport_error_slot();


     void on_pushButton_4_clicked();

     void on_pushButton_5_clicked();
     void close_map_slot();

     void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;


};
#endif // MAINWINDOW_H
