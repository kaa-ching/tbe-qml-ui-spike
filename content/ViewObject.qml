import QtQuick 2.0

Image {
    id: floor1
    source: "qrc:/images/used_wood_bar.png"
    width: 200
    height: 80
    x: 120
    y: 130
    MouseArea {
        anchors.fill: parent
        drag{
            target: parent
            minimumX: 0
            minimumY: 0
            maximumX: theScene.width - parent.width
            maximumY: theScene.height - parent.height
            smoothed: true
        }
        onPressed: {
            if(selection)
                if (selection.theDecorated != parent) {
                    selection.destroy();
                    selection = null
                }
            if(!selection) {
                var component = Qt.createComponent("qrc:/content/MoveResizeRotate.qml");
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
