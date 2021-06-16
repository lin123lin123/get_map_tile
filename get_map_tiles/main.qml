import QtQuick 2.9
import QtQuick.Window 2.9
import QtPositioning 5.5
import QtLocation 5.6
import QtGraphicalEffects 1.0
import lin.com 1.1
Window {
    width: 1920
    height: 1080
    visible: true
    title: qsTr("Hello World")
     id:main_map
    Plugin{
        id:mapPlugin
        name:"osm"
        PluginParameter { name: "osm.mapping.offline.directory"; value: "f:/map"}


    }

   Map{

       id:map
       x:0
        y:0
        width:1920
        height:1080
        z:0
        visible: true
        //  anchors.fill:parent
       plugin:mapPlugin
       center:QtPositioning.coordinate(41.22, 60.21)
       zoomLevel: 10
       PositionSource {
             id: positionSource

         }
       MapCircle{
           id:red_hot
           center:QtPositioning.coordinate(41.22, 60.21)
           radius:500
           color:"red"
           visible: true
       }


   }
     Lin_mode{
        id:data_to_control_widget

     }
     Rectangle
     {
         x:0
          y:0
          width:40
          height:20
          z:1
          id:rec
          Text {
              x:0
              y:0
              width:40
              height:20
              visible: true
              id: name
              color: "red"
              text: qsTr("Return")
              signal return_opration(int msg)
          }
          MouseArea
          {
              x:0
              y:0
              width:40
              height:20
              onClicked:
              {
               name.return_opration.connect(data_to_control_widget.rec_operation_slot)
                emit: name.return_opration(1);
                   main_map.close();
              }
          }

     }

     Connections{
         target: mainwidget
         onClose_map:
         {
             main_map.close();
         }
     }

}
