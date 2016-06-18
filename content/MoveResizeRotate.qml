import QtQuick 2.4

Rectangle {
    id: selComp
    property int rulersSize: 22 // for Klaas' FullHD 24"
    property int minSize: 50
    property int rotationAngle: 0
    property Item theParent: null

    border {
        width: 1
        color: "black"
    }

    color: "#354682B4"
    rotation: rotationAngle

    Binding { target: floor1; property: "x"; value: selComp.x }
    Binding { target: floor1; property: "y"; value: selComp.y }
    Binding { target: floor1; property: "rotation"; value: rotationAngle }
    Binding { target: floor1; property: "width"; value: selComp.width }
    Binding { target: floor1; property: "height"; value: selComp.height }

    MouseArea {     // drag mouse area
        anchors.fill: parent
        drag{
            target: parent
            minimumX: 0
            minimumY: 0
            maximumX: parent.parent.width - parent.width
            maximumY: parent.parent.height - parent.height
            smoothed: true
        }
    }

    Image {
        // TODO/FIXME: I want to redo this to work like PowerPoint: move mouse at will, but always rotate in 15 degree steps
        id: rotateLeft
        width: rulersSize
        height: rulersSize
        anchors.horizontalCenter: parent.left
        anchors.verticalCenter: parent.top
        source: "qrc:/images/ActionRotateLeft.svg"

        MouseArea {
            anchors.fill: parent
            onClicked: {
                rotationAngle -= 15
            }
        }
    }

    Image {
        // TODO/FIXME: I hate the fact that I cannot use a tooltip to highlight the double clicking
        id: deleteItem
        width: rulersSize
        height: rulersSize
//                anchors.right: rotateLeft.left
        anchors.left: parent.right
        anchors.rightMargin: rulersSize / 2.0
//                anchors.verticalCenter: rotateLeft.verticalCenter
        anchors.top: parent.bottom
        source: "qrc:/images/ActionDelete.svg"

        MouseArea {
            anchors.fill: parent
            onDoubleClicked: {
                selComp.destroy()        // destroy component
            }
        }
    }

    Image {
        id: rotateright
        width: rulersSize
        height: rulersSize
        anchors.horizontalCenter: parent.right
        anchors.verticalCenter: parent.top
        source: "qrc:/images/ActionRotateLeft.svg"
        mirror: true

        MouseArea {
            anchors.fill: parent
            onClicked: {
                rotationAngle += 15
            }
        }
    }

    Image {
        id: left
        width: rulersSize
        height: rulersSize / 1.5
        anchors.horizontalCenter: parent.left
        anchors.verticalCenter: parent.verticalCenter
        source: "qrc:/images/ActionResizeHorizontally.svg"

        MouseArea {
            anchors.fill: parent
            drag{ target: parent; axis: Drag.XAxis}
            onMouseXChanged: {
                if(drag.active){
                    var myMouseX = mouseX
                    if (selComp.width - mouseX < minSize)
                        myMouseX = selComp.width - minSize
                    selComp.width -= myMouseX
                    selComp.x += myMouseX * (0.5 + 0.5 * Math.cos(rotationAngle/180*Math.PI))
                    selComp.y += myMouseX * 0.5 * Math.sin(rotationAngle/180*Math.PI)
                }
            }
        }
    }

    Image {
        id: right
        width: rulersSize
        height: rulersSize / 1.5
        anchors.horizontalCenter: parent.right
        anchors.verticalCenter: parent.verticalCenter
        source: "qrc:/images/ActionResizeHorizontally.svg"

        MouseArea {
            anchors.fill: parent
            drag{ target: parent; axis: Drag.XAxis }
            onMouseXChanged: {
                if(drag.active){
                    var myMouseX = mouseX
                    if (selComp.width + mouseX < minSize)
                        myMouseX = minSize - selComp.width
                    selComp.width += myMouseX
                    selComp.x -= myMouseX * (0.5 - 0.5 * Math.cos(rotationAngle/180*Math.PI))
                    selComp.y += myMouseX * 0.5 * Math.sin(rotationAngle/180*Math.PI)
                }
            }
        }
    }

    Image {
        id: top
        width: rulersSize / 1.5
        height: rulersSize
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.top
        source: "qrc:/images/ActionResizeVertically.svg"

        MouseArea {
            anchors.fill: parent
            drag{ target: parent; axis: Drag.YAxis }
            onMouseYChanged: {
                if(drag.active){
                    var myMouseY = mouseY
                    if (selComp.height - mouseY < minSize)
                        myMouseY = selComp.height - minSize
                    selComp.height -= myMouseY
                    selComp.x -= myMouseY * 0.5 * Math.sin(rotationAngle/180*Math.PI)
                    selComp.y += myMouseY * (0.5 + 0.5 * Math.cos(rotationAngle/180*Math.PI))
                }
            }
        }
    }


    Image {
        id: bottom
        width: rulersSize / 1.5
        height: rulersSize
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.bottom
        source: "qrc:/images/ActionResizeVertically.svg"

        MouseArea {
            anchors.fill: parent
            drag{ target: parent; axis: Drag.YAxis }
            onMouseYChanged: {
                if(drag.active){
                    var myMouseY = mouseY
                    if (selComp.height + mouseY < minSize)
                        myMouseY = minSize - selComp.height
                    selComp.height += myMouseY
                    selComp.x -= myMouseY * 0.5 * Math.sin(rotationAngle/180*Math.PI)
                    selComp.y -= myMouseY * (0.5 - 0.5 * Math.cos(rotationAngle/180*Math.PI))
                }
            }
        }
    }
}
