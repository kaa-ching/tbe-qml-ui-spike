import QtQuick 2.0
import TBEView 1.0

Image {
    id: viewObject
    source: "qrc:/images/used_wood_bar.png"
    width: 200
    height: 80
    x: 120
    y: 130

    property bool isHResize : false
    property bool isVResize : false
    property bool isRotate  : false

    ViewItem {
        // nothing needed here?
        id: theVI
        objectName: "theVI"

        Binding { target: parent; property: "isHResize"; value: theVI.isHResize }
        Binding { target: viewObject; property: "isVResize"; value: theVI.isVResize }
        Binding { target: viewObject; property: "isRotate";  value: theVI.isRotate }
    }

    MouseArea {
        objectName: "theMA"
        anchors.fill: parent
        drag{
            target: parent
            minimumX: 0
            minimumY: 0
            maximumX: theScene.width/theScale - parent.width
            maximumY: theScene.height/theScale - parent.height
            smoothed: true
        }
        onPressed: {
            if(selection)
                if (selection.theDecorated != parent) {
                    selection.destroy();
                    selection = undefined
                }
            if(!selection) {
                var component = Qt.createComponent("qrc:/content/ResizeRotate.qml");
                if (component.status == Component.Ready) {
                    selection = component.createObject(theScene, {
                                                           "theDecorated": parent,
                                                           "x": parent.x,
                                                           "y": parent.y,
                                                           "rotationAngle": parent.rotation,
                                                           "width": parent.width,
                                                           "height": parent.height})
                }
            }
        }
    }
}
