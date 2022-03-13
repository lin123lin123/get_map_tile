#include "map_preview.h"
#include"QDebug"
#include <QQuickView>
map_preview *p1;
map_preview::map_preview()
{
  p1=this;

}

void map_preview::map_load()
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    #endif
      engine.rootContext()->setContextProperty("mainwidget",this);
       const QUrl url(QStringLiteral("qrc:/main.qml"));
       engine.load(url);
       if (engine.rootObjects().isEmpty())
       {  //qDebug()<<"load error";
           qDebug()<<"qml load erro";
           return;
        }



}



void map_preview::show_map_slot(int control)
{
   // qDebug()<<"show_map_slot";
    emit show_map(control);
}

void map_preview::send_gps_slot(double lon, double lat, int zoom)
{
   //  qDebug()<<"send_gps_slot";
    emit send_gps(lon,lat,zoom);
}
