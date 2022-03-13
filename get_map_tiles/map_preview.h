#ifndef MAP_PREVIEW_H
#define MAP_PREVIEW_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include<QThread>
class map_preview : public QObject
{

     Q_OBJECT
public:
    map_preview();
    void map_load();
    QQmlApplicationEngine engine;
signals:
    void show_map(int control);
    void send_gps(double lon,double lat,int zoom);
public slots:
    void show_map_slot(int control);
    void send_gps_slot(double lon,double lat,int zoom);

};

#endif // MAP_PREVIEW_H
