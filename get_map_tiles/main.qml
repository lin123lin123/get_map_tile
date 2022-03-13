import QtQuick 2.9
import QtQuick.Window 2.12
import QtPositioning 5.5
import QtLocation 5.6
import QtGraphicalEffects 1.0
import lin.com 1.1
Window {
    x:0
    y:0
    width:1000
    height:300
   id:mainwindow

 signal send_gps_to_map(int lat,int lon,int zoom)
   visible: true
   Map_pro
   {

       id:map_load
       x:0
       y:0
       width:1000
       height:300
       visible: false;

   }
     Connections{
         target: mainwidget
         onShow_map:
         {
               console.log("onShow_map");
             if(control)
             {
                 map_load.visible=true;
                console.log("loding map");

             }else
             {
                  map_load.visible=false;
                 console.log("remove  map");
             }
         }
         onSend_gps:
         {
             map_load.lat_1=lat;
             map_load.lon_1=lon;
             map_load.zoom_1=zoom;
         }
     }

}
