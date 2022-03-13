#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QDebug>
#include<QStringList>
#include"thread_loop.h"
#include"http_a.h"
#include"http_b.h"
#include"http_c.h"
#include"http_d.h"
#include<map_preview.h>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include"rec_qmldata.h"
#include"log_thread.h"
#include"map_preview.h"
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
    bool get_tile(double lon,double lat,int zoom,int thread_index);
    http_a  http_pro_a;
    http_b  http_pro_b;
    http_c  http_pro_c;
    http_d  http_pro_d;
    thread_loop *Thread_loop;
    map_preview map_show;
    bool is_start=false;   
    log_thread Log_thread;
    quint16 http_repeat_a=0;
    bool finish_down_png_a=true;
    quint16 http_repeat_b=0;
    bool finish_down_png_b=true;
    quint16 http_repeat_c=0;
    bool finish_down_png_c=true;
    quint16 http_repeat_d=0;
    bool finish_down_png_d=true;

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
    void show_map(int control);
    void send_gps(double lon,double lat,int zoom);


private slots:
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();
     void poll_loop_slot();
     void write_log_slot(QString log);
     void transport_error_slot_b();
     void finish_down_load_slot_b();
     void transport_error_slot_a();
     void finish_down_load_slot_a();
     void transport_error_slot_c();
     void finish_down_load_slot_c();
     void transport_error_slot_d();
     void finish_down_load_slot_d();


     void on_pushButton_4_clicked();

     void on_pushButton_5_clicked();
     void close_map_slot();

     void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;


};
#endif // MAINWINDOW_H
