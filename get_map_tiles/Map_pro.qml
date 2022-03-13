import QtQuick 2.9
import QtQuick.Window 2.12
import QtPositioning 5.5
import QtLocation 5.6
import QtGraphicalEffects 1.0
Item {
    id:main_map
    property  int lat_1: 0
    property  int lon_1: 0
     property  int zoom_1: 0
   Plugin{
        id:mapPlugin
        name:"osm"
        PluginParameter { name: "osm.mapping.offline.directory"; value: "f:/map"}


    }

   Map{

       id:map
       x:0
        y:0
        width:1000
        height:300
        z:0
        visible: true
        //  anchors.fill:parent
       plugin:mapPlugin
       center:QtPositioning.coordinate(lat_1, lon_1)
       zoomLevel: zoom_1
       PositionSource {
             id: positionSource

         }
       MapCircle{
           id:red_hot
           center:QtPositioning.coordinate(lat_1, lon_1)
           radius:(5000/zoom_1)
           color:"red"
           visible: true
       }


   }


}
