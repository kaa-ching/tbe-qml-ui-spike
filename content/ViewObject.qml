import QtQuick 2.0
import TBEView 1.0

Image {
    id: viewObject
    source: "qrc:/images/used_wood_bar.png"
    width: 200
    height: 80
    x: 120
    y: 130

    // the is* properties are updated by the ViewItem
    property bool isHResize : false
    property bool isVResize : false
    property bool isRotate  : false
    property bool isColliding : false

    ViewItem {
        id: theVI
        objectName: "theVI"
    }

    MouseArea {
        objectName: "theMA"
        anchors.fill: parent
        drag{
            target: parent
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
